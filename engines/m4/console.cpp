/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "m4/console.h"
#include "m4/vars.h"

namespace M4 {

Console::Console() : GUI::Debugger() {
	registerCmd("test",   WRAP_METHOD(Console, Cmd_test));
	registerCmd("room",   WRAP_METHOD(Console, Cmd_room));
}

Console::~Console() {
}

bool Console::Cmd_test(int argc, const char **argv) {
	debugPrintf("Test\n");
	return true;
}

bool Console::Cmd_room(int argc, const char **argv) {
	if (argc == 2) {
		_G(game).setRoom(atol(argv[1]));
		return false;
	} else {
		debugPrintf("room <room number>]\n");
		return true;
	}
}


} // End of namespace M4
