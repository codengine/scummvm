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

#ifndef GLK_COMPREHEND_GAME_OO_H
#define GLK_COMPREHEND_GAME_OO_H

#include "glk/comprehend/game_opcodes.h"

namespace Glk {
namespace Comprehend {

enum RestartMode { RESTART_IMMEDIATE, RESTART_WITH_MSG, RESTART_WITHOUT_MSG };

class OOToposGame : public ComprehendGameV2 {
private:
	RestartMode _restartMode;
	bool _wearingGoggles, _lightOn;
	int _stringVal1, _stringVal2;
	bool _addStringFlag, _shipNotWorking;

	void randomizeGuardLocation();
	void computerResponse();

	/**
	 * Checks whether the ship is in working order
	 */
	void checkShipWorking();

	/**
	 * Tests if the player has enough to purchase needed ship fuel
	 */
	void checkShipFuel();

	/**
	 * Checks whether the ship can depart, printing out the computer's response
	 */
	void shipDepartCheck();

	/**
	 * A wrapped version of console_println that only prints the passed string
	 * if the _addStringFlag is set
	 */
	void console_cond_println(const char *str);
public:
	OOToposGame();
	~OOToposGame() override {}

	void beforeGame() override;
	void beforeTurn() override;
	bool afterTurn() override;
	int roomIsSpecial(unsigned room_index, unsigned *room_desc_string) override;
	void handleSpecialOpcode(uint8 operand) override;
	bool handle_restart() override;
};

} // namespace Comprehend
} // namespace Glk

#endif
