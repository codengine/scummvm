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

#ifndef CHEWY_ROOMS_ROOM41_H
#define CHEWY_ROOMS_ROOM41_H

namespace Chewy {
namespace Rooms {

class Room41 {
private:
	static void first_talk();
	static void start_hoggy();
	static void stop_hoggy();
	static void setup_func();

public:
	static void entry();
	static void xit();
	static int16 gedUserFunc(int16 idx_nr);

	static int16 use_brief();
	static int16 use_lola();
	static int16 use_kasse();
	static void talk_hoggy1();
	static void talk_hoggy2();
	static void sub_dia();
};

} // namespace Rooms
} // namespace Chewy

#endif
