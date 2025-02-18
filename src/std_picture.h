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

#pragma once
#ifndef STD_PICTURE_H
#define STD_PICTURE_H

#include "core/picture_data.h"
#include "core/picture_load.h"

#ifdef DEBUG_BUILD
#   include <string>
#   define STD_PICTURE_HAS_ORIG_PATH
#endif

/*!
 * \brief RGB pixel color
 */
struct PGEColor
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

struct SDL_Texture;

/**
 * @brief Handler of a graphical texture
 */
struct StdPicture
{
#ifdef STD_PICTURE_HAS_ORIG_PATH
    //! Debug-only file path to the original picture
    std::string origPath;
#endif

    //! Was this texture initialized by graphical engine or not?
    bool inited = false;

    //! Width of texture
    int w = 0;
    //! Height of texture
    int h = 0;

    // Frame width and height (for animation sprite textures)
    //! Animation frame width
    int frame_w = 0;
    //1 Animation frame height
    int frame_h = 0;

    // These colors were used to auto-choose the fill color for the background
    //! Left-top pixel color
    PGEColor ColorUpper;
    //! Left-bottom pixel color
    PGEColor ColorLower;

    /*!
     * \brief Reset colors into black
     */
    inline void resetColors()
    {
        ColorUpper.r = 0;
        ColorUpper.g = 0;
        ColorUpper.b = 0;
        ColorLower.r = 0;
        ColorLower.g = 0;
        ColorLower.b = 0;
    }


    /* Loader related stuff */

    //! Loader-related data
    StdPictureLoad l;

    //! Platform specific texture data
    StdPictureData d;

    /*!
     * \brief Reset all values into initial state.
     *
     * This must be called by renderer backend after texture deletion
     */
    inline void resetAll()
    {
        inited = false;
        l.clear();
        w = 0;
        h = 0;
        frame_w = 0;
        frame_h = 0;
    }
};

// This macro allows to get the original texture path when debug build is on,
// and safely return the blank string when the release build is
#ifdef STD_PICTURE_HAS_ORIG_PATH
#   define StdPictureGetOrigPath(x) x.origPath
#else
#   define StdPictureGetOrigPath(x) std::string()
#endif


#endif // STD_PICTURE_H
