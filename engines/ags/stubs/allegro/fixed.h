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

#ifndef AGS_STUBS_ALLEGRO_FIXED_H
#define AGS_STUBS_ALLEGRO_FIXED_H

#include "common/scummsys.h"

namespace AGS3 {

typedef long fixed;

extern fixed fixtorad_r;
extern fixed radtofix_r;
extern fixed _cos_tbl[];
extern fixed _tan_tbl[];
extern fixed _acos_tbl[];

extern fixed ftofix(double x);
extern double fixtof(fixed x);
extern fixed fixadd(fixed x, fixed y);
extern fixed fixsub(fixed x, fixed y);
extern fixed fixmul(fixed x, fixed y);
extern fixed fixdiv(fixed x, fixed y);
extern int fixfloor(fixed x);
extern int fixceil(fixed x);
extern fixed itofix(int x);
extern int fixtoi(fixed x);
extern fixed fixcos(fixed x);
extern fixed fixsin(fixed x);
extern fixed fixtan(fixed x);
extern fixed fixacos(fixed x);
extern fixed fixasin(fixed x);

#if 0
extern fixed fixsqrt(fixed x);
extern fixed fixhypot(fixed x, fixed y);
extern fixed fixatan(fixed x);
extern fixed fixatan2(fixed y, fixed x);
#endif

} // namespace AGS3

#endif
