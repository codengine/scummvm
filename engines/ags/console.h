
/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef AGS_CONSOLE_H
#define AGS_CONSOLE_H

#include "gui/debugger.h"
#include "ags/shared/debugging/debugmanager.h"
#include "ags/shared/debugging/outputhandler.h"

namespace AGS {

class AGSEngine;
class LogOutputTarget;

class AGSConsole : public GUI::Debugger {
public:
	AGSConsole(AGSEngine *vm);
	~AGSConsole() override;

private:
	AGSEngine *_vm;
	LogOutputTarget *_logOutputTarget;
	AGS3::AGS::Shared::PDebugOutput _agsDebuggerOutput;

	bool Cmd_listDebugGroups(int argc, const char **argv);
	bool Cmd_setDebugGroupLevel(int argc, const char **argv);

	bool Cmd_getSptintInfo(int argc, const char **argv);
	bool Cmd_dumpSrite(int argc, const char **argv);

	const char *getVerbosityLevel(uint32_t groupID) const;
	uint32_t parseGroup(const char *, bool &) const;
	AGS3::AGS::Shared::MessageType parseLevel(const char *, bool &) const;
	void printGroupList();
	void printLevelList();
};

class LogOutputTarget : public AGS3::AGS::Shared::IOutputHandler {
public:
	LogOutputTarget();
	virtual ~LogOutputTarget() override;

	void PrintMessage(const AGS3::AGS::Shared::DebugMessage &msg) override;
};

} // End of namespace CGE

#endif
