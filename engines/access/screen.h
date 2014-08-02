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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ACCESS_SCREEN_H
#define ACCESS_SCREEN_H

#include "common/scummsys.h"
#include "common/rect.h"
#include "common/stream.h"
#include "graphics/surface.h"

namespace Access {

class AccessEngine;

#define PALETTE_COUNT 256
#define PALETTE_SIZE (256 * 3)

class Screen: public Graphics::Surface {
private:
	AccessEngine *_vm;
	byte _tempPalette[PALETTE_SIZE];
	byte _rawPalette[PALETTE_SIZE];

	void setPalette();

	void updatePalette();
public:
	bool _loadPalFlag;
public:
	Screen(AccessEngine *vm);

	void setDisplayScan();

	/**
	 * Update the underlying screen
	 */
	void updateScreen();

	/**
	 * Fade out screen
	 */
	void forceFadeOut();

	/**
	 * Fade in screen
	 */
	void forceFadeIn();

	/**
	 * Set the initial palette
	 */
	void setInitialPalettte();

	void loadPalette(Common::SeekableReadStream *stream);

	/**
	 * Copy a buffer to the screen
	 */
	void copyBuffer(const byte *data);
};

} // End of namespace Access

#endif /* ACCESS_SCREEN_H */
