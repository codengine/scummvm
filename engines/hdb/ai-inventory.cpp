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

#include "hdb/hdb.h"

namespace HDB {

// Add entity to Player's Inventory
bool AI::addToInventory(AIEntity *e) {
	switch (e->type) {
	case ITEM_GEM_WHITE:
		_numGems++;
		removeEntity(e);
		return true;
	case ITEM_GEM_BLUE:
		_numGems += 5;
		removeEntity(e);
		return true;
	case ITEM_GEM_RED:
		_numGems += 10;
		removeEntity(e);
		return true;
	case ITEM_GEM_GREEN:
		_numGems += 100;
		removeEntity(e);
		return true;
	case ITEM_GOO_CUP:
		_numGooCups++;
		removeEntity(e);
		return true;
	case ITEM_MONKEYSTONE:
		_numMonkeystones++;
		removeEntity(e);
		return true;
	}

	if (_numInventory >= kMaxInventory) {
		warning("STUB: addToInventory: Inventory full message");
		return false;
	}

	memcpy(&_inventory[_numInventory].ent, e, sizeof(AIEntity));
	_numInventory++;

	// If weapon, ready it
	switch (e->type) {
	case ITEM_CLUB:
	case ITEM_ROBOSTUNNER:
	case ITEM_SLUGSLINGER:
		warning("STUB: addToInventory: Ready weapon");
	}

	warning("STUB: addToInventory: Print a 'You Got' message");
	removeEntity(e);
	return true;
}

} // End of Namespace
