/*
 * TheXTech - A platform game engine ported from old source code for VB6
 *
 * Copyright (c) 2009-2011 Andrew Spinks, original VB6 code
 * Copyright (c) 2020-2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "../globals.h"
#include "../game_main.h"


void SetupPlayerFrames()
{
    For(A, 1, maxPlayerFrames)
    {
        MarioFrameX[A] = 0;
        MarioFrameY[A] = 0;
        LuigiFrameX[A] = 0;
        LuigiFrameY[A] = 0;
        PeachFrameX[A] = 0;
        PeachFrameY[A] = 0;
        ToadFrameX[A] = 0;
        ToadFrameY[A] = 0;
    }

    LinkFrameY[101] = -8;
    LinkFrameY[102] = -8;
    LinkFrameY[103] = -8;
    LinkFrameY[104] = -6;
    LinkFrameY[105] = -8;
    LinkFrameY[106] = -8;
    LinkFrameY[107] = -4;
    LinkFrameY[108] = -6;
    LinkFrameY[109] = -4;
    LinkFrameY[110] = -16;
    LinkFrameY[111] = -2;
    LinkFrameY[99] = -8;
    LinkFrameY[98] = -8;
    LinkFrameY[97] = -8;
    LinkFrameY[96] = -6;
    LinkFrameY[95] = -8;
    LinkFrameY[94] = -8;
    LinkFrameY[93] = -4;
    LinkFrameY[92] = -6;
    LinkFrameY[91] = -4;
    LinkFrameY[90] = -16;
    LinkFrameY[89] = -2;
    For(A, 51, 149)
    {
        LinkFrameX[A] = -4;
    }
    LinkFrameX[106] = -18;
    LinkFrameX[93] = -36;
    LinkFrameX[92] = -36;

    For(A, 51, 649)
    {
        LinkFrameX[A + 100] = LinkFrameX[A];
        LinkFrameY[A + 100] = LinkFrameY[A];
    }

        LinkFrameX[512] = -4;
        LinkFrameY[512] = -8;
        LinkFrameX[488] = -4;
        LinkFrameY[488] = -8;

    For(A, 51, 149)
    {
        ToadFrameY[A] = -6;
        ToadFrameX[A] = -2;
    }
    ToadFrameY[107] = -2;
    ToadFrameY[127] = -2;

    ToadFrameX[127] = -4;
    ToadFrameX[73] = -4;

    ToadFrameX[115] = -4;
    ToadFrameX[85] = -4;
    ToadFrameY[93] = -2;
    ToadFrameY[73] = -2;
    ToadFrameY[122] = -20;
    ToadFrameY[123] = -12;

    ToadFrameY[78] = -20;
    ToadFrameY[77] = -12;

    For(A, 151, 349)
    {
        ToadFrameY[A] = 2;
        ToadFrameX[A] = -4;
    }

    For(A, 151, 349)
    {
        ToadFrameY[A] = ToadFrameY[A] - 4;
    }

    ToadFrameY[227] = 0;
    ToadFrameY[207] = 0;
    ToadFrameY[173] = 0;
    ToadFrameY[193] = 0;
    ToadFrameY[327] = 0;
    ToadFrameY[307] = 0;
    ToadFrameY[273] = 0;
    ToadFrameY[293] = 0;
    ToadFrameY[322] = -22;
    ToadFrameY[278] = -22;
    ToadFrameY[222] = -22;
    ToadFrameY[178] = -22;
    ToadFrameY[323] = -16;
    ToadFrameY[277] = -16;
    ToadFrameY[223] = -16;
    ToadFrameY[177] = -16;

    ToadFrameX[294] = -4;
    ToadFrameX[194] = -4;
    ToadFrameX[306] = -6;
    ToadFrameX[206] = -6;
    ToadFrameX[106] = -4;

    PeachFrameY[101] = -4;
    PeachFrameY[102] = -4;
    PeachFrameY[103] = -4;
    PeachFrameY[104] = -4;
    PeachFrameY[108] = -4;
    PeachFrameY[109] = -4;
    PeachFrameY[110] = -4;
    PeachFrameY[127] = -2;
    PeachFrameY[122] = -16;
    PeachFrameY[78] = -16;
    PeachFrameY[99] = -4;
    PeachFrameY[98] = -4;
    PeachFrameY[97] = -4;
    PeachFrameY[96] = -4;
    PeachFrameY[92] = -4;
    PeachFrameY[91] = -4;
    PeachFrameY[90] = -4;
    PeachFrameY[73] = -2;
    PeachFrameX[101] = -2;
    PeachFrameX[102] = -2;
    PeachFrameX[103] = -2;
    PeachFrameX[104] = -2;
    PeachFrameX[108] = -2;
    PeachFrameX[109] = -2;
    PeachFrameX[110] = -2;
    PeachFrameX[107] = -2;
    PeachFrameX[93] = -2;
    PeachFrameX[127] = -4;
    PeachFrameX[99] = 0;
    PeachFrameX[98] = 0;
    PeachFrameX[97] = 0;
    PeachFrameX[96] = 0;
    PeachFrameX[92] = 0;
    PeachFrameX[91] = 0;
    PeachFrameX[90] = 0;
    PeachFrameX[73] = -4;

    PeachFrameY[201] = -2;
    PeachFrameY[202] = -2;
    PeachFrameY[203] = -2;
    PeachFrameY[204] = -2;
    PeachFrameY[208] = -2;
    PeachFrameY[209] = -2;
    PeachFrameY[210] = -2;
    PeachFrameY[215] = -2;
    PeachFrameY[185] = -2;
    PeachFrameY[222] = -30;
    PeachFrameY[178] = -30;
    PeachFrameY[199] = -2;
    PeachFrameY[198] = -2;
    PeachFrameY[197] = -2;
    PeachFrameY[196] = -2;
    PeachFrameY[192] = -2;
    PeachFrameY[191] = -2;
    PeachFrameY[190] = -2;
    PeachFrameX[201] = -4;
    PeachFrameX[202] = -4;
    PeachFrameX[203] = -4;
    PeachFrameX[204] = -4;
    PeachFrameX[207] = -4;
    PeachFrameX[208] = -4;
    PeachFrameX[209] = -4;
    PeachFrameX[210] = -4;
    PeachFrameX[215] = -4;
    PeachFrameX[185] = -4;
    PeachFrameX[227] = -4;
    PeachFrameX[199] = -4;
    PeachFrameX[198] = -4;
    PeachFrameX[197] = -4;
    PeachFrameX[196] = -4;
    PeachFrameX[193] = -4;
    PeachFrameX[192] = -4;
    PeachFrameX[191] = -4;
    PeachFrameX[190] = -4;
    PeachFrameX[173] = -4;
    PeachFrameY[223] = -30;
    PeachFrameY[177] = -30;
    PeachFrameY[206] = -2;
    PeachFrameY[194] = -2;
    PeachFrameX[195] = PeachFrameX[196];
    PeachFrameY[195] = PeachFrameY[196];
    PeachFrameX[205] = PeachFrameX[204];
    PeachFrameY[205] = PeachFrameY[204];
    PeachFrameX[206] = -8;
    PeachFrameX[194] = 0;
    PeachFrameX[213] = -4;
    PeachFrameX[187] = -4;
    PeachFrameY[213] = -2;
    PeachFrameY[187] = -2;
    PeachFrameY[123] = -16;
    PeachFrameY[77] = -16;
    PeachFrameY[122] = -2;
    PeachFrameY[78] = -22;
    PeachFrameY[106] = -4;
    PeachFrameY[94] = -4;
    PeachFrameX[95] = PeachFrameX[96];
    PeachFrameY[95] = PeachFrameY[96];
    PeachFrameX[105] = PeachFrameX[104];
    PeachFrameY[105] = PeachFrameY[104];
    PeachFrameX[106] = -4;
    PeachFrameX[94] = 0;
    PeachFrameX[113] = -2;
    PeachFrameX[115] = -2;
    PeachFrameX[85] = -2;
    PeachFrameY[115] = -4;
    PeachFrameY[85] = -4;
    PeachFrameX[87] = -2;
    PeachFrameY[113] = -4;
    PeachFrameY[87] = -4;
    PeachFrameY[75] = -2;
    PeachFrameY[74] = -2;
    PeachFrameY[125] = -2;
    PeachFrameY[126] = -2;
    PeachFrameY[123] = -16;
    PeachFrameY[122] = -22;
    For(A, 151, 249)
    {
        PeachFrameX[A + 100] = PeachFrameX[A];
        PeachFrameY[A + 100] = PeachFrameY[A];
    }
    PeachFrameX[312] = PeachFrameX[310];
    PeachFrameX[311] = PeachFrameX[310];
    PeachFrameX[288] = PeachFrameX[290];
    PeachFrameX[289] = PeachFrameX[290];
    PeachFrameY[312] = PeachFrameY[310];
    PeachFrameY[311] = PeachFrameY[310];
    PeachFrameY[288] = PeachFrameY[290];
    PeachFrameY[289] = PeachFrameY[290];




    MarioFrameY[96] = 0;
    MarioFrameX[97] = -4;
    MarioFrameX[98] = -2;
    MarioFrameY[98] = 0;
    MarioFrameY[99] = 2;
    MarioFrameY[101] = 2;
    MarioFrameX[102] = -4;
    MarioFrameY[102] = 0;
    MarioFrameX[103] = -4;
    MarioFrameY[104] = 0;
    MarioFrameX[105] = -2;
    MarioFrameX[106] = -4;
    MarioFrameY[190] = 2;
    MarioFrameY[191] = 2;
    MarioFrameY[192] = 2;
    MarioFrameY[193] = -4;
    MarioFrameX[194] = -2;
    MarioFrameY[194] = 0;
    MarioFrameX[195] = -2;
    MarioFrameX[196] = -2;
    MarioFrameX[197] = -2;
    MarioFrameY[197] = 2;
    MarioFrameX[198] = -2;
    MarioFrameY[198] = 2;
    MarioFrameY[199] = 2;
    MarioFrameY[201] = 2;
    MarioFrameY[202] = 2;
    MarioFrameX[202] = -2;
    MarioFrameY[203] = 2;
    MarioFrameX[203] = -2;
    MarioFrameX[204] = -2;
    MarioFrameX[205] = -2;
    MarioFrameX[206] = -2;
    MarioFrameY[206] = 0;
    MarioFrameY[207] = -4;
    MarioFrameY[208] = 2;
    MarioFrameY[209] = 2;
    MarioFrameY[210] = 2;
    MarioFrameX[209] = -2;
    MarioFrameX[210] = -4;
    MarioFrameY[288] = 2;
    MarioFrameY[289] = 2;
    MarioFrameY[290] = 2;
    MarioFrameY[291] = 2;
    MarioFrameY[292] = 2;
    MarioFrameY[293] = -4;
    MarioFrameX[294] = -2;
    MarioFrameY[294] = 0;
    MarioFrameX[295] = -2;
    MarioFrameX[296] = -2;
    MarioFrameX[297] = -2;
    MarioFrameY[297] = 2;
    MarioFrameX[298] = -2;
    MarioFrameY[298] = 2;
    MarioFrameY[299] = 2;
    MarioFrameY[301] = 2;
    MarioFrameY[302] = 2;
    MarioFrameX[302] = -2;
    MarioFrameY[303] = 2;
    MarioFrameX[303] = -2;
    MarioFrameX[304] = -2;
    MarioFrameX[305] = -2;
    MarioFrameX[306] = -2;
    MarioFrameY[306] = 0;
    MarioFrameY[307] = -4;
    MarioFrameY[308] = 2;
    MarioFrameY[309] = 2;
    MarioFrameY[310] = 2;
    MarioFrameX[309] = -2;
    MarioFrameX[310] = -4;
    MarioFrameY[311] = 2;
    MarioFrameY[312] = 2;
    MarioFrameX[382] = -4;
    MarioFrameX[383] = -4;
    MarioFrameX[384] = -4;
    MarioFrameY[385] = -2;
    MarioFrameX[386] = -14;
    MarioFrameX[389] = -2;
    MarioFrameY[393] = -4;
    MarioFrameX[394] = -2;
    MarioFrameY[394] = -4;
    MarioFrameX[395] = -2;
    MarioFrameX[396] = -2;
    MarioFrameX[397] = -2;
    MarioFrameX[398] = -2;
    MarioFrameX[401] = -14;
    MarioFrameX[402] = -14;
    MarioFrameX[403] = -16;
    MarioFrameX[404] = -16;
    MarioFrameX[405] = -16;
    MarioFrameY[406] = -4;
    MarioFrameX[407] = -14;
    MarioFrameY[407] = -4;
    MarioFrameX[408] = -14;
    MarioFrameX[409] = -16;
    MarioFrameX[410] = -18;
    MarioFrameX[411] = -14;
    MarioFrameX[412] = -18;
    MarioFrameX[413] = -4;
    MarioFrameX[414] = -4;
    MarioFrameX[415] = -4;
    MarioFrameY[415] = -2;
    MarioFrameX[416] = -16;
    MarioFrameX[417] = -16;
    MarioFrameX[418] = -16;
    MarioFrameX[419] = -16;
    MarioFrameX[420] = -16;
    MarioFrameX[421] = -16;
    LuigiFrameY[96] = 0;
    LuigiFrameX[97] = -4;
    LuigiFrameX[98] = -2;
    LuigiFrameY[98] = 0;
    LuigiFrameY[99] = 2;
    LuigiFrameY[101] = 2;
    LuigiFrameX[102] = -4;
    LuigiFrameY[102] = 0;
    LuigiFrameX[103] = -4;
    LuigiFrameY[104] = 0;
    LuigiFrameX[105] = -2;
    LuigiFrameX[106] = -4;
    LuigiFrameY[190] = 2;
    LuigiFrameY[191] = 2;
    LuigiFrameY[192] = 2;
    LuigiFrameY[193] = -6;
    LuigiFrameX[194] = -2;
    LuigiFrameY[194] = 0;
    LuigiFrameX[195] = -2;
    LuigiFrameX[196] = -2;
    LuigiFrameX[197] = -2;
    LuigiFrameY[197] = 2;
    LuigiFrameX[198] = -2;
    LuigiFrameY[198] = 2;
    LuigiFrameY[199] = 2;
    LuigiFrameY[201] = 2;
    LuigiFrameY[202] = 2;
    LuigiFrameX[202] = -2;
    LuigiFrameY[203] = 2;
    LuigiFrameX[203] = -2;
    LuigiFrameX[204] = -2;
    LuigiFrameX[205] = -2;
    LuigiFrameX[206] = -2;
    LuigiFrameY[206] = 0;
    LuigiFrameY[207] = -6;
    LuigiFrameY[208] = 2;
    LuigiFrameY[209] = 2;
    LuigiFrameY[210] = 2;
    LuigiFrameX[209] = -2;
    LuigiFrameX[210] = -4;
    LuigiFrameY[288] = 2;
    LuigiFrameY[289] = 2;
    LuigiFrameY[290] = 2;
    LuigiFrameY[291] = 2;
    LuigiFrameY[292] = 2;
    LuigiFrameY[293] = -6;
    LuigiFrameX[294] = -2;
    LuigiFrameY[294] = 0;
    LuigiFrameX[295] = -2;
    LuigiFrameX[296] = -2;
    LuigiFrameX[297] = -2;
    LuigiFrameY[297] = 2;
    LuigiFrameX[298] = -2;
    LuigiFrameY[298] = 2;
    LuigiFrameY[299] = 2;
    LuigiFrameY[301] = 2;
    LuigiFrameY[302] = 2;
    LuigiFrameX[302] = -2;
    LuigiFrameY[303] = 2;
    LuigiFrameX[303] = -2;
    LuigiFrameX[304] = -2;
    LuigiFrameX[305] = -2;
    LuigiFrameX[306] = -2;
    LuigiFrameY[306] = 0;
    LuigiFrameY[307] = -6;
    LuigiFrameY[308] = 2;
    LuigiFrameY[309] = 2;
    LuigiFrameY[310] = 2;
    LuigiFrameX[309] = -2;
    LuigiFrameX[310] = -4;
    LuigiFrameY[311] = 2;
    LuigiFrameY[312] = 2;
    LuigiFrameX[382] = -4;
    LuigiFrameX[383] = -4;
    LuigiFrameX[384] = -2;
    LuigiFrameX[386] = -14;
    LuigiFrameX[389] = -2;
    LuigiFrameY[393] = -4;
    LuigiFrameX[394] = -2;
    LuigiFrameY[394] = 0;
    LuigiFrameX[395] = -2;
    LuigiFrameX[396] = -2;
    LuigiFrameX[397] = -2;
    LuigiFrameX[398] = -2;
    LuigiFrameX[401] = -14;
    LuigiFrameX[402] = -14;
    LuigiFrameX[403] = -16;
    LuigiFrameX[404] = -16;
    LuigiFrameX[405] = -16;
    LuigiFrameY[406] = 0;
    LuigiFrameX[407] = -14;
    LuigiFrameY[407] = -4;
    LuigiFrameX[408] = -14;
    LuigiFrameX[409] = -16;
    LuigiFrameX[410] = -18;
    LuigiFrameX[411] = -14;
    LuigiFrameX[412] = -18;
    LuigiFrameX[413] = -4;
    LuigiFrameX[414] = -4;
    LuigiFrameX[415] = -4;
    LuigiFrameX[416] = -16;
    LuigiFrameX[417] = -16;
    LuigiFrameX[418] = -16;
    LuigiFrameX[419] = -16;
    LuigiFrameX[420] = -18;
    LuigiFrameX[421] = -16;


    For(A, 150, maxPlayerFrames) // Adjust the players frames to their new sizes
    {
        MarioFrameX[A] = MarioFrameX[A] - 2;
        LuigiFrameX[A] = LuigiFrameX[A] - 2;
        LuigiFrameY[A] = LuigiFrameY[A] - 2;
    }
    LuigiFrameY[101] = LuigiFrameY[101] - 2;
    LuigiFrameY[102] = LuigiFrameY[102] - 2;
    LuigiFrameY[105] = LuigiFrameY[105] - 2;
    LuigiFrameY[106] = LuigiFrameY[106] - 2;
    LuigiFrameY[99] = LuigiFrameY[99] - 2;
    LuigiFrameY[98] = LuigiFrameY[98] - 2;
    LuigiFrameY[95] = LuigiFrameY[95] - 2;
    LuigiFrameY[94] = LuigiFrameY[94] - 2;

// Yoshi Frames
    MarioFrameX[130] = -2 - 4;
    MarioFrameX[70] = 6 - 4;
    MarioFrameY[130] = 18;
    MarioFrameY[70] = 18;
    MarioFrameX[230] = -4 - 4;
    MarioFrameX[170] = 4 - 4;
    MarioFrameX[330] = -4 - 4;
    MarioFrameX[270] = 4 - 4;
    MarioFrameX[430] = -20 - 4;
    MarioFrameX[370] = 4 - 4;
    MarioFrameY[430] = -2;
    MarioFrameY[370] = -2;
    LuigiFrameX[130] = -2 - 4;
    LuigiFrameX[70] = 6 - 4;
    LuigiFrameY[130] = 16;
    LuigiFrameY[70] = 16;
    LuigiFrameY[230] = -4;
    LuigiFrameY[170] = -4;
    LuigiFrameY[330] = -4;
    LuigiFrameY[270] = -4;
    LuigiFrameY[430] = -6;
    LuigiFrameY[370] = -6;
    LuigiFrameX[230] = -6 - 4;
    LuigiFrameX[170] = 4 - 4;
    LuigiFrameX[330] = -6 - 4;
    LuigiFrameX[270] = 4 - 4;
    LuigiFrameX[430] = -20 - 4;
    LuigiFrameX[370] = 4 - 4;


    MarioFrameX[131] = -2 - 2;
    MarioFrameX[69] = 6 - 4;
    MarioFrameY[131] = 22;
    MarioFrameY[69] = 22;
    MarioFrameX[231] = -4 - 3;
    MarioFrameX[169] = 4 - 6;
    MarioFrameY[231] = 8;
    MarioFrameY[169] = 8;
    MarioFrameX[331] = -4 - 2;
    MarioFrameX[269] = 4 - 6;
    MarioFrameY[331] = 8;
    MarioFrameY[269] = 8;
    MarioFrameX[431] = -20;
    MarioFrameX[369] = 4 - 6;
    MarioFrameY[431] = 6;
    MarioFrameY[369] = 6;
    LuigiFrameX[131] = -2 - 2;
    LuigiFrameX[69] = 6 - 4;
    LuigiFrameY[131] = 22;
    LuigiFrameY[69] = 22;
    LuigiFrameX[231] = -6;
    LuigiFrameX[169] = 4 - 6;
    LuigiFrameY[231] = 4;
    LuigiFrameY[169] = 4;
    LuigiFrameX[331] = -6;
    LuigiFrameX[269] = 4 - 6;
    LuigiFrameY[331] = 4;
    LuigiFrameY[269] = 4;
    LuigiFrameX[431] = -20;
    LuigiFrameX[369] = 4 - 6;
    LuigiFrameY[431] = 2;
    LuigiFrameY[369] = 2;

// Facing Frames
    MarioFrameX[113] = -2;
    MarioFrameY[113] = 2;
    MarioFrameX[115] = -2;
    MarioFrameY[115] = 2;
    MarioFrameX[87] = MarioFrameX[113];
    MarioFrameY[87] = MarioFrameY[113];
    MarioFrameX[85] = MarioFrameX[115];
    MarioFrameY[85] = MarioFrameY[115];
    MarioFrameX[213] = -4;
    MarioFrameY[213] = 2;
    MarioFrameX[215] = -4;
    MarioFrameY[215] = 2;
    MarioFrameX[187] = MarioFrameX[213];
    MarioFrameY[187] = MarioFrameY[213];
    MarioFrameX[185] = MarioFrameX[215];
    MarioFrameY[185] = MarioFrameY[215];
    MarioFrameX[313] = -4;
    MarioFrameY[313] = 2;
    MarioFrameX[315] = -4;
    MarioFrameY[315] = 2;
    MarioFrameX[287] = MarioFrameX[313];
    MarioFrameY[287] = MarioFrameY[313];
    MarioFrameX[285] = MarioFrameX[315];
    MarioFrameY[285] = MarioFrameY[315];
    MarioFrameX[413] = -4;
    MarioFrameY[413] = 0;
    MarioFrameX[415] = -4;
    MarioFrameY[415] = -2;
    MarioFrameX[387] = MarioFrameX[413];
    MarioFrameY[387] = MarioFrameY[413];
    MarioFrameX[385] = MarioFrameX[415];
    MarioFrameY[385] = MarioFrameY[415];
    LuigiFrameX[113] = -2;
    LuigiFrameY[113] = 2;
    LuigiFrameX[115] = -2;
    LuigiFrameY[115] = 2;
    LuigiFrameX[87] = LuigiFrameX[113];
    LuigiFrameY[87] = LuigiFrameY[113];
    LuigiFrameX[85] = LuigiFrameX[115];
    LuigiFrameY[85] = LuigiFrameY[115];
    LuigiFrameX[213] = -4;
    LuigiFrameY[213] = 2;
    LuigiFrameX[215] = -4;
    LuigiFrameY[215] = 2;
    LuigiFrameX[187] = LuigiFrameX[213];
    LuigiFrameY[187] = LuigiFrameY[213];
    LuigiFrameX[185] = LuigiFrameX[215];
    LuigiFrameY[185] = LuigiFrameY[215];
    LuigiFrameX[313] = -4;
    LuigiFrameY[313] = 2;
    LuigiFrameX[315] = -4;
    LuigiFrameY[315] = 2;
    LuigiFrameX[287] = LuigiFrameX[313];
    LuigiFrameY[287] = LuigiFrameY[313];
    LuigiFrameX[285] = LuigiFrameX[315];
    LuigiFrameY[285] = LuigiFrameY[315];
    LuigiFrameX[413] = -4;
    LuigiFrameY[413] = 0;
    LuigiFrameX[415] = -4;
    LuigiFrameY[415] = -2;
    LuigiFrameX[387] = LuigiFrameX[413];
    LuigiFrameY[387] = LuigiFrameY[413];
    LuigiFrameX[385] = LuigiFrameX[415];
    LuigiFrameY[385] = LuigiFrameY[415];
    LuigiFrameX[113] = 0; // -2
    LuigiFrameY[113] = 0;
    LuigiFrameX[115] = 0; // -2
    LuigiFrameY[115] = 0;
    LuigiFrameX[87] = LuigiFrameX[113];
    LuigiFrameY[87] = LuigiFrameY[113];
    LuigiFrameX[85] = LuigiFrameX[115];
    LuigiFrameY[85] = LuigiFrameY[115];
    LuigiFrameX[213] = -4;
    LuigiFrameY[213] = 0;
    LuigiFrameX[215] = -4;
    LuigiFrameY[215] = 0;
    LuigiFrameX[187] = LuigiFrameX[213];
    LuigiFrameY[187] = LuigiFrameY[213];
    LuigiFrameX[185] = LuigiFrameX[215];
    LuigiFrameY[185] = LuigiFrameY[215];
    LuigiFrameX[313] = -4;
    LuigiFrameY[313] = 0;
    LuigiFrameX[315] = -4;
    LuigiFrameY[315] = 0;
    LuigiFrameX[287] = LuigiFrameX[313];
    LuigiFrameY[287] = LuigiFrameY[313];
    LuigiFrameX[285] = LuigiFrameX[315];
    LuigiFrameY[285] = LuigiFrameY[315];
    LuigiFrameX[413] = -4;
    LuigiFrameY[413] = -2;
    LuigiFrameX[415] = -4;
    LuigiFrameY[415] = -2;
    LuigiFrameX[387] = LuigiFrameX[413];
    LuigiFrameY[387] = LuigiFrameY[413];
    LuigiFrameX[385] = LuigiFrameX[415];
    LuigiFrameY[385] = LuigiFrameY[415];


    For(A, 450, 550)
    {
        MarioFrameX[A] = MarioFrameX[A - 100];
        MarioFrameY[A] = MarioFrameY[A - 100];
        LuigiFrameX[A] = LuigiFrameX[A - 100];
        LuigiFrameY[A] = LuigiFrameY[A - 100];
        MarioFrameX[A + 100] = MarioFrameX[A - 200];
        MarioFrameY[A + 100] = MarioFrameY[A - 200];
        LuigiFrameX[A + 100] = LuigiFrameX[A - 200];
        LuigiFrameY[A + 100] = LuigiFrameY[A - 200];
    }
    MarioFrameY[508] = MarioFrameY[508] - 2;
    MarioFrameY[509] = MarioFrameY[509] - 2;
    MarioFrameY[510] = MarioFrameY[510] - 2;
    MarioFrameY[492] = MarioFrameY[492] - 2;
    MarioFrameY[491] = MarioFrameY[491] - 2;
    MarioFrameY[490] = MarioFrameY[490] - 2;
    MarioFrameY[501] = -2;
    MarioFrameY[499] = -2;
    MarioFrameY[502] = -2;
    MarioFrameY[498] = -2;
    MarioFrameY[503] = 0;
    MarioFrameY[497] = 0;
    MarioFrameY[512] = -2;
    MarioFrameY[513] = -2;
    MarioFrameY[514] = -2;
    MarioFrameY[515] = 0;
    MarioFrameY[488] = -2;
    MarioFrameY[487] = -2;
    MarioFrameY[486] = -2;
    MarioFrameY[485] = 0;
    MarioFrameX[513] = -6;
    MarioFrameX[514] = -6;
    MarioFrameX[515] = -6;
    MarioFrameX[485] = -2;
    MarioFrameX[487] = -2;
    MarioFrameX[518] = -16;
    MarioFrameX[517] = -16;
    MarioFrameX[516] = -16;
    MarioFrameY[530] = MarioFrameY[530] - 2;
    MarioFrameY[531] = MarioFrameY[531] - 2;
    MarioFrameY[470] = MarioFrameY[470] - 2;
    MarioFrameY[569] = MarioFrameY[469] - 2;
    MarioFrameY[500] = -2;
    MarioFrameX[500] = -4;
    LuigiFrameY[500] = 4;
    LuigiFrameX[500] = -4;
    MarioFrameX[513] = -4;
    MarioFrameX[487] = -4;
    MarioFrameX[601] = -6;
    MarioFrameY[601] = 0;
    MarioFrameY[599] = 0;
    MarioFrameY[602] = 0;
    MarioFrameY[603] = 0;
    MarioFrameY[598] = 0;
    MarioFrameY[597] = 0;
    MarioFrameY[604] = -2;
    MarioFrameY[605] = -2;
    MarioFrameY[596] = -2;
    MarioFrameY[595] = -2;
    MarioFrameY[613] = -2;
    MarioFrameY[587] = -2;
    MarioFrameY[615] = 0;
    MarioFrameY[585] = 0;
    MarioFrameX[608] = -6;
    MarioFrameY[608] = 0;
    MarioFrameY[592] = 0;
    MarioFrameX[609] = -6;
    MarioFrameY[609] = 0;
    MarioFrameY[591] = 0;
    MarioFrameY[610] = 0;
    MarioFrameY[590] = 0;
    MarioFrameY[611] = 0;
    MarioFrameX[611] = -6;
    MarioFrameY[589] = 0;
    MarioFrameY[612] = 0;
    MarioFrameX[612] = -6;
    MarioFrameY[588] = 0;
    MarioFrameY[613] = 0;
    MarioFrameY[587] = 0;
    MarioFrameY[630] = -2;
    MarioFrameY[570] = -2;
    MarioFrameY[631] = 6;
    MarioFrameY[569] = 6;
    MarioFrameY[469] = 4;
    MarioFrameY[607] = 0;
    MarioFrameY[593] = 0;
    MarioFrameX[593] = -6;
    LuigiFrameX[601] = -6;
    LuigiFrameX[608] = -6;
    LuigiFrameX[609] = -6;
    LuigiFrameX[611] = -6;
    LuigiFrameX[612] = -6;
    LuigiFrameX[630] = -12;
    LuigiFrameY[607] = 0;
    LuigiFrameY[593] = 0;

    MarioFrameX[225] = -4;
    MarioFrameX[226] = -4;
    MarioFrameX[175] = -4;
    MarioFrameX[174] = -4;
    MarioFrameX[325] = -4;
    MarioFrameX[326] = -4;
    MarioFrameX[275] = -4;
    MarioFrameX[274] = -4;
    MarioFrameX[425] = -4;
    MarioFrameX[426] = -4;
    MarioFrameX[375] = -4;
    MarioFrameX[374] = -4;
    MarioFrameX[525] = -4;
    MarioFrameX[526] = -4;
    MarioFrameX[475] = -4;
    MarioFrameX[474] = -4;
    MarioFrameX[625] = -4;
    MarioFrameX[626] = -4;
    MarioFrameX[575] = -4;
    MarioFrameX[574] = -4;
    MarioFrameX[125] = -2;
    MarioFrameX[126] = -2;
    MarioFrameX[75] = -2;
    MarioFrameX[74] = -2;
    LuigiFrameX[225] = -4;
    LuigiFrameX[226] = -4;
    LuigiFrameX[175] = -4;
    LuigiFrameX[174] = -4;
    LuigiFrameX[325] = -4;
    LuigiFrameX[326] = -4;
    LuigiFrameX[275] = -4;
    LuigiFrameX[274] = -4;
    LuigiFrameX[425] = -4;
    LuigiFrameX[426] = -4;
    LuigiFrameX[375] = -4;
    LuigiFrameX[374] = -4;
    LuigiFrameX[525] = -4;
    LuigiFrameX[526] = -4;
    LuigiFrameX[475] = -4;
    LuigiFrameX[474] = -4;
    LuigiFrameX[625] = -4;
    LuigiFrameX[626] = -4;
    LuigiFrameX[575] = -4;
    LuigiFrameX[574] = -4;

    LuigiFrameX[124] = -4;
    LuigiFrameX[76] = -4;
    LuigiFrameX[224] = -4;
    LuigiFrameX[176] = -4;
    LuigiFrameX[324] = -4;
    LuigiFrameX[276] = -4;
    LuigiFrameX[424] = -4;
    LuigiFrameX[376] = -4;
    LuigiFrameX[524] = -4;
    LuigiFrameX[476] = -4;
    LuigiFrameX[624] = -4;
    LuigiFrameX[576] = -4;

    LuigiFrameY[224] = 2;
    LuigiFrameY[176] = 2;
    LuigiFrameY[324] = 2;
    LuigiFrameY[276] = 2;
    LuigiFrameY[424] = 0;
    LuigiFrameY[376] = 0;
    LuigiFrameY[524] = 0;
    LuigiFrameY[476] = 0;
    LuigiFrameY[624] = 2;
    LuigiFrameY[576] = 2;



    MarioFrameX[124] = -4;
    MarioFrameX[76] = -2;
    MarioFrameX[224] = -4;
    MarioFrameX[176] = -4;
    MarioFrameX[324] = -4;
    MarioFrameX[276] = -4;
    MarioFrameX[424] = -4;
    MarioFrameX[376] = -4;
    MarioFrameX[524] = -4;
    MarioFrameX[476] = -4;
    MarioFrameX[624] = -4;
    MarioFrameX[576] = -4;
    MarioFrameY[224] = 4;
    MarioFrameY[176] = 4;
    MarioFrameY[324] = 4;
    MarioFrameY[276] = 4;
    MarioFrameY[424] = 2;
    MarioFrameY[376] = 2;
    MarioFrameY[524] = 2;
    MarioFrameY[476] = 2;
    MarioFrameY[624] = 2;
    MarioFrameY[576] = 2;



    MarioFrameX[140] = -4;
    MarioFrameY[140] = 2;
    MarioFrameX[141] = -4;
    MarioFrameY[141] = 2;
    MarioFrameX[142] = -4;
    MarioFrameY[142] = 2;
    MarioFrameX[143] = -4;
    MarioFrameY[143] = 2;
    MarioFrameX[60] = -4;
    MarioFrameY[60] = 2;
    MarioFrameX[59] = -4;
    MarioFrameY[59] = 2;
    MarioFrameX[58] = 0;
    MarioFrameY[58] = 2;
    MarioFrameX[57] = 0;
    MarioFrameY[57] = 2;
    MarioFrameX[240] = -8;
    MarioFrameY[240] = 2;
    MarioFrameX[241] = -8;
    MarioFrameY[241] = 2;
    MarioFrameX[242] = -8;
    MarioFrameY[242] = 2;
    MarioFrameX[243] = -8;
    MarioFrameY[243] = 2;
    MarioFrameX[244] = -8;
    MarioFrameY[244] = 2;
    MarioFrameX[160] = -6;
    MarioFrameY[160] = 2;
    MarioFrameX[159] = -6;
    MarioFrameY[159] = 2;
    MarioFrameX[158] = -6;
    MarioFrameY[158] = 2;
    MarioFrameX[157] = -4;
    MarioFrameY[157] = 2;
    MarioFrameX[156] = -6;
    MarioFrameY[156] = 2;
    MarioFrameX[340] = -8;
    MarioFrameY[340] = 2;
    MarioFrameX[341] = -8;
    MarioFrameY[341] = 2;
    MarioFrameX[342] = -8;
    MarioFrameY[342] = 2;
    MarioFrameX[343] = -8;
    MarioFrameY[343] = 2;
    MarioFrameX[344] = -8;
    MarioFrameY[344] = 2;
    MarioFrameX[260] = -6;
    MarioFrameY[260] = 2;
    MarioFrameX[259] = -6;
    MarioFrameY[259] = 2;
    MarioFrameX[258] = -6;
    MarioFrameY[258] = 2;
    MarioFrameX[257] = -4;
    MarioFrameY[257] = 2;
    MarioFrameX[256] = -6;
    MarioFrameY[256] = 2;
    MarioFrameX[540] = -18;
    MarioFrameY[540] = 0;
    MarioFrameX[541] = -18;
    MarioFrameY[541] = 0;
    MarioFrameX[542] = -18;
    MarioFrameY[542] = 0;
    MarioFrameX[543] = -18;
    MarioFrameY[543] = 0;
    MarioFrameX[544] = -18;
    MarioFrameY[544] = 0;
    MarioFrameX[460] = -6;
    MarioFrameY[460] = 0;
    MarioFrameX[459] = -6;
    MarioFrameY[459] = 0;
    MarioFrameX[458] = -6;
    MarioFrameY[458] = 0;
    MarioFrameX[457] = -4;
    MarioFrameY[457] = 0;
    MarioFrameX[456] = -6;
    MarioFrameY[456] = 0;
    MarioFrameX[440] = -18;
    MarioFrameY[440] = 0;
    MarioFrameX[441] = -18;
    MarioFrameY[441] = 0;
    MarioFrameX[442] = -18;
    MarioFrameY[442] = 0;
    MarioFrameX[443] = -18;
    MarioFrameY[443] = 0;
    MarioFrameX[444] = -18;
    MarioFrameY[444] = 0;
    MarioFrameX[360] = -6;
    MarioFrameY[360] = 0;
    MarioFrameX[359] = -6;
    MarioFrameY[359] = 0;
    MarioFrameX[358] = -6;
    MarioFrameY[358] = 0;
    MarioFrameX[357] = -4;
    MarioFrameY[357] = 0;
    MarioFrameX[356] = -6;
    MarioFrameY[356] = 0;
    MarioFrameX[640] = -8;
    MarioFrameY[640] = 0;
    MarioFrameX[641] = -8;
    MarioFrameY[641] = 0;
    MarioFrameX[642] = -8;
    MarioFrameY[642] = 0;
    MarioFrameX[643] = -8;
    MarioFrameY[643] = 0;
    MarioFrameX[644] = -8;
    MarioFrameY[644] = 0;
    MarioFrameX[560] = -6;
    MarioFrameY[560] = 0;
    MarioFrameX[559] = -6;
    MarioFrameY[559] = 0;
    MarioFrameX[558] = -6;
    MarioFrameY[558] = 0;
    MarioFrameX[557] = -4;
    MarioFrameY[557] = 0;
    MarioFrameX[556] = -6;
    MarioFrameY[556] = 0;


    MarioFrameX[515] = -4;
    MarioFrameX[485] = -4;


    LuigiFrameX[640] = -10;
    LuigiFrameY[640] = 0;
    LuigiFrameX[641] = -10;
    LuigiFrameY[641] = 0;
    LuigiFrameX[642] = -10;
    LuigiFrameY[642] = 0;
    LuigiFrameX[643] = -10;
    LuigiFrameY[643] = 0;
    LuigiFrameX[644] = -10;
    LuigiFrameY[644] = 0;

    LuigiFrameX[560] = -4;
    LuigiFrameY[560] = 0;
    LuigiFrameX[559] = -4;
    LuigiFrameY[559] = 0;
    LuigiFrameX[558] = -4;
    LuigiFrameY[558] = 0;
    LuigiFrameX[557] = -2;
    LuigiFrameY[557] = 0;
    LuigiFrameX[556] = -2;
    LuigiFrameY[556] = 0;


    LuigiFrameX[540] = -20;
    LuigiFrameY[540] = -2;
    LuigiFrameX[541] = -20;
    LuigiFrameY[541] = -2;
    LuigiFrameX[542] = -20;
    LuigiFrameY[542] = -2;
    LuigiFrameX[543] = -20;
    LuigiFrameY[543] = -2;
    LuigiFrameX[544] = -20;
    LuigiFrameY[544] = -2;
    LuigiFrameX[460] = -4;
    LuigiFrameY[460] = -2;
    LuigiFrameX[459] = -4;
    LuigiFrameY[459] = -2;
    LuigiFrameX[458] = -4;
    LuigiFrameY[458] = -2;
    LuigiFrameX[457] = -2;
    LuigiFrameY[457] = -2;
    LuigiFrameX[456] = -2;
    LuigiFrameY[456] = -2;



    LuigiFrameX[140] = -4;
    LuigiFrameY[140] = 0;
    LuigiFrameX[141] = -4;
    LuigiFrameY[141] = 0;
    LuigiFrameX[142] = -4;
    LuigiFrameY[142] = 0;
    LuigiFrameX[143] = -4;
    LuigiFrameY[143] = 0;
    LuigiFrameX[60] = -6;
    LuigiFrameY[60] = 0;
    LuigiFrameX[59] = -6;
    LuigiFrameY[59] = 0;
    LuigiFrameX[58] = 0;
    LuigiFrameY[58] = 0;
    LuigiFrameX[57] = 0;
    LuigiFrameY[57] = 0;

    LuigiFrameX[240] = -10;
    LuigiFrameY[240] = 0;
    LuigiFrameX[241] = -10;
    LuigiFrameY[241] = 0;
    LuigiFrameX[242] = -10;
    LuigiFrameY[242] = 0;
    LuigiFrameX[243] = -10;
    LuigiFrameY[243] = 0;
    LuigiFrameX[244] = -10;
    LuigiFrameY[244] = 0;
    LuigiFrameX[160] = -4;
    LuigiFrameY[160] = 0;
    LuigiFrameX[159] = -4;
    LuigiFrameY[159] = 0;
    LuigiFrameX[158] = -4;
    LuigiFrameY[158] = 0;
    LuigiFrameX[157] = -2;
    LuigiFrameY[157] = 0;
    LuigiFrameX[156] = -2;
    LuigiFrameY[156] = 0;

    LuigiFrameX[340] = -10;
    LuigiFrameY[340] = 0;
    LuigiFrameX[341] = -10;
    LuigiFrameY[341] = 0;
    LuigiFrameX[342] = -10;
    LuigiFrameY[342] = 0;
    LuigiFrameX[343] = -10;
    LuigiFrameY[343] = 0;
    LuigiFrameX[344] = -10;
    LuigiFrameY[344] = 0;
    LuigiFrameX[260] = -4;
    LuigiFrameY[260] = 0;
    LuigiFrameX[259] = -4;
    LuigiFrameY[259] = 0;
    LuigiFrameX[258] = -4;
    LuigiFrameY[258] = 0;
    LuigiFrameX[257] = -2;
    LuigiFrameY[257] = 0;
    LuigiFrameX[256] = -2;
    LuigiFrameY[256] = 0;


    LuigiFrameX[440] = -20;
    LuigiFrameY[440] = -2;
    LuigiFrameX[441] = -20;
    LuigiFrameY[441] = -2;
    LuigiFrameX[442] = -20;
    LuigiFrameY[442] = -2;
    LuigiFrameX[443] = -20;
    LuigiFrameY[443] = -2;
    LuigiFrameX[444] = -20;
    LuigiFrameY[444] = -2;
    LuigiFrameX[360] = -4;
    LuigiFrameY[360] = -2;
    LuigiFrameX[359] = -4;
    LuigiFrameY[359] = -2;
    LuigiFrameX[358] = -4;
    LuigiFrameY[358] = -2;
    LuigiFrameX[357] = -2;
    LuigiFrameY[357] = -2;
    LuigiFrameX[356] = -2;
    LuigiFrameY[356] = -2;



    MarioFrameY[122] = -8;
    MarioFrameY[123] = -6;
    MarioFrameY[78] = -8;
    MarioFrameX[78] = -4;
    MarioFrameY[77] = -6;

    MarioFrameY[222] = -24;
    MarioFrameX[222] = -4;
    MarioFrameY[223] = -6 - 24;
    MarioFrameX[223] = -4;
    MarioFrameY[178] = -24;
    MarioFrameX[178] = -4;
    MarioFrameY[177] = -6 - 24;
    MarioFrameX[177] = -4;
    MarioFrameY[322] = -24;
    MarioFrameX[322] = -4;
    MarioFrameY[323] = -6 - 24;
    MarioFrameX[323] = -4;
    MarioFrameY[278] = -24;
    MarioFrameX[278] = -4;
    MarioFrameY[277] = -6 - 24;
    MarioFrameX[277] = -4;
    MarioFrameY[422] = -24 - 2;
    MarioFrameX[422] = -4;
    MarioFrameY[423] = -6 - 24;
    MarioFrameX[423] = -4;
    MarioFrameY[378] = -24 - 2;
    MarioFrameX[378] = -4;
    MarioFrameY[377] = -6 - 24;
    MarioFrameX[377] = -4;

    MarioFrameY[522] = -24 - 2;
    MarioFrameX[522] = -4;
    MarioFrameY[523] = -6 - 24;
    MarioFrameX[523] = -4;
    MarioFrameY[478] = -24 - 2;
    MarioFrameX[478] = -4;
    MarioFrameY[477] = -6 - 24;
    MarioFrameX[477] = -4;

    MarioFrameY[622] = -24 - 2;
    MarioFrameX[622] = -4;
    MarioFrameY[623] = -6 - 24;
    MarioFrameX[623] = -4;
    MarioFrameY[578] = -24 - 2;
    MarioFrameX[578] = -4;
    MarioFrameY[577] = -6 - 24;
    MarioFrameX[577] = -4;
    LuigiFrameY[122] = -8;
    LuigiFrameY[123] = -6;
    LuigiFrameX[123] = -2;
    LuigiFrameY[78] = -8;
    LuigiFrameX[78] = -4;
    LuigiFrameY[77] = -6;
    LuigiFrameY[222] = -24 - 4;
    LuigiFrameX[222] = -4;
    LuigiFrameY[223] = -8 - 24;
    LuigiFrameX[223] = -4;
    LuigiFrameY[178] = -24 - 4;
    LuigiFrameX[178] = -4;
    LuigiFrameY[177] = -8 - 24;
    LuigiFrameX[177] = -4;

    LuigiFrameY[322] = -24 - 4;
    LuigiFrameX[322] = -4;
    LuigiFrameY[323] = -8 - 24;
    LuigiFrameX[323] = -4;
    LuigiFrameY[278] = -24 - 4;
    LuigiFrameX[278] = -4;
    LuigiFrameY[277] = -8 - 24;
    LuigiFrameX[277] = -4;

    LuigiFrameY[422] = -24 - 4;
    LuigiFrameX[422] = -4;
    LuigiFrameY[423] = -8 - 24;
    LuigiFrameX[423] = -4;
    LuigiFrameY[378] = -24 - 4;
    LuigiFrameX[378] = -4;
    LuigiFrameY[377] = -8 - 24;
    LuigiFrameX[377] = -4;

    LuigiFrameY[522] = -24 - 4;
    LuigiFrameX[522] = -4;
    LuigiFrameY[523] = -8 - 24;
    LuigiFrameX[523] = -4;
    LuigiFrameY[478] = -24 - 4;
    LuigiFrameX[478] = -4;
    LuigiFrameY[477] = -8 - 24;
    LuigiFrameX[477] = -4;

    LuigiFrameY[622] = -24 - 4;
    LuigiFrameX[622] = -4;
    LuigiFrameY[623] = -8 - 24;
    LuigiFrameX[623] = -4;
    LuigiFrameY[578] = -24 - 4;
    LuigiFrameX[578] = -4;
    LuigiFrameY[577] = -8 - 24;
    LuigiFrameX[577] = -4;

    LuigiFrameY[207] = -6;
    LuigiFrameY[193] = -6;
    LuigiFrameY[307] = -6;
    LuigiFrameY[293] = -6;

    For(A, 650, 750)
    {
        MarioFrameX[A] = MarioFrameX[A - 400];
        MarioFrameY[A] = MarioFrameY[A - 400];
        LuigiFrameX[A] = LuigiFrameX[A - 400];
        LuigiFrameY[A] = LuigiFrameY[A - 400];
        PeachFrameX[A] = PeachFrameX[A - 400];
        PeachFrameY[A] = PeachFrameY[A - 400];
        ToadFrameX[A] = ToadFrameX[A - 400];
        ToadFrameY[A] = ToadFrameY[A - 400];
        LinkFrameX[A] = LinkFrameX[A - 400];
        LinkFrameY[A] = LinkFrameY[A - 400];
    }

    For(A, 950, 1050)
    {
        MarioFrameX[A] = MarioFrameX[A - 400];
        MarioFrameY[A] = MarioFrameY[A - 400] - 2;
        LuigiFrameX[A] = LuigiFrameX[A - 400];
        LuigiFrameY[A] = LuigiFrameY[A - 400] - 6;
        PeachFrameX[A] = PeachFrameX[A - 400];
        PeachFrameY[A] = PeachFrameY[A - 400] - 4;
        ToadFrameX[A] = ToadFrameX[A - 400];
        ToadFrameY[A] = ToadFrameY[A - 400] - 2;
        LinkFrameX[A] = LinkFrameX[A - 400];
        LinkFrameY[A] = LinkFrameY[A - 400];
    }
    //propeller suit
    MarioFrameX[982] -= 25;
    MarioFrameX[983] -= 13;
    MarioFrameX[984] -= 13;
    MarioFrameX[1017] -= 13;
    MarioFrameX[1018] -= 13;

    MarioFrameY[1007] -= 8;
    MarioFrameY[993] -= 8;

    MarioFrameX[1016] -= 12;
    For(A, 750, 850)
    {
        MarioFrameX[A] = MarioFrameX[A - 400];
        MarioFrameY[A] = MarioFrameY[A - 400] - 16;
        LuigiFrameX[A] = LuigiFrameX[A - 400];
        LuigiFrameY[A] = LuigiFrameY[A - 400];
        PeachFrameX[A] = PeachFrameX[A - 400];
        PeachFrameY[A] = PeachFrameY[A - 400];
        ToadFrameX[A] = ToadFrameX[A - 400];
        ToadFrameY[A] = ToadFrameY[A - 400];
        LinkFrameX[A] = LinkFrameX[A - 400];
        LinkFrameY[A] = LinkFrameY[A - 400];
    }

    For(A, 850, 950)
    {
        MarioFrameY[A] -= 2;
        PeachFrameY[A] -= 14;
        ToadFrameY[A] -= 8;
        LinkFrameY[A] -= 6;
    }
    For(A, 850, 900)
    {
        LuigiFrameY[A] += 2;
    }
    For(A, 900, 950)
    {
        MarioFrameX[A] += 4;
        LuigiFrameX[A] += 4;
        PeachFrameX[A] -= 2;
        ToadFrameX[A] -= 2;
        LinkFrameX[A] += 2;
    }

    LinkFrameY[907] += 2;
    LinkFrameY[904] += 2;
    LinkFrameY[893] += 2;
    LinkFrameX[893] -= 8;

    //frog suit

    //mario
    MarioFrameX[795] -= 4;
    MarioFrameX[796] -= 4;
    MarioFrameX[804] += 4;
    MarioFrameX[805] += 4;
    MarioFrameX[802] += 9;
    MarioFrameX[803] += 9;
    MarioFrameX[797] -= 12;
    MarioFrameX[798] -= 12;
    MarioFrameX[799] -= 12;
    MarioFrameX[801] += 12;
    MarioFrameX[804] += 6;
    MarioFrameX[805] += 6;
    MarioFrameX[793] += 2;
    MarioFrameX[807] += 16;

    MarioFrameX[807] -= 8;
    MarioFrameX[793] -= 8;

    MarioFrameY[807] -= 4;
    MarioFrameY[793] -= 4;
    MarioFrameY[802] -= 10;
    MarioFrameY[803] -= 10;

    MarioFrameY[798] -= 10;
    MarioFrameY[797] -= 10;

    For(A, 790, 792)
    {
        MarioFrameY[A] -= 14;
    }

    For(A, 808, 810)
    {
        MarioFrameX[A] += 4;
        MarioFrameY[A] -= 14;
    }


    //end

    PeachFrameX[401] = -16;
    PeachFrameY[401] = -2;
    PeachFrameX[399] = -4;
    PeachFrameY[399] = -2;
    PeachFrameX[402] = -16;
    PeachFrameY[402] = -2;
    PeachFrameX[398] = -4;
    PeachFrameY[398] = -2;
    PeachFrameX[403] = -16;
    PeachFrameY[403] = -2;
    PeachFrameX[397] = -4;
    PeachFrameY[397] = -2;
    PeachFrameX[404] = -14;
    PeachFrameY[404] = -2;
    PeachFrameX[396] = -4;
    PeachFrameY[396] = -2;
    PeachFrameX[405] = -14;
    PeachFrameY[405] = -2;
    PeachFrameX[395] = -4;
    PeachFrameY[395] = -2;
    PeachFrameX[406] = -8;
    PeachFrameY[406] = -2;
    PeachFrameX[394] = -14;
    PeachFrameY[394] = -2;
    PeachFrameX[407] = -4;
    PeachFrameY[407] = -2;
    PeachFrameX[393] = -4;
    PeachFrameY[393] = -2;
    PeachFrameX[408] = -14;
    PeachFrameY[408] = -2;
    PeachFrameX[392] = -4;
    PeachFrameY[392] = -2;
    PeachFrameX[409] = -14;
    PeachFrameY[409] = -2;
    PeachFrameX[391] = -4;
    PeachFrameY[391] = -2;
    PeachFrameX[410] = -16;
    PeachFrameY[410] = -2;
    PeachFrameX[390] = -4;
    PeachFrameY[390] = -2;
    PeachFrameX[412] = -16;
    PeachFrameY[412] = -2;
    PeachFrameX[388] = -4;
    PeachFrameY[388] = -2;
    PeachFrameX[413] = -4;
    PeachFrameY[413] = -4;
    PeachFrameX[387] = -4;
    PeachFrameY[387] = -4;
    PeachFrameX[414] = -4;
    PeachFrameY[414] = -2;
    PeachFrameX[386] = -16;
    PeachFrameY[386] = -2;
    PeachFrameX[415] = -4;
    PeachFrameY[415] = -4;
    PeachFrameX[385] = -4;
    PeachFrameY[385] = -4;
    PeachFrameX[419] = -13;
    PeachFrameY[419] = 0;
    PeachFrameX[381] = -11;
    PeachFrameY[381] = 0;
    PeachFrameX[420] = -13;
    PeachFrameY[420] = 0;
    PeachFrameX[380] = -11;
    PeachFrameY[380] = 0;
    PeachFrameX[421] = -13;
    PeachFrameY[421] = 0;
    PeachFrameX[379] = -11;
    PeachFrameY[379] = 0;
    PeachFrameX[422] = 0;
    PeachFrameY[422] = -30;
    PeachFrameX[378] = 0;
    PeachFrameY[378] = -30;
    PeachFrameX[423] = 0;
    PeachFrameY[423] = -30;
    PeachFrameX[377] = 0;
    PeachFrameY[377] = -30;
    PeachFrameX[425] = 0;
    PeachFrameY[425] = -2;
    PeachFrameX[375] = 0;
    PeachFrameY[375] = -2;
    PeachFrameX[426] = 0;
    PeachFrameY[426] = -2;
    PeachFrameX[374] = 0;
    PeachFrameY[374] = -2;
    PeachFrameX[427] = -4;
    PeachFrameY[427] = -2;
    PeachFrameX[373] = -4;
    PeachFrameY[373] = -2;
    PeachFrameX[501] = -16;
    PeachFrameY[501] = -6;
    PeachFrameX[499] = -4;
    PeachFrameY[499] = -6;
    PeachFrameX[502] = -18;
    PeachFrameY[502] = -6;
    PeachFrameX[498] = -4;
    PeachFrameY[498] = -6;
    PeachFrameX[503] = -16;
    PeachFrameY[503] = -6;
    PeachFrameX[497] = -4;
    PeachFrameY[497] = -6;
    PeachFrameX[504] = -14;
    PeachFrameY[504] = -6;
    PeachFrameX[496] = -4;
    PeachFrameY[496] = -6;
    PeachFrameX[505] = -14;
    PeachFrameY[505] = -6;
    PeachFrameX[495] = -4;
    PeachFrameY[495] = -6;
    PeachFrameX[506] = -8;
    PeachFrameY[506] = -6;
    PeachFrameX[494] = -12;
    PeachFrameY[494] = -6;
    PeachFrameX[507] = -4;
    PeachFrameY[507] = -6;
    PeachFrameX[493] = -4;
    PeachFrameY[493] = -6;
    PeachFrameX[508] = -16;
    PeachFrameY[508] = -6;
    PeachFrameX[492] = -4;
    PeachFrameY[492] = -6;
    PeachFrameX[509] = -18;
    PeachFrameY[509] = -6;
    PeachFrameX[491] = -4;
    PeachFrameY[491] = -6;
    PeachFrameX[510] = -18;
    PeachFrameY[510] = -6;
    PeachFrameX[490] = -4;
    PeachFrameY[490] = -6;
    PeachFrameX[512] = -16;
    PeachFrameY[512] = -6;
    PeachFrameX[488] = -4;
    PeachFrameY[488] = -6;
    PeachFrameX[513] = -4;
    PeachFrameY[513] = -2;
    PeachFrameX[487] = -4;
    PeachFrameY[487] = -2;
    PeachFrameX[514] = -4;
    PeachFrameY[514] = -6;
    PeachFrameX[486] = -16;
    PeachFrameY[486] = -6;
    PeachFrameX[515] = -4;
    PeachFrameY[515] = -6;
    PeachFrameX[485] = -4;
    PeachFrameY[485] = -6;
    PeachFrameX[519] = -13;
    PeachFrameY[519] = -4;
    PeachFrameX[481] = -9;
    PeachFrameY[481] = -4;
    PeachFrameX[520] = -13;
    PeachFrameY[520] = -4;
    PeachFrameX[480] = -9;
    PeachFrameY[480] = -4;
    PeachFrameX[521] = -13;
    PeachFrameY[521] = -4;
    PeachFrameX[479] = -9;
    PeachFrameY[479] = -4;
    PeachFrameX[522] = 0;
    PeachFrameY[522] = -34;
    PeachFrameX[478] = 0;
    PeachFrameY[478] = -34;
    PeachFrameX[523] = 0;
    PeachFrameY[523] = -34;
    PeachFrameX[477] = 0;
    PeachFrameY[477] = -34;
    PeachFrameX[525] = 0;
    PeachFrameY[525] = 0;
    PeachFrameX[475] = 0;
    PeachFrameY[475] = 0;
    PeachFrameX[526] = 0;
    PeachFrameY[526] = 0;
    PeachFrameX[474] = 0;
    PeachFrameY[474] = 0;
    PeachFrameX[527] = -6;
    PeachFrameY[527] = -6;
    PeachFrameX[473] = -6;
    PeachFrameY[473] = -6;
    PeachFrameX[500] = -5;
    PeachFrameY[500] = -6;

    PeachFrameX[601] = -10;
    PeachFrameY[601] = -2;
    PeachFrameX[599] = -4;
    PeachFrameY[599] = -2;
    PeachFrameX[602] = -10;
    PeachFrameY[602] = -2;
    PeachFrameX[598] = -4;
    PeachFrameY[598] = -2;
    PeachFrameX[603] = -8;
    PeachFrameY[603] = -2;
    PeachFrameX[597] = -4;
    PeachFrameY[597] = -2;
    PeachFrameX[604] = -8;
    PeachFrameY[604] = -2;
    PeachFrameX[596] = -4;
    PeachFrameY[596] = -2;
    PeachFrameX[605] = -8;
    PeachFrameY[605] = -2;
    PeachFrameX[595] = -4;
    PeachFrameY[595] = -2;
    PeachFrameX[606] = -6;
    PeachFrameY[606] = -2;
    PeachFrameX[594] = -6;
    PeachFrameY[594] = -2;
    PeachFrameX[607] = -4;
    PeachFrameY[607] = -4;
    PeachFrameX[593] = -4;
    PeachFrameY[593] = -4;
    PeachFrameX[608] = -6;
    PeachFrameY[608] = -2;
    PeachFrameX[592] = -4;
    PeachFrameY[592] = -2;
    PeachFrameX[609] = -6;
    PeachFrameY[609] = -2;
    PeachFrameX[591] = -4;
    PeachFrameY[591] = -2;
    PeachFrameX[610] = -8;
    PeachFrameY[610] = -2;
    PeachFrameX[590] = -4;
    PeachFrameY[590] = -2;
    PeachFrameX[611] = -6;
    PeachFrameY[611] = -2;
    PeachFrameX[589] = -4;
    PeachFrameY[589] = -2;
    PeachFrameX[612] = -6;
    PeachFrameY[612] = -2;
    PeachFrameX[588] = -4;
    PeachFrameY[588] = -2;
    PeachFrameX[613] = -4;
    PeachFrameY[613] = 2;
    PeachFrameX[587] = -4;
    PeachFrameY[587] = 2;
    PeachFrameX[615] = -4;
    PeachFrameY[615] = -4;
    PeachFrameX[585] = -4;
    PeachFrameY[585] = -4;
    PeachFrameX[622] = 0;
    PeachFrameY[622] = -34;
    PeachFrameX[578] = 0;
    PeachFrameY[578] = -34;
    PeachFrameX[623] = 0;
    PeachFrameY[623] = -32;
    PeachFrameX[577] = 0;
    PeachFrameY[577] = -32;
    PeachFrameX[625] = 0;
    PeachFrameY[625] = 2;
    PeachFrameX[575] = 0;
    PeachFrameY[575] = 2;
    PeachFrameX[626] = 0;
    PeachFrameY[626] = 2;
    PeachFrameX[574] = 0;
    PeachFrameY[574] = 2;
    PeachFrameX[627] = -4;
    PeachFrameY[627] = -4;
    PeachFrameX[573] = -4;
    PeachFrameY[573] = -4;

    ToadFrameX[401] = -14;
    ToadFrameY[401] = -2;
    ToadFrameX[399] = -4;
    ToadFrameY[399] = -2;
    ToadFrameX[402] = -12;
    ToadFrameY[402] = -2;
    ToadFrameX[398] = -4;
    ToadFrameY[398] = -2;
    ToadFrameX[403] = -18;
    ToadFrameY[403] = -2;
    ToadFrameX[397] = -4;
    ToadFrameY[397] = -2;
    ToadFrameX[404] = -18;
    ToadFrameY[404] = -2;
    ToadFrameX[396] = -4;
    ToadFrameY[396] = -2;
    ToadFrameX[405] = -18;
    ToadFrameY[405] = -2;
    ToadFrameX[395] = -4;
    ToadFrameY[395] = -2;
    ToadFrameX[406] = -6;
    ToadFrameY[406] = -2;
    ToadFrameX[394] = -4;
    ToadFrameY[394] = -2;
    ToadFrameX[407] = -4;
    ToadFrameY[407] = 0;
    ToadFrameX[393] = -4;
    ToadFrameY[393] = 0;
    ToadFrameX[408] = -16;
    ToadFrameY[408] = -2;
    ToadFrameX[392] = -4;
    ToadFrameY[392] = -2;
    ToadFrameX[409] = -14;
    ToadFrameY[409] = -2;
    ToadFrameX[391] = -4;
    ToadFrameY[391] = -2;
    ToadFrameX[410] = -18;
    ToadFrameY[410] = -2;
    ToadFrameX[390] = -4;
    ToadFrameY[390] = -2;
    ToadFrameX[411] = -14;
    ToadFrameY[411] = -2;
    ToadFrameX[389] = -4;
    ToadFrameY[389] = -2;
    ToadFrameX[412] = -16;
    ToadFrameY[412] = -2;
    ToadFrameX[388] = -4;
    ToadFrameY[388] = -2;
    ToadFrameX[413] = -4;
    ToadFrameY[413] = -4;
    ToadFrameX[387] = -4;
    ToadFrameY[387] = -4;
    ToadFrameX[414] = -4;
    ToadFrameY[414] = -2;
    ToadFrameX[386] = -14;
    ToadFrameY[386] = -2;
    ToadFrameX[415] = -4;
    ToadFrameY[415] = -2;
    ToadFrameX[385] = -4;
    ToadFrameY[385] = -2;
    ToadFrameX[416] = -18;
    ToadFrameY[416] = -2;
    ToadFrameX[384] = -8;
    ToadFrameY[384] = -2;
    ToadFrameX[417] = -18;
    ToadFrameY[417] = -2;
    ToadFrameX[383] = -8;
    ToadFrameY[383] = -2;
    ToadFrameX[418] = -18;
    ToadFrameY[418] = -2;
    ToadFrameX[382] = -8;
    ToadFrameY[382] = -2;
    ToadFrameX[419] = -12;
    ToadFrameY[419] = -2;
    ToadFrameX[381] = -8;
    ToadFrameY[381] = -2;
    ToadFrameX[420] = -18;
    ToadFrameY[420] = -2;
    ToadFrameX[380] = -8;
    ToadFrameY[380] = -2;
    ToadFrameX[421] = -14;
    ToadFrameY[421] = -2;
    ToadFrameX[379] = -8;
    ToadFrameY[379] = -2;
    ToadFrameX[422] = -4;
    ToadFrameY[422] = -22;
    ToadFrameX[378] = -4;
    ToadFrameY[378] = -22;
    ToadFrameX[423] = -4;
    ToadFrameY[423] = -16;
    ToadFrameX[377] = -4;
    ToadFrameY[377] = -16;
    ToadFrameX[424] = -8;
    ToadFrameY[424] = 6;
    ToadFrameX[376] = -4;
    ToadFrameY[376] = 6;
    ToadFrameX[425] = -4;
    ToadFrameY[425] = -4;
    ToadFrameX[375] = -4;
    ToadFrameY[375] = -4;
    ToadFrameX[426] = -4;
    ToadFrameY[426] = -4;
    ToadFrameX[374] = -4;
    ToadFrameY[374] = -4;
    ToadFrameX[427] = -4;
    ToadFrameY[427] = 0;
    ToadFrameX[373] = -4;
    ToadFrameY[373] = 0;




    ToadFrameX[501] = -12;
    ToadFrameY[501] = -2;
    ToadFrameX[499] = -4;
    ToadFrameY[499] = -2;
    ToadFrameX[502] = -12;
    ToadFrameY[502] = -2;
    ToadFrameX[498] = -4;
    ToadFrameY[498] = -2;
    ToadFrameX[503] = -18;
    ToadFrameY[503] = -2;
    ToadFrameX[497] = -4;
    ToadFrameY[497] = -2;
    ToadFrameX[504] = -18;
    ToadFrameY[504] = -2;
    ToadFrameX[496] = -4;
    ToadFrameY[496] = -2;
    ToadFrameX[505] = -18;
    ToadFrameY[505] = -2;
    ToadFrameX[495] = -4;
    ToadFrameY[495] = -2;
    ToadFrameX[506] = -6;
    ToadFrameY[506] = -2;
    ToadFrameX[494] = -4;
    ToadFrameY[494] = -2;
    ToadFrameX[507] = -4;
    ToadFrameY[507] = 0;
    ToadFrameX[493] = -4;
    ToadFrameY[493] = 0;
    ToadFrameX[508] = -12;
    ToadFrameY[508] = -2;
    ToadFrameX[492] = -4;
    ToadFrameY[492] = -2;
    ToadFrameX[509] = -12;
    ToadFrameY[509] = -2;
    ToadFrameX[491] = -4;
    ToadFrameY[491] = -2;
    ToadFrameX[510] = -18;
    ToadFrameY[510] = -2;
    ToadFrameX[490] = -4;
    ToadFrameY[490] = -2;
    ToadFrameX[511] = -14;
    ToadFrameY[511] = -2;
    ToadFrameX[489] = -4;
    ToadFrameY[489] = -2;
    ToadFrameX[512] = -14;
    ToadFrameY[512] = -2;
    ToadFrameX[488] = -4;
    ToadFrameY[488] = -2;
    ToadFrameX[513] = -4;
    ToadFrameY[513] = -4;
    ToadFrameX[487] = -4;
    ToadFrameY[487] = -4;
    ToadFrameX[514] = -4;
    ToadFrameY[514] = -2;
    ToadFrameX[486] = -12;
    ToadFrameY[486] = -2;
    ToadFrameX[515] = -4;
    ToadFrameY[515] = -2;
    ToadFrameX[485] = -4;
    ToadFrameY[485] = -2;
    ToadFrameX[516] = -12;
    ToadFrameY[516] = -2;
    ToadFrameX[484] = -8;
    ToadFrameY[484] = -2;
    ToadFrameX[517] = -12;
    ToadFrameY[517] = -2;
    ToadFrameX[483] = -8;
    ToadFrameY[483] = -2;
    ToadFrameX[518] = -18;
    ToadFrameY[518] = -2;
    ToadFrameX[482] = -8;
    ToadFrameY[482] = -2;
    ToadFrameX[519] = -12;
    ToadFrameY[519] = -2;
    ToadFrameX[481] = -8;
    ToadFrameY[481] = -2;
    ToadFrameX[520] = -12;
    ToadFrameY[520] = -2;
    ToadFrameX[480] = -8;
    ToadFrameY[480] = -2;
    ToadFrameX[521] = -14;
    ToadFrameY[521] = -2;
    ToadFrameX[479] = -8;
    ToadFrameY[479] = -2;
    ToadFrameX[522] = -4;
    ToadFrameY[522] = -22;
    ToadFrameX[478] = -4;
    ToadFrameY[478] = -22;
    ToadFrameX[523] = -4;
    ToadFrameY[523] = -16;
    ToadFrameX[477] = -4;
    ToadFrameY[477] = -16;
    ToadFrameX[524] = -12;
    ToadFrameY[524] = 6;
    ToadFrameX[476] = -4;
    ToadFrameY[476] = 6;
    ToadFrameX[525] = -4;
    ToadFrameY[525] = -4;
    ToadFrameX[475] = -4;
    ToadFrameY[475] = -4;
    ToadFrameX[526] = -4;
    ToadFrameY[526] = -4;
    ToadFrameX[474] = -4;
    ToadFrameY[474] = -4;
    ToadFrameX[527] = -4;
    ToadFrameY[527] = -2;
    ToadFrameX[473] = -4;
    ToadFrameY[473] = -2;


    ToadFrameX[601] = -6;
    ToadFrameY[601] = -2;
    ToadFrameX[599] = -4;
    ToadFrameY[599] = -2;

    ToadFrameX[602] = -6;
    ToadFrameY[602] = -2;
    ToadFrameX[598] = -4;
    ToadFrameY[598] = -2;

    ToadFrameX[603] = -6;
    ToadFrameY[603] = -2;
    ToadFrameX[597] = -4;
    ToadFrameY[597] = -2;

    ToadFrameX[604] = -6;
    ToadFrameY[604] = -2;
    ToadFrameX[596] = -4;
    ToadFrameY[596] = -2;

    ToadFrameX[605] = -6;
    ToadFrameY[605] = -2;
    ToadFrameX[595] = -4;
    ToadFrameY[595] = -2;

    ToadFrameX[606] = -6;
    ToadFrameY[606] = -2;
    ToadFrameX[594] = -4;
    ToadFrameY[594] = -2;

    ToadFrameX[607] = -6;
    ToadFrameY[607] = 0;
    ToadFrameX[593] = -6;
    ToadFrameY[593] = 0;

    ToadFrameX[608] = -6;
    ToadFrameY[608] = -2;
    ToadFrameX[592] = -4;
    ToadFrameY[592] = -2;

    ToadFrameX[609] = -6;
    ToadFrameY[609] = -2;
    ToadFrameX[591] = -4;
    ToadFrameY[591] = -2;

    ToadFrameX[610] = -6;
    ToadFrameY[610] = -2;
    ToadFrameX[590] = -4;
    ToadFrameY[590] = -2;

    ToadFrameX[611] = -6;
    ToadFrameY[611] = -2;
    ToadFrameX[589] = -4;
    ToadFrameY[589] = -2;

    ToadFrameX[612] = -6;
    ToadFrameY[612] = -2;
    ToadFrameX[588] = -4;
    ToadFrameY[588] = -2;

    ToadFrameX[613] = -4;
    ToadFrameY[613] = -2;
    ToadFrameX[587] = -4;
    ToadFrameY[587] = -2;

    ToadFrameX[615] = -6;
    ToadFrameY[615] = -2;
    ToadFrameX[585] = -6;
    ToadFrameY[585] = -2;

    ToadFrameX[622] = -4;
    ToadFrameY[622] = -22;
    ToadFrameX[578] = -4;
    ToadFrameY[578] = -22;

    ToadFrameX[623] = -4;
    ToadFrameY[623] = -16;
    ToadFrameX[577] = -4;
    ToadFrameY[577] = -16;

    ToadFrameX[625] = -4;
    ToadFrameY[625] = -2;
    ToadFrameX[575] = -4;
    ToadFrameY[575] = -2;

    ToadFrameX[626] = -4;
    ToadFrameY[626] = -2;
    ToadFrameX[574] = -4;
    ToadFrameY[574] = -2;

    ToadFrameX[627] = -4;
    ToadFrameY[627] = 0;
    ToadFrameX[573] = -4;
    ToadFrameY[573] = 0;


    ToadFrameX[500] = -6;
    ToadFrameY[500] = -6;
}
