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

#include "mm/mm1/views/locations/training.h"
#include "mm/mm1/events.h"
#include "mm/mm1/globals.h"
#include "mm/mm1/mm1.h"
#include "mm/mm1/sound.h"

namespace MM {
namespace MM1 {
namespace Views {
namespace Locations {

#define MAX_LEVEL 200

static const int TRAINING_COSTS1[7] = {
	25, 50, 100, 200, 400, 800, 1500
};
static const int TRAINING_COSTS2[7] = {
	40, 75, 150, 300, 600, 1200, 2500
};
static const int CLASS_HP_PER_LEVEL[6] = {
	12, 10, 10, 8, 6, 8
};

Training::Training() : Location("Training") {
}

bool Training::msgFocus(const FocusMessage &msg) {
	send("View", ValueMessage(LOC_TRAINING));
	changeCharacter(0);

	return true;
}

void Training::changeCharacter(uint index) {
	Location::changeCharacter(index);
	Character &c = *g_globals->_currCharacter;

	_currLevel = c._levelBase;
	if (_currLevel >= MAX_LEVEL)
		return;

	// Initialize fields
	_expTotal = 0;
	_remainingExp = 0;
	_expAmount = 0;
	_cost = _cost2 = 0;
	_canTrain = false;
	_canAfford = false;
	_class = c._class;

	if (_class == KNIGHT || _class == CLERIC || _class == ROBBER) {
		_expTotal = 1500;
		_expAmount = 150000;

		if (_currLevel != 0) {
			_cost = _currLevel >= 8 ? 3000 :
				TRAINING_COSTS1[_currLevel - 1];
		}
	} else {
		_expTotal = 2000;
		_expAmount = 200000;
		_cost = _currLevel >= 8 ? 4000 :
			TRAINING_COSTS2[_currLevel - 1];
	}

	for (int level = _currLevel - 1, ctr = 0; level > 0; --level) {
		_expTotal *= 16;

		if (++ctr >= 7) {
			while (--level > 0)
				_expTotal += _expAmount;
			break;
		}
	}

	_remainingExp = _expTotal - c._exp;
	_canTrain = _remainingExp > 0;
	_canAfford = (int)c._gold >= _cost;
}

void Training::draw() {
	Location::draw();

	writeString(18, 1, STRING["dialogs.training.for_level"]);
	writeNumber(_currLevel + 1);

	if (_currLevel >= MAX_LEVEL) {
		writeString(24, 3, STRING["dialogs.training.no_way"]);

	} else if (_remainingExp > 0) {
		writeString(21, 3, Common::String::format(
			STRING["dialogs.training.need"].c_str(), _remainingExp));
		writeString(20, 5, STRING["dialogs.training.xp"]);

	} else {
		writeString(21, 3, Common::String::format(
			STRING["dialogs.training.cost"].c_str(), _cost));
		writeString(18, 5, STRING["dialogs.training.cost"]);
	}
}

bool Training::msgKeypress(const KeypressMessage &msg) {
	switch (msg.keycode) {
	case Common::KEYCODE_ESCAPE:
		leave();
		break;
	case Common::KEYCODE_a:
		if (_canTrain)
			train();
		break;
	case Common::KEYCODE_g:
		gatherGold();
		redraw();
		break;
	case Common::KEYCODE_1:
	case Common::KEYCODE_2:
	case Common::KEYCODE_3:
	case Common::KEYCODE_4:
	case Common::KEYCODE_5:
	case Common::KEYCODE_6:
		changeCharacter(msg.keycode - Common::KEYCODE_1);
		break;
	default:
		break;
	}

	return true;
}

void Training::train() {
	Character &c = *g_globals->_currCharacter;

	if (c._condition) {
		Sound::sound(SOUND_3);
		clearSurface();
		writeString(8, 5, STRING["dialogs.training.condition"]);
		_timeoutCtr = 3 * FRAME_RATE;

	} else if (!_canAfford) {
		notEnoughGold();

	} else {
		// Do the actual training
		c._gold -= _cost;
		doTraining();
	}
}

void Training::doTraining() {
	Character &c = *g_globals->_currCharacter;
	c._level = ++c._levelBase;
	c._age = ++c._ageBase;
	if (c._ageBase > 220)
		c._ageBase = 220;
	c._v6c += 2;

	int classNum = c._class == NONE ? ROBBER : c._class;
	int newHP = g_engine->getRandomNumber(CLASS_HP_PER_LEVEL[classNum - 1]);

	if (c._endBase >= 40)
		newHP += 10;
	else if (c._endBase >= 35)
		newHP += 9;
	else if (c._endBase >= 30)
		newHP += 8;
	else if (c._endBase >= 27)
		newHP += 7;
	else if (c._endBase >= 24)
		newHP += 6;
	else if (c._endBase >= 21)
		newHP += 5;
	else if (c._endBase >= 19)
		newHP += 4;
	else if (c._endBase >= 17)
		newHP += 3;
	else if (c._endBase >= 15)
		newHP += 2;
	else if (c._endBase >= 13)
		newHP += 1;
	else if (c._endBase >= 9)
		newHP += 0;
	else if (c._endBase >= 7)
		newHP = MAX(newHP - 1, 1);
	else if (c._endBase >= 5)
		newHP = MAX(newHP - 2, 1);
	else
		newHP = MAX(newHP - 3, 1);

	c._hpBase += newHP;
	c._hp = c._hpMax = c._hpBase;

	// TODO: Remaining stuff
}

} // namespace Locations
} // namespace Views
} // namespace MM1
} // namespace MM
