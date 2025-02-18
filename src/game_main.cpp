/*
 * TheXTech - A platform game engine ported from old source code for VB6
 *
 * Copyright (c) 2009-2011 Andrew Spinks, original VB6 code
 * Copyright (c) 2020-2022 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_thread.h>

#include <Logger/logger.h>
#include <Utils/files.h>
#include <AppPath/app_path.h>
#include <PGE_File_Formats/file_formats.h>
#ifdef THEXTECH_INTERPROC_SUPPORTED
#   include <InterProcess/intproc.h>
#endif
#include <pge_delay.h>
#include <fmt_format_ne.h>

#ifdef ENABLE_XTECH_LUA
#include "xtech_lua_main.h"
#endif

#include "globals.h"
#include "game_main.h"
#include "gfx.h"

#include "config.h"
#include "frame_timer.h"
#include "compat.h"
#include "blocks.h"
#include "change_res.h"
#include "collision.h"
#include "effect.h"
#include "graphics.h"
#include "layers.h"
#include "load_gfx.h"
#include "player.h"
#include "sound.h"
#include "video.h"
#include "editor.h"
#include "editor/new_editor.h"
#include "custom.h"
#include "main/world_globals.h"
#include "main/cheat_code.h"
#include "main/game_globals.h"
#include "main/level_file.h"
#include "main/world_file.h"
#include "main/speedrunner.h"
#include "main/menu_main.h"
#include "main/game_info.h"
#include "main/record.h"
#include "core/render.h"
#include "core/window.h"
#include "core/events.h"
#include "core/msgbox.h"
#include "script/luna/luna.h"

#include "pseudo_vb.h"

#include "controls.h"

#include "config.h"
#include "main/screen_connect.h"

void CheckActive();
// set up sizable blocks
void SizableBlocks();

// game_main_setupphysics.cpp

static int loadingThread(void *waiter_ptr)
{
#ifndef PGE_NO_THREADING
    auto *waiter = (SDL_atomic_t *)waiter_ptr;
#else
    UNUSED(waiter_ptr);
#endif
    SetupPhysics(); // Setup Physics
    SetupGraphics(); // setup graphics
//    Load GFX 'load the graphics form
//    GFX.load(); // load the graphics form // Moved to before sound load
    SizableBlocks();
    LoadGFX(); // load the graphics from file
    SetupVars(); //Setup Variables

#ifdef THEXTECH_PRELOAD_LEVELS
    FindWorlds();
    FindLevels();
#endif

    InitSound(); // Setup sound effects

#ifndef PGE_NO_THREADING
    if(waiter)
        SDL_AtomicSet(waiter, 0);
#endif

    return 0;
}

static std::string getIntrFile()
{
    auto introPath = AppPath + "intro.lvlx";

    if(!Files::fileExists(introPath))
        introPath = AppPath + "intro.lvl";

    if(!Files::fileExists(introPath))
        return std::string();

    pLogDebug("Found root intro level file: %s", introPath.c_str());

    return introPath;
}

static std::string findIntroLevel()
{
    std::string introPath;
    std::string introSetDir = AppPath + "introset/";

    if(!DirMan::exists(introSetDir))
        return getIntrFile();

    DirMan introSet(introSetDir);
    std::vector<std::string> intros;

    if(!introSet.getListOfFiles(intros, {".lvl", "lvlx"}) || intros.empty())
        return getIntrFile();

    std::sort(intros.begin(), intros.end());

    for(auto &i : intros)
    {
        i.insert(0, introSetDir);
        pLogDebug("Found introset intro level: %s", i.c_str());
    }

    auto rootIntro = getIntrFile();
    if(!rootIntro.empty())
        intros.push_back(rootIntro);

    const std::string &selected = intros[iRand2(intros.size())];;

    pLogDebug("Selected intro level to start: %s", selected.c_str());

    return selected;
}


int GameMain(const CmdLineSetup_t &setup)
{
    Player_t blankPlayer;
//    int A = 0;
//    int B = 0;
//    int C = 0;
    bool tempBool = false;
    int lastWarpEntered = 0;

//    LB = "\n";
//    EoT = "";

    FrameSkip = setup.frameSkip;
    noSound = setup.noSound;
    neverPause = setup.neverPause;

    CompatSetEnforcedLevel(setup.compatibilityLevel);

    g_speedRunnerMode = setup.speedRunnerMode;
    g_drawController |= setup.showControllerState;
    speedRun_setSemitransparentRender(setup.speedRunnerSemiTransparent);
    speedRun_setBlinkEffect(setup.speedRunnerBlinkEffect);

    ResetCompat();
    cheats_reset();

    // [ !Here was a starting dialog! ]

    //    frmLoader.Show 'show the Splash screen
    //    Do
    //        DoEvents
    //    Loop While StartMenu = False 'wait until the player clicks a button

    initMainMenu();
    StartMenu = true;

    initAll();

//    Unload frmLoader
    gfxLoaderTestMode = setup.testLevelMode;

    if(!GFX.load()) // Load UI graphics
        return 1;

//    If LevelEditor = False Then
//        frmMain.Show // Show window a bit later
//    XWindow::show();
//        GameMenu = True
    GameMenu = true;
//    Else
//        frmSplash.Show
//        BlocksSorted = True
//    End If

    LoadingInProcess = true;

    ShowFPS = setup.testShowFPS;
    MaxFPS = setup.testMaxFPS; // || (g_videoSettings.renderModeObtained == RENDER_ACCELERATED_VSYNC);

    OpenConfig();

    XEvents::doEvents();

#ifdef __EMSCRIPTEN__ // Workaround for a recent Chrome's policy to avoid sudden sound without user's interaction
    XWindow::show(); // Don't show window until playing an initial sound

    while(!SharedCursor.Primary)
    {
        XRender::setTargetTexture();
        XRender::clearBuffer();
        SuperPrint("Click to start a game", 3, 230, 280);
        XRender::repaint();
        XRender::setTargetScreen();
        XEvents::doEvents();
        Controls::Update();
        PGE_Delay(10);
    }
#endif

    if(!noSound)
        InitMixerX();

#ifndef PGE_NO_THREADING
    gfxLoaderThreadingMode = true;
#endif
    XWindow::show(); // Don't show window until playing an initial sound

    if(!noSound)
    {
        if(!setup.testLevelMode)
            PlayInitSound();
    }

#ifndef PGE_NO_THREADING
    {
        SDL_Thread*     loadThread;
        int             threadReturnValue;
        SDL_atomic_t    loadWaiter;
        int             loadWaiterState = 1;

        SDL_AtomicSet(&loadWaiter, loadWaiterState);
        loadThread = SDL_CreateThread(loadingThread, "Loader", &loadWaiter);

        if(!loadThread)
        {
            gfxLoaderThreadingMode = false;
            pLogCritical("Failed to create the loading thread! Do running the load directly");
            loadingThread(nullptr);
        }
        else
        {
            do
            {
                UpdateLoadREAL();
                PGE_Delay(15);
                loadWaiterState = SDL_AtomicGet(&loadWaiter);
            } while(loadWaiterState);

            SDL_WaitThread(loadThread, &threadReturnValue);
            pLogDebug("Loading thread was exited with %d code.", threadReturnValue);
        }
    }
#else
    loadingThread(nullptr);
#endif

    LevelSelect = true; // world map is to be shown

#ifdef THEXTECH_INTERPROC_SUPPORTED
    if(setup.interprocess)
        IntProc::init();
#endif

    LoadingInProcess = false;

    // Clear the screen
    XRender::setTargetTexture();
    XRender::clearBuffer();
    XRender::repaint();
    XEvents::doEvents();

    if(!neverPause && !XWindow::hasWindowInputFocus())
        SoundPauseEngine(1);

    if(!setup.testLevel.empty() || !setup.testReplay.empty() || setup.interprocess) // Start level testing immediately!
    {
        GameMenu = false;
        LevelSelect = false;

        if(!setup.testReplay.empty())
            Record::LoadReplay(setup.testReplay, setup.testLevel);
        else
            FullFileName = setup.testLevel;

        if(setup.testBattleMode)
        {
            numPlayers = 2;
            BattleMode = true;
            BattleIntro = 150;
        }
        else
        {
            numPlayers = setup.testNumPlayers;
            BattleMode = false;
            BattleIntro = 0;
        }
        GodMode = setup.testGodMode;
        GrabAll = setup.testGrabAll;

        editorScreen.ResetCursor();
        zTestLevel(setup.testMagicHand, setup.interprocess);
    }

    do
    {
        if(GameMenu || MagicHand || LevelEditor)
        {
            XWindow::setCursor(AbstractWindow_t::CURSOR_NONE);
            XWindow::showCursor(0);
        }
        else if(!resChanged)
        {
            XWindow::setCursor(AbstractWindow_t::CURSOR_DEFAULT);
            XWindow::showCursor(1);
        }


        if(LevelEditor) // Load the level editor
        {
            // if(resChanged)
            //     ChangeScreen();
            BattleMode = false;
            SingleCoop = 0;
            numPlayers = 0;
            ScreenType = 0;
            XEvents::doEvents();
            SetupEditorGraphics(); //Set up the editor graphics
            SetupScreens();
            MagicHand = false;
            MouseRelease = false;
            ScrollRelease = false;

            // coming back from a level test
            if(!WorldEditor)
            {
                EditorRestore();
            }

            // Run the frame-loop
            runFrameLoop(&EditorLoop,
                         nullptr,
                        []()->bool{ return LevelEditor || WorldEditor;}, nullptr,
                        nullptr,
                        nullptr);

            MenuMode = MENU_MAIN; // MENU_INTRO when this is implemented
            LevelEditor = false;
            WorldEditor = false;
            XRender::clearBuffer();
            XRender::repaint();
#ifdef THEXTECH_PRELOAD_LEVELS
            FindWorlds();
#endif
        }

        // TheXTech Credits
        else if(GameOutro)
        {
            ShadowMode = false;
            GodMode = false;
            GrabAll= false;
            CaptainN = false;
            FlameThrower = false;
            FreezeNPCs = false;
            WalkAnywhere = false;
            MultiHop = false;
            SuperSpeed = false;
            FlyForever = false;
            GoToLevelNoGameThing = false;

            for(int A = 1; A <= maxPlayers; A++)
                Player[A] = blankPlayer;

            numPlayers = g_gameInfo.outroMaxPlayersCount;
            if(g_gameInfo.outroDeadMode)
                numPlayers = 1; // Deadman mode
            GameMenu = false;
            StopMusic();

            auto outroPath = AppPath + "outro.lvlx";
            if(!Files::fileExists(outroPath))
                outroPath = AppPath + "outro.lvl";
            OpenLevel(outroPath);

            SetupScreens();
            ClearBuffer = true;

            for(int A = 1; A <= numPlayers; ++A)
            {
                Player_t &p = Player[A];

                if(A <= (int)g_gameInfo.outroStates.size())
                    p.State = g_gameInfo.outroStates[A - 1];
                else if(A == 1)
                    p.State = 4;
                else if(A == 2)
                    p.State = 7;
                else if(A == 3)
                    p.State = 5;
                else if(A == 4)
                    p.State = 3;
                else
                    p.State = 6;

                p.Character = g_gameInfo.outroCharacterNext();

                if(A <= (int)g_gameInfo.outroMounts.size())
                {
                    p.Mount = g_gameInfo.outroMounts[A - 1];
                    switch(p.Mount)
                    {
                    case 1:
                        p.MountType = iRand(3) + 1;
                        break;
                    case 3:
                        p.MountType = iRand(8) + 1;
                        break;
                    default:
                        p.MountType = 0;
                    }
                }
                else if(A == 4)
                {
                    p.Mount = 1;
                    p.MountType = iRand(3) + 1;
                }
                else if(A == 2)
                {
                    p.Mount = 3;
                    p.MountType = iRand(8) + 1;
                }

                p.HeldBonus = 0;
                p.Section = 0;
                p.Location.Height = Physics.PlayerHeight[p.Character][p.State];
                p.Location.Width = Physics.PlayerWidth[p.Character][p.State];
            }

            SetupPlayers();
            CreditChop = 300; // 100
            EndCredits = 0;
            GameOutroDoQuit = false;
            SetupCredits();

            // Update graphics before loop begin (to process an initial lazy-unpacking of used sprites)
            GraphicsLazyPreLoad();
            resetFrameTimer();

            for(int A = 1; A <= numPlayers; ++A)
            {
                if(g_gameInfo.outroWalkDirection == 0 && A <= (int)g_gameInfo.outroInitialDirections.size())
                {
                    if(g_gameInfo.outroInitialDirections[A - 1] < 0)
                        Player[A].Direction = -1;
                    else if(g_gameInfo.outroInitialDirections[A - 1] > 0)
                        Player[A].Direction = 1;
                }
            }

            if(g_gameInfo.outroDeadMode)
            {
                CheckSection(1);
                for(int A = 1; A <= numPlayers; ++A)
                    Player[A].Dead = true;
            }

            lunaLoad();

            clearScreenFaders();

            // Run the frame-loop
            runFrameLoop(&OutroLoop,
                         nullptr,
                        []()->bool{ return GameOutro;}, nullptr,
                        nullptr,
                        []()->void
                        {
                            SetupScreens();
                        });
        }

        // The Game Menu
        else if(GameMenu)
        {
            BattleIntro = 0;
            BattleOutro = 0;
            AllCharBlock = 0;
            Cheater = false;

            // in a main menu, reset this into initial state
            GoToLevelNoGameThing = false;

            for(int A = 1; A <= maxPlayers; ++A)
            {
                OwedMount[A] = 0;
                OwedMountType[A] = 0;
            }

            MenuMouseRelease = false;
            MenuMouseClick = false;
            MenuCursorCanMove = false;
            BattleMode = false;

            if(MenuMode != MENU_BATTLE_MODE)
            {
                PlayerCharacter = 0;
                PlayerCharacter2 = 0;
            }

            pLogDebug("Clear check-points at Game Menu start");
            Checkpoint.clear();
            CheckpointsList.clear();
            WorldPlayer[1].Frame = 0;
            cheats_clearBuffer();
            LevelBeatCode = 0;
            curWorldLevel = 0;

            ClearWorld();

            ReturnWarp = 0;
            ReturnWarpSaved = 0;
            ShadowMode = false;
            GodMode = false;
            GrabAll = false;
            CaptainN = false;
            FlameThrower = false;
            FreezeNPCs = false;
            WalkAnywhere = false;
            MultiHop = false;
            SuperSpeed = false;
            FlyForever = false;
            BeatTheGame = false;

            SetupScreens();

            BattleOutro = 0;
            BattleIntro = 0;

            for(int A = 1; A <= maxPlayers; ++A)
            {
                Player[A] = blankPlayer;
            }

            numPlayers = g_gameInfo.introMaxPlayersCount;
            if(g_gameInfo.introDeadMode)
                numPlayers = 1;// one deadman should be

            auto introPath = findIntroLevel();
            if(introPath.empty())
            {
                XMsgBox::errorMsgBox("Fatal error",
                                     "Can't find any intro level file to start the main menu.\n"
                                     "The game will be closed.\n"
                                     "\n"
                                     "Please make sure the intro.lvlx or intro.lvl file is exist\n"
                                     "in the game assets directory, or make sure the \"introset\" directory\n"
                                     "contains any valid level files.");
                return 1;// Fatal error happen
            }

            OpenLevel(introPath);
            vScreenX[1] = -level[0].X;

            if(g_config.EnableInterLevelFade)
                g_levelScreenFader.setupFader(3, 65, 0, ScreenFader::S_FADE);
            else
                clearScreenFaders();

            setMusicStartDelay(); // Don't start music until all gfx will be loaded

            StartMusic(0);
            SetupPlayers();

            For(A, 1, numPlayers)
            {
                Player_t &p = Player[A];
                p.State = iRand(6) + 2;
                // p.Character = (iRand() % 5) + 1;

                // if(A >= 1 && A <= 5)
                p.Character = g_gameInfo.introCharacterNext();

                p.HeldBonus = 0;
                p.Section = 0;
                p.Location.Height = Physics.PlayerHeight[p.Character][p.State];
                p.Location.Width = Physics.PlayerWidth[p.Character][p.State];
                p.Location.X = level[p.Section].X + ((128 + dRand() * 64) * A);
                p.Location.Y = level[p.Section].Height - p.Location.Height - 65;

                do
                {
                    tempBool = true;
                    for(int B = 1; B <= numBlock; ++B)
                    {
                        if(CheckCollision(p.Location, Block[B].Location))
                        {
                            p.Location.Y = Block[B].Location.Y - p.Location.Height - 0.1;
                            tempBool = false;
                        }
                    }
                } while(!tempBool);
                p.Dead = true;
            }

            // Update graphics before loop begin (to process inital lazy-unpacking of used sprites)
            GraphicsLazyPreLoad();
            resetFrameTimer();
            // Clear the speed-runner timer
            speedRun_resetTotal();

            lunaLoad();

            delayedMusicStart(); // Allow music being started

            ProcEvent(EVENT_LEVEL_START, true);
            For(A, 2, maxEvents)
            {
                if(Events[A].AutoStart)
                    ProcEvent(A, true);
            }

            // Main menu loop
            runFrameLoop(&MenuLoop, nullptr, []()->bool{ return GameMenu;});
            if(!GameIsActive)
            {
                speedRun_saveStats();
                return 0;// Break on quit
            }
        }

        // World Map
        else if(LevelSelect)
        {
            cheats_clearBuffer();

            For(A, 1, numPlayers)
            {
                if(Player[A].Mount == 0 || Player[A].Mount == 2)
                {
                    if(OwedMount[A] > 0)
                    {
                        Player[A].Mount = OwedMount[A];
                        if(OwedMountType[A] > 0)
                            Player[A].MountType = OwedMountType[A];
                        else
                            Player[A].MountType = 1;
                    }
                }

                OwedMount[A] = 0;
                OwedMountType[A] = 0;
            }

            if(!NoMap)
            {
                // Restore the previously preserved world map paths
                FileNameFull = FileNameFullWorld;
                FileName = FileNameWorld;
                FileNamePath = FileNamePathWorld;
                FileFormat = FileFormatWorld;

                // Recalculate the FullFileName
                FullFileName = FileNamePath + FileNameFull;
            }

            LoadCustomCompat();
            FindCustomPlayers();
            LoadCustomGFX();
            LoadCustomSound();
            SetupPlayers();

            if(!NoMap)
                FindWldStars();

            if((!StartLevel.empty() && NoMap) || !GoToLevel.empty())
            {
                if(NoMap)
                    SaveGame();

                Player[1].Vine = 0;
                Player[2].Vine = 0;

//                if(!GoToLevelNoGameThing)
//                    PlaySound(SFX_LevelSelect);
                SoundPause[26] = 2000;

                LevelSelect = false;

                XRender::setTargetTexture();
                XRender::clearBuffer();
                XRender::repaint();

                lunaReset();
                ResetSoundFX();
                ClearLevel();

                std::string levelPath;
                if(GoToLevel.empty())
                    levelPath = SelectWorld[selWorld].WorldPath + StartLevel;
                else
                {
                    levelPath = SelectWorld[selWorld].WorldPath + GoToLevel;
                    GoToLevel.clear();
                }

                if(!OpenLevel(levelPath))
                {
                    MessageText = fmt::format_ne("ERROR: Can't open \"{0}\": file doesn't exist or corrupted.", levelPath);
                    PauseGame(PauseCode::Message);
                    ErrorQuit = true;
                }

                if(!GoToLevelNoGameThing)
                {
                    GameThing(1000, 3);
                }
                else
                {
                    XRender::setTargetTexture();
                    XRender::clearBuffer();
                    XRender::repaint();
                }
            }
            else
            {
                ResetSoundFX();
                setMusicStartDelay(); // Don't start music until all gfx will be loaded

                if(curWorldMusic > 0)
                    StartMusic(curWorldMusic);

                resetFrameTimer();
                speedRun_resetCurrent();

                // On a world map, reset this into default state
                GoToLevelNoGameThing = false;

                // Update graphics before loop begin (to process inital lazy-unpacking of used sprites)
                UpdateGraphics2(true);
                resetFrameTimer();

                if(g_config.EnableInterLevelFade)
                    g_worldScreenFader.setupFader(4, 65, 0, ScreenFader::S_FADE);
                else
                    g_worldScreenFader.clearFader();

                // WorldLoop will automatically resume the music as needed
                // delayedMusicStart(); // Allow music being started

                // 'level select loop
                runFrameLoop(nullptr, &WorldLoop,
                             []()->bool{return LevelSelect;},
                             nullptr,
                             []()->void{FreezeNPCs = false;});

                if(!GameIsActive)
                {
                    speedRun_saveStats();
                    return 0;// Break on quit
                }
            }
        }

        // MAIN GAME
        else
        {
            cheats_clearBuffer();
            EndLevel = false;

            Record::InitRecording(); // initializes level data recording

            for(int A = 1; A <= numPlayers; ++A)
            {
                if(Player[A].Mount == 2)
                    Player[A].Mount = 0; // take players off the clown car
            }

            setMusicStartDelay(); // Don't start music until all gfx will be loaded

            SetupPlayers(); // Setup Players for the level

            if(LevelRestartRequested && Checkpoint.empty())
                StartWarp = lastWarpEntered; // When restarting a level (after death), don't restore an entered warp on checkpoints

            qScreen = false;
            LevelRestartRequested = false;

            if(lastWarpEntered != StartWarp)
                lastWarpEntered = StartWarp; // Re-use it when player re-enters a level after death (when option is toggled on)

// for warp entrances
            if((ReturnWarp > 0 && IsEpisodeIntro/*FileName == StartLevel*/) || (StartWarp > 0))
            {
                for(int numPlayersMax = numPlayers, A = 1; A <= numPlayersMax; ++A)
                {
                    Player_t &p = Player[A];

                    if(StartWarp > 0)
                        p.Warp = StartWarp;
                    else
                        p.Warp = ReturnWarp;

                    p.WarpBackward = false;
                    auto &warp = Warp[p.Warp];

                    if(warp.Effect == 1)
                    {
                        if(warp.Direction2 == 1) // DOWN
                        {
//                                .Location.X = Warp(.Warp).Exit.X + Warp(.Warp).Exit.Width / 2 - .Location.Width / 2
                            p.Location.X = warp.Exit.X + (warp.Exit.Width / 2) - (p.Location.Width / 2);
//                                .Location.Y = Warp(.Warp).Exit.Y - .Location.Height - 8
                            p.Location.Y = warp.Exit.Y - p.Location.Height - 8;
                        }
//                            ElseIf Warp(.Warp).Direction2 = 3 Then
                        if(warp.Direction2 == 3) // UP
                        {
//                                .Location.X = Warp(.Warp).Exit.X + Warp(.Warp).Exit.Width / 2 - .Location.Width / 2
                            p.Location.X = warp.Exit.X + (warp.Exit.Width / 2) - (p.Location.Width / 2);
//                                .Location.Y = Warp(.Warp).Exit.Y + Warp(.Warp).Exit.Height + 8
                            p.Location.Y = warp.Exit.Y + warp.Exit.Height + 8;
                        }
//                            ElseIf Warp(.Warp).Direction2 = 2 Then
                        if(warp.Direction2 == 2) // RIGHT
                        {
//                                If .Mount = 3 Then .Duck = True
                            if(p.Mount == 3) p.Duck = true;
//                                .Location.X = Warp(.Warp).Exit.X - .Location.Width - 8
                            p.Location.X = warp.Exit.X - p.Location.Width - 8;
//                                .Location.Y = Warp(.Warp).Exit.Y + Warp(.Warp).Exit.Height - .Location.Height - 2
                            p.Location.Y = warp.Exit.Y + warp.Exit.Height - p.Location.Height - 2;
                        }
//                            ElseIf Warp(.Warp).Direction2 = 4 Then
                        if(warp.Direction2 == 4) // LEFT
                        {
//                                If .Mount = 3 Then .Duck = True
                            if(p.Mount == 3) p.Duck = true;
//                                .Location.X = Warp(.Warp).Exit.X + Warp(.Warp).Exit.Width + 8
                            p.Location.X = warp.Exit.X + warp.Exit.Width + 8;
//                                .Location.Y = Warp(.Warp).Exit.Y + Warp(.Warp).Exit.Height - .Location.Height - 2
                            p.Location.Y = warp.Exit.Y + warp.Exit.Height - p.Location.Height - 2;
//                            End If
                        }

                        PlayerFrame(p);
                        CheckSection(A);
                        SoundPause[17] = 0;
                        p.Effect = 8;
                        p.Effect2 = 950;
                    }
                    else if(warp.Effect == 2)
                    {
//                            .Location.X = Warp(.Warp).Exit.X + Warp(.Warp).Exit.Width / 2 - .Location.Width / 2
                        p.Location.X = warp.Exit.X + warp.Exit.Width / 2 - p.Location.Width / 2;
//                            .Location.Y = Warp(.Warp).Exit.Y + Warp(.Warp).Exit.Height - .Location.Height
                        p.Location.Y = warp.Exit.Y + warp.Exit.Height - p.Location.Height;

                        CheckSection(A);
                        p.Effect = 8;
                        p.Effect2 = 2000;
                    }
                    else if(warp.Effect == 3) // Portal warp
                    {
                        p.Location.X = warp.Exit.X + warp.Exit.Width / 2 - p.Location.Width / 2;
                        p.Location.Y = warp.Exit.Y + warp.Exit.Height - p.Location.Height;
                        CheckSection(A);
                        p.WarpCD = 50;
                    }
                }

                if(StartWarp > 0)
                    StartWarp = 0;
                else
                    ReturnWarp = 0;
            }

            speedRun_resetCurrent();
//'--------------------------------------------

            // Update graphics before loop begin (to process inital lazy-unpacking of used sprites)
            GraphicsLazyPreLoad();
            resetFrameTimer();

            speedRun_triggerEnter();

            clearScreenFaders(); // Reset all faders
            if(g_config.EnableInterLevelFade)
                g_levelScreenFader.setupFader(2, 65, 0, ScreenFader::S_FADE);

            lunaLoad();

            delayedMusicStart(); // Allow music being started

            ProcEvent(EVENT_LEVEL_START, true);
            for(int A = 2; A <= maxEvents; ++A)
            {
                if(Events[A].AutoStart)
                    ProcEvent(A, true);
            }

            // MAIN GAME LOOP
            runFrameLoop(nullptr, &GameLoop,
            []()->bool{return !LevelSelect && !GameMenu;},
            []()->bool
            {
                if(!LivingPlayers())
                {
                    EveryonesDead();
                    return true;
                }
                return false;
            });

            Record::EndRecording();

            StopAllSounds();
            UnloadExtSounds();

            if(!GameIsActive)
            {
                speedRun_saveStats();
                return 0;// Break on quit
            }

            // TODO: Utilize this and any TestLevel/MagicHand related code to allow PGE Editor integration
            // (do any code without interaction of no more existnig Editor VB forms, keep IPS with PGE Editor instead)

//            If TestLevel = True Then
            if(TestLevel)
            {
                // if failed, restart
                if(LevelBeatCode == 0 && g_config.editor_pause_on_death)
                {
                    LevelSelect = false;
                    LevelBeatCode = -2; // checked in PauseScreen::Init()
                    PauseGame(PauseCode::PauseScreen);
                }

                // check that we are still restarting (it could have been canceled above)
                if(LevelBeatCode == 0 || LevelBeatCode == -2)
                {
                    GameThing();
                    zTestLevel(setup.testMagicHand || editorScreen.test_magic_hand, setup.interprocess); // Restart level
                }
                // from editor, return to editor
                else if(!Backup_FullFileName.empty())
                {
                    // printf("returning to editor...\n");

                    TestLevel = false;
                    LevelEditor = true;

                    // reopen the temporary level (FullFileName)
                    OpenLevel(FullFileName);

                    // reset FullFileName to point to the real level (Backup_FullFileName)
                    Files::deleteFile(FullFileName);
                    FullFileName = Backup_FullFileName;
                    // this is needed because the temporary levels are currently saved as ".lvl(x)tst"
                    if(FileNameFull.size() > 3 && FileNameFull.substr(FileNameFull.size() - 3) == "tst")
                        FileNameFull.resize(FileNameFull.size() - 3);

                    Backup_FullFileName = "";

                    editorScreen.active = false;
                    MouseRelease = false;

                    if(g_config.EnableInterLevelFade)
                        g_levelScreenFader.setupFader(3, 65, 0, ScreenFader::S_FADE);
                }
                // from command line, close
                else if(setup.testLevelMode)
                {
                    GameIsActive = false;
                }

                LevelBeatCode = 0;

//                If nPlay.Online = False Then
//                    OpenLevel FullFileName
//                OpenLevel(FullFileName);
//                Else
//                    If nPlay.Mode = 1 Then
//                        Netplay.sendData "H0" & LB
//                        If Len(FullFileName) > 4 Then
//                            If LCase(Right(FullFileName, 4)) = ".lvl" Then
//                                OpenLevel FullFileName
//                            Else
//                                For A = 1 To 15
//                                    If nPlay.ClientCon(A) = True Then Netplay.InitSync A
//                                Next A
//                            End If
//                        Else
//                            For A = 1 To 15
//                                If nPlay.ClientCon(A) = True Then Netplay.InitSync A
//                            Next A
//                        End If
//                    End If
//                End If

//                LevelSelect = False
                LevelSelect = false;
            }
//            Else
            else if(!LevelRestartRequested)
            {
                lunaReset();
                ResetSoundFX();
                ClearLevel();
//            End If
            } // TestLevel
        }

    } while(GameIsActive);

    return 0;
}

// game_main_setupvars.cpp

// game_loop.cpp

// menu_loop.cpp

void EditorLoop()
{
    Controls::Update();
    UpdateEditor();
    UpdateBlocks();
    UpdateEffects();
    if(WorldEditor)
        UpdateGraphics2();
    else
        UpdateGraphics();

    updateScreenFaders();

    // TODO: if there's a second screen, draw editor screen there too

    UpdateSound();
}

void KillIt()
{
    GameIsActive = false;
#ifndef RENDER_FULLSCREEN_ALWAYS
    XWindow::hide();
    if(resChanged)
        SetOrigRes();
#else
    XRender::clearBuffer();
    XRender::repaint();
#endif
    lunaReset();
    QuitMixerX();
    UnloadGFX();
    XWindow::showCursor(1);
}


void NextLevel()
{
    int A = 0;

    for(A = 1; A <= numPlayers; A++)
        Player[A].HoldingNPC = 0;

    LevelMacro = LEVELMACRO_OFF;
    LevelMacroCounter = 0;
    StopMusic();
    lunaReset();
    ResetSoundFX();
    ClearLevel();
    XRender::setTargetTexture();
    XRender::clearBuffer();
    XRender::repaint();
    XEvents::doEvents();

    if(!TestLevel && GoToLevel.empty() && !NoMap)
        PGE_Delay(500);

    if(BattleMode && !LevelEditor && !TestLevel)
    {
        EndLevel = false;
        GameMenu = true;
        MenuMode = MENU_BATTLE_MODE;
        MenuCursor = selWorld - 1;
        PlayerCharacter = Player[1].Character;
        PlayerCharacter2 = Player[2].Character;
    }
    else
    {
        LevelSelect = true;
        EndLevel = false;
        if(TestLevel && BattleMode)
        {
            BattleIntro = 150;
            GameIsActive = false; // Quit game
        }
    }
}

// macros mainly used for end of level stuffs. takes over the players controls
void UpdateMacro()
{
    int A = 0;
    bool OnScreen = false;

#ifdef THEXTECH_INTERPROC_SUPPORTED
    if(LevelMacro != LEVELMACRO_OFF && LevelMacroCounter == 0 && IntProc::isEnabled())
    {
        for(int i = 0; i < numPlayers; ++i)
        {
            auto &p = Player[i + 1];
            IntProc::sendPlayerSettings(i, p.Character, p.State, p.Mount, p.MountType);
        }
    }
#endif

    if(LevelMacro == LEVELMACRO_CARD_ROULETTE_EXIT) // SMB3 Exit
    {
        for(A = 1; A <= numPlayers; A++)
        {
            auto &p = Player[A];
            auto &c = p.Controls;
            if(p.Location.X < level[p.Section].Width && !p.Dead)
            {
                OnScreen = true;
                c.Down = false;
                c.Drop = false;
                c.Jump = false;
                c.Left = false;
                c.Right = true;
                c.Run = false;
                c.Up = false;
                c.Start = false;
                c.AltJump = false;
                c.AltRun = false;
                if(p.Wet > 0 && p.CanJump)
                {
                    if(p.Location.SpeedY > 1)
                        c.Jump = true;
                }
            }
            else
            {
                p.Location.SpeedY = -Physics.PlayerGravity;
                c.Down = false;
                c.Drop = false;
                c.Jump = false;
                c.Left = false;
                c.Right = true;
                c.Run = false;
                c.Up = false;
                c.Start = false;
                c.AltJump = false;
                c.AltRun = false;
            }
        }

        if(!OnScreen)
        {
            LevelMacroCounter++;

            if(g_config.EnableInterLevelFade && LevelMacroCounter == 34)
                g_levelScreenFader.setupFader(1, 0, 65, ScreenFader::S_FADE);

            if(LevelMacroCounter >= 100)
            {
                LevelBeatCode = 1;
                LevelMacro = LEVELMACRO_OFF;
                LevelMacroCounter = 0;
                EndLevel = true;
            }
        }
    }
    else if(LevelMacro == LEVELMACRO_QUESTION_SPHERE_EXIT)
    {
        for(A = 1; A <= numPlayers; A++)
        {
            auto &c = Player[A].Controls;
            c.Down = false;
            c.Drop = false;
            c.Jump = false;
            c.Left = false;
            c.Right = false;
            c.Run = false;
            c.Up = false;
            c.Start = false;
            c.AltJump = false;
            c.AltRun = false;
        }

        LevelMacroCounter++;

        if(g_config.EnableInterLevelFade && LevelMacroCounter == 395)
            g_levelScreenFader.setupFader(1, 0, 65, ScreenFader::S_FADE);

        if(LevelMacroCounter >= 460)
        {
            LevelBeatCode = 2;
            EndLevel = true;
            LevelMacro = LEVELMACRO_OFF;
            LevelMacroCounter = 0;
            XRender::clearBuffer();
        }
    }
    else if(LevelMacro == LEVELMACRO_KEYHOLE_EXIT)
    {
        float tempTime = 0;
        float gameTime = 0;
        int keyholeMax = g_compatibility.fix_keyhole_framerate ? 192 : 300;

        do
        {
            // tempTime = Timer - Int(Timer)

            tempTime = (float(SDL_GetTicks()) / 1000.0f) - std::floor(float(SDL_GetTicks()) / 1000.0f);
//            if(tempTime > (float)(gameTime + 0.01f) || tempTime < gameTime)

            if(g_compatibility.fix_keyhole_framerate)
                XEvents::doEvents();

            if(g_compatibility.fix_keyhole_framerate ?
               canProceedFrame() :
               (tempTime > (float)(gameTime + 0.01f) || tempTime < gameTime))
            {
                gameTime = tempTime;

                if(g_compatibility.fix_keyhole_framerate)
                    computeFrameTime1();
                else
                    XEvents::doEvents();

                speedRun_tick();
                Controls::Update();
                UpdateGraphics();
                UpdateSound();
                BlockFrames();

                if(g_compatibility.fix_keyhole_framerate)
                {
                    XEvents::doEvents();
                    computeFrameTime2();
                }

                updateScreenFaders();

                LevelMacroCounter++;

                if(g_config.EnableInterLevelFade && LevelMacroCounter == (keyholeMax - 65))
                    g_levelScreenFader.setupFader(1, 0, 65, ScreenFader::S_FADE);

                if(LevelMacroCounter >= keyholeMax) /*300*/
                    break;
            }

            if(!GameIsActive)
            {
                speedRun_saveStats();
                return;
            }

            PGE_Delay(1);
        } while(true);

        LevelBeatCode = 4;
        EndLevel = true;
        LevelMacro = LEVELMACRO_OFF;
        LevelMacroCounter = 0;
        XRender::clearBuffer();
    }
    else if(LevelMacro == LEVELMACRO_CRYSTAL_BALL_EXIT)
    {
        for(A = 1; A <= numPlayers; A++)
        {
            auto &c = Player[A].Controls;
            c.Down = false;
            c.Drop = false;
            c.Jump = false;
            c.Left = false;
            c.Right = false;
            c.Run = false;
            c.Up = false;
            c.Start = false;
            c.AltJump = false;
            c.AltRun = false;
        }

        LevelMacroCounter++;

        if(g_config.EnableInterLevelFade && LevelMacroCounter == 235)
            g_levelScreenFader.setupFader(1, 0, 65, ScreenFader::S_FADE);

        if(LevelMacroCounter >= 300)
        {
            LevelBeatCode = 5;
            EndLevel = true;
            LevelMacro = LEVELMACRO_OFF;
            LevelMacroCounter = 0;
            XRender::clearBuffer();
        }
    }
    else if(LevelMacro == LEVELMACRO_GAME_COMPLETE_EXIT)
    {
        // numNPCs = 0
        for(A = 1; A <= numPlayers; A++)
        {
            auto &c = Player[A].Controls;
            c.Down = false;
            c.Drop = false;
            c.Jump = false;
            c.Left = false;
            c.Right = false;
            c.Run = false;
            c.Up = false;
            c.Start = false;
            c.AltJump = false;
            c.AltRun = false;
        }

        LevelMacroCounter++;

        if(LevelMacroCounter == 250)
            PlaySound(SFX_GameBeat);

        if(g_config.EnableInterLevelFade && LevelMacroCounter == 735)
            g_levelScreenFader.setupFader(1, 0, 65, ScreenFader::S_FADE);

        if(LevelMacroCounter >= 800)
        {
            EndLevel = true;
            LevelMacro = LEVELMACRO_OFF;
            LevelMacroCounter = 0;
            if(!TestLevel)
            {
                BeatTheGame = true;
                SaveGame();
                GameOutro = true;
                MenuMode = MENU_MAIN;
                MenuCursor = 0;
            }
            XRender::clearBuffer();
        }
    }
    else if(LevelMacro == LEVELMACRO_STAR_EXIT) // Star Exit
    {
        for(A = 1; A <= numPlayers; A++)
        {
            auto &c = Player[A].Controls;
            c.Down = false;
            c.Drop = false;
            c.Jump = false;
            c.Left = false;
            c.Right = false;
            c.Run = false;
            c.Up = false;
            c.Start = false;
            c.AltJump = false;
            c.AltRun = false;
        }

        LevelMacroCounter++;

        if(g_config.EnableInterLevelFade && LevelMacroCounter == 235)
            g_levelScreenFader.setupFader(1, 0, 65, ScreenFader::S_FADE);

        if(LevelMacroCounter >= 300)
        {
            LevelBeatCode = 7;
            LevelMacro = LEVELMACRO_OFF;
            LevelMacroCounter = 0;
            EndLevel = true;
        }
    }
    else if(LevelMacro == LEVELMACRO_GOAL_TAPE_EXIT) // SMW Exit
    {
        for(A = 1; A <= numPlayers; A++)
        {
            auto &p = Player[A];
            auto &c = p.Controls;

            if(p.Location.X < level[p.Section].Width && !p.Dead)
            {
                c.Down = false;
                c.Drop = false;
                c.Jump = false;
                c.Left = false;
                c.Right = true;
                c.Run = false;
                c.Up = false;
                c.Start = false;
                c.AltJump = false;
                c.AltRun = false;
            }
            else
            {
                p.Location.SpeedY = -Physics.PlayerGravity;
                c.Down = false;
                c.Drop = false;
                c.Jump = false;
                c.Left = false;
                c.Right = true;
                c.Run = false;
                c.Up = false;
                c.Start = false;
                c.AltJump = false;
                c.AltRun = false;
            }
        }

        LevelMacroCounter++;

        if(g_config.EnableInterLevelFade && LevelMacroCounter == 598)
        {
            bool canTrack = (Player[1].Location.X < level[Player[1].Section].Width);
            double focusX = canTrack ?
                            Player[1].Location.X + Player[1].Location.Width / 2 :
                            level[Player[1].Section].Width;
            double focusY = Player[1].Location.Y + Player[1].Location.Height / 2;

            g_levelScreenFader.setupFader(2, 0, 65, ScreenFader::S_CIRCLE, true, focusX, focusY, 1);

            if(canTrack)
                g_levelScreenFader.setTrackedFocus(&Player[1].Location.X,
                                                   &Player[1].Location.Y,
                                                   Player[1].Location.Width / 2,
                                                   Player[1].Location.Height / 2);
        }

        if(LevelMacroCounter >= 630)
        {
            LevelBeatCode = 8;
            LevelMacro = LEVELMACRO_OFF;
            LevelMacroCounter = 0;
            EndLevel = true;
        }
    }
}

// main_config.cpp


void NPCyFix()
{
    int A = 0;
    float XnH = 0;
    float XnHfix = 0;

    for(A = 1; A <= numNPCs; A++)
    {
        XnH = NPC[A].Location.Y + NPC[A].Location.Height;
        if((int(XnH * 100) % 800) / 100 != 0)
        {
            if((int(XnH + std::abs((int(XnH * 100) % 800) / 100)) * 100) % 800 == 0)
                XnHfix = std::abs((int(XnH * 100) % 800) / 100);
            else
                XnHfix = std::abs(8 - ((int(XnH * 100) % 800) / 100));
            NPC[A].Location.Y += XnHfix;
        }
    }
}

void CheckActive()
{
    // It's useless on Emscripten as no way to check activity (or just differently)
    // and on Android as it has built-in application pauser
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
//    bool MusicPaused = false;
    bool focusLost = false;

    if(neverPause)
        return;

    if(!GameIsActive)
        return;

//    If nPlay.Online = True Then Exit Sub
    // If LevelEditor = False And TestLevel = False Then Exit Sub
    // If LevelEditor = False Then Exit Sub
    while(!XWindow::hasWindowInputFocus())
    {
        XEvents::waitEvents();
//        If LevelEditor = True Or MagicHand = True Then frmLevelWindow.vScreen(1).MousePointer = 0
        if(LevelEditor || MagicHand)
            XWindow::showCursor(0);

        resetFrameTimer();

        resetTimeBuffer();
        //keyDownEnter = false;
        //keyDownAlt = false;

        if(!focusLost)
        {
            pLogDebug("Window Focus lost");
            focusLost = true;
        }

//        if(musicPlaying && !MusicPaused)
//        {
//            MusicPaused = true;
//            SoundPauseEngine(1);
//        }

        if(!GameIsActive)
        {
            speedRun_saveStats();
            break;
        }
    }

    if(focusLost)
        pLogDebug("Window Focus got back");

//    if(MusicPaused)
//        SoundPauseEngine(0);

/* // Useless condition
    if(!noSound && MusicPaused)
    {
        if(MusicPaused)
        {
            SoundResumeAll();
            if(GameOutro == true)
                SoundResumeAll();
            else if(LevelSelect == true && GameMenu == false && LevelEditor == false)
                SoundResumeAll();
            else if(curMusic > 0)
                SoundResumeAll();
            else if(curMusic < 0)
            {
                SoundResumeAll();
                if(PSwitchStop > 0)
                {
                    // mciSendString "resume stmusic", 0, 0, 0
                    SoundResumeAll();
                }
                else
                {
                    // mciSendString "resume smusic", 0, 0, 0
                    SoundResumeAll();
                }
            }
        }
    }
    */
//    If LevelEditor = True Or MagicHand = True Then frmLevelWindow.vScreen(1).MousePointer = 99
#endif // not def __EMSCRIPTEN__
}


Location_t newLoc(double X, double Y, double Width, double Height)
{
    Location_t ret;
    ret.X = X;
    ret.Y = Y;
    ret.Width = Width;
    ret.Height = Height;
    return ret;
}

Location_t roundLoc(const Location_t &inLoc, double grid)
{
    Location_t ret = inLoc;
    ret.X = Maths::roundTo(ret.X, grid);
    ret.Y = Maths::roundTo(ret.Y, grid);
    return ret;
}

void MoreScore(int addScore, const Location_t &Loc)
{
    int mult = 0; // dummy
    MoreScore(addScore, Loc, mult);
}

void MoreScore(int addScore, const Location_t &Loc, int &Multiplier)
{
    //int oldM = 0;
    int A = 0;

    if(GameMenu || GameOutro || BattleMode)
        return;
    A = addScore + Multiplier;
    if(A == 0)
        return;
    Multiplier++;
    if(A > 13)
        A = 13;
    if(A < addScore)
        A = addScore;
    if(Multiplier > 9)
        Multiplier = 8;
    if(A > 13)
        A = 13;
    if(Points[A] <= 5)
    {
        Lives += Points[A];
        PlaySound(SFX_1up, Points[A] - 1);
    }
    else
        Score += Points[A];
    NewEffect(79, Loc);
    Effect[numEffects].Frame = A - 1;
}

void SizableBlocks()
{
    BlockIsSizable[568] = true;
    BlockIsSizable[579] = true;
    BlockIsSizable[575] = true;
    BlockIsSizable[25] = true;
    BlockIsSizable[26] = true;
    BlockIsSizable[27] = true;
    BlockIsSizable[28] = true;
    BlockIsSizable[38] = true;
    BlockIsSizable[79] = true;
    BlockIsSizable[108] = true;
    BlockIsSizable[130] = true;
    BlockIsSizable[161] = true;
    BlockIsSizable[240] = true;
    BlockIsSizable[241] = true;
    BlockIsSizable[242] = true;
    BlockIsSizable[243] = true;
    BlockIsSizable[244] = true;
    BlockIsSizable[245] = true;
    BlockIsSizable[259] = true;
    BlockIsSizable[260] = true;
    BlockIsSizable[261] = true;
    BlockIsSizable[287] = true;
    BlockIsSizable[288] = true;
    BlockIsSizable[437] = true;
    BlockIsSizable[441] = true;
    BlockIsSizable[442] = true;
    BlockIsSizable[443] = true;
    BlockIsSizable[444] = true;
    BlockIsSizable[438] = true;
    BlockIsSizable[439] = true;
    BlockIsSizable[440] = true;
    BlockIsSizable[445] = true;
}

void StartEpisode()
{
    For(A, 1, numCharacters)
    {
        SavedChar[A] = Player_t();
        SavedChar[A].Character = A;
        SavedChar[A].State = 1;
    }

    for(int i = 1; i <= maxLocalPlayers; i++)
    {
        Player[i].State = 1;
        Player[i].Mount = 0;
        // reassigned below unless something is wrong
        Player[i].Character = (i - 1) % 5 + 1;
        Player[i].HeldBonus = 0;
        Player[i].CanFly = false;
        Player[i].CanFly2 = false;
        Player[i].TailCount = 0;
        Player[i].YoshiBlue = false;
        Player[i].YoshiRed = false;
        Player[i].YoshiYellow = false;
        Player[i].Hearts = 0;
    }

    numPlayers = Controls::g_InputMethods.size();
    if(numPlayers > maxLocalPlayers)
        numPlayers = maxLocalPlayers;
    for(int i = 0; i < numPlayers; i++)
    {
        if(g_charSelect[i] != 0)
            Player[i+1].Character = g_charSelect[i];
    }

    for(int i = Controls::g_InputMethods.size() - 1; i >= numPlayers; i--)
    {
        Controls::DeleteInputMethodSlot(i);
    }

    ConnectScreen::SaveChars();

    numStars = 0;
    Coins = 0;
    Score = 0;
    Lives = 3;
    LevelSelect = true;
    GameMenu = false;
    XRender::setTargetTexture();
    XRender::clearBuffer();
    XRender::repaint();
    StopMusic();
    XEvents::doEvents();
    // Note: this causes the rendered touchscreen controller to freeze with button pressed.
    PGE_Delay(500);
    ClearGame();

    std::string wPath = SelectWorld[selWorld].WorldPath + SelectWorld[selWorld].WorldFile;

    if(numPlayers == 1 && g_recentWorld1p != wPath)
    {
        g_recentWorld1p = wPath;
        SaveConfig();
    }
    else if(numPlayers >= 2 && g_recentWorld2p != wPath)
    {
        g_recentWorld2p = wPath;
        SaveConfig();
    }

    OpenWorld(wPath);

    if(SaveSlot[selSave] >= 0)
    {
        if(!NoMap)
            StartLevel.clear();
        LoadGame();
        speedRun_loadStats();
    }

    if(WorldUnlock)
    {
        For(A, 1, numWorldPaths)
        {
            Location_t tempLocation = WorldPath[A].Location;
            {
                Location_t &l = tempLocation;
                l.X += 4;
                l.Y += 4;
                l.Width -= 8;
                l.Height -= 8;
            }

            WorldPath[A].Active = true;

            For(B, 1, numScenes)
            {
                if(CheckCollision(tempLocation, Scene[B].Location))
                    Scene[B].Active = false;
            }
        }

        For(A, 1, numWorldLevels)
            WorldLevel[A].Active = true;
    }

    SetupPlayers();

    if(!StartLevel.empty())
    {
        // TODO: why did Wohlstand disable this?
        PlaySoundMenu(SFX_LevelSelect);
        SoundPause[26] = 200;
        LevelSelect = false;

        ResetSoundFX();
        // todo: update this!
        ClearLevel();
        std::string levelPath = SelectWorld[selWorld].WorldPath + StartLevel;
        if(!OpenLevel(levelPath))
        {
            MessageText = fmt::format_ne("ERROR: Can't open \"{0}\": file doesn't exist or corrupted.", StartLevel);
            PauseGame(PauseCode::Message);
            ErrorQuit = true;
        }
        GameThing(1000, 3);
    }
}

void StartBattleMode()
{
    int A = 0;
    Player_t blankPlayer;

    for(A = 1; A <= numCharacters; A++)
    {
        SavedChar[A] = blankPlayer;
        SavedChar[A].Character = A;
        SavedChar[A].State = 1;
    }

    for(int i = 1; i <= maxLocalPlayers; i++)
    {
        Player[i].State = 2;
        Player[i].Mount = 0;
        // reassigned below unless something is wrong
        Player[i].Character = (i - 1) % 5 + 1;
        Player[i].HeldBonus = 0;
        Player[i].CanFly = false;
        Player[i].CanFly2 = false;
        Player[i].TailCount = 0;
        Player[i].YoshiBlue = false;
        Player[i].YoshiRed = false;
        Player[i].YoshiYellow = false;
        Player[i].Hearts = 2;
    }

    numPlayers = Controls::g_InputMethods.size();
    if(numPlayers > maxLocalPlayers)
        numPlayers = maxLocalPlayers;
    for(int i = 0; i < numPlayers; i++)
    {
        if(g_charSelect[i] != 0)
            Player[i+1].Character = g_charSelect[i];
    }

    for(int i = Controls::g_InputMethods.size() - 1; i >= numPlayers; i--)
    {
        Controls::DeleteInputMethodSlot(i);
    }

    numStars = 0;
    Coins = 0;
    Score = 0;
    Lives = 99;
    BattleLives[1] = 3;
    BattleLives[2] = 3;
    LevelSelect = false;
    GameMenu = false;
    BattleMode = true;
    XRender::setTargetTexture();
    XRender::clearBuffer();
    XRender::repaint();
    StopMusic();
    XEvents::doEvents();
    PGE_Delay(500);
    lunaReset();
    ResetSoundFX();
    ClearLevel();

    if(NumSelectBattle <= 1)
    {
        MessageText = "Can't start battle because of no levels available";
        PauseGame(PauseCode::Message);
        ErrorQuit = true;
    }
    else
    {
        if(selWorld == 1)
            selWorld = (iRand(NumSelectBattle - 1)) + 2;
    }

    std::string levelPath = SelectBattle[selWorld].WorldPath + SelectBattle[selWorld].WorldFile;
    if(!OpenLevel(levelPath))
    {
        MessageText = fmt::format_ne("ERROR: Can't open \"{0}\": file doesn't exist or corrupted.", SelectBattle[selWorld].WorldFile);
        PauseGame(PauseCode::Message);
        ErrorQuit = true;
    }
    SetupPlayers();

    BattleIntro = 150;
    BattleWinner = 0;
    BattleOutro = 0;
}

void DeleteSave(int world, int save)
{
    auto &w = SelectWorld[world];
    std::vector<std::string> deleteList;

#define AddFile(f) \
    deleteList.push_back(makeGameSavePath(w.WorldPath, \
                                          w.WorldFile,\
                                          fmt::format_ne(f, save)));
#define AddFileW(f) \
    deleteList.push_back(w.WorldPath + fmt::format_ne(f, save));

    AddFile("save{0}.savx");
    AddFile("timers{0}.ini");
    AddFile("demos-{0}.dmo");
    // Old gamesaves
    AddFileW("save{0}.savx");
    AddFileW("save{0}.sav");

    // Clear all files in list
    for(auto &s : deleteList)
    {
        if(Files::fileExists(s))
            Files::deleteFile(s);
    }

#undef AddFile
#undef AddFileW

#ifdef __EMSCRIPTEN__
    AppPathManager::syncFs();
#endif
}

static void copySaveFile(const SelectWorld_t& w, const char*file_mask, int src, int dst)
{
    std::string filePathSrc = makeGameSavePath(w.WorldPath,
                                               w.WorldFile,
                                               fmt::format_ne(file_mask, src));
    std::string filePathDst = makeGameSavePath(w.WorldPath,
                                               w.WorldFile,
                                               fmt::format_ne(file_mask, dst));
    Files::copyFile(filePathDst, filePathSrc, true);
}

void CopySave(int world, int src, int dst)
{
    auto &w = SelectWorld[world];

    std::string savePathSrc = makeGameSavePath(w.WorldPath,
                                               w.WorldFile,
                                               fmt::format_ne("save{0}.savx", src));
    std::string savePathDst = makeGameSavePath(w.WorldPath,
                                               w.WorldFile,
                                               fmt::format_ne("save{0}.savx", dst));

    if(!Files::fileExists(savePathSrc)) // Attempt to import an old game-save from the episode directory
    {
        std::string savePathOld     = w.WorldPath + fmt::format_ne("save{0}.savx", src);
        std::string savePathAncient = w.WorldPath + fmt::format_ne("save{0}.sav", src);

        GamesaveData sav;
        bool succ = false;

        if(Files::fileExists(savePathOld))
            succ = FileFormats::ReadExtendedSaveFileF(savePathOld, sav);
        else if(Files::fileExists(savePathAncient))
            succ = FileFormats::ReadSMBX64SavFileF(savePathAncient, sav);

        if(succ)
            FileFormats::WriteExtendedSaveFileF(savePathSrc, sav);
    }

    Files::copyFile(savePathDst, savePathSrc, true);

    copySaveFile(w, "timers{0}.ini", src, dst);
    copySaveFile(w, "demos-{0}.dmo", src, dst);

#ifdef __EMSCRIPTEN__
    AppPathManager::syncFs();
#endif
}
