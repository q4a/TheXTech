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
#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <memory>
#include <string>

#include "cmd_line_setup.h"

#include "core/base/render_base.h"
#include "core/base/window_base.h"
#include "core/base/msgbox_base.h"
#include "core/base/events_base.h"


class FrmMain
{
    std::unique_ptr<AbstractWindow_t> m_window;
    std::unique_ptr<AbstractRender_t> m_render;
    std::unique_ptr<AbstractMsgBox_t> m_msgbox;
    std::unique_ptr<AbstractEvents_t> m_events;

public:
    FrmMain() noexcept = default;
    ~FrmMain() = default;

    bool initSystem(const CmdLineSetup_t &setup);
    void freeSystem();
};

#endif // FRMMAIN_H
