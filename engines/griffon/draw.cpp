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
 *
 *              Originally written by Syn9 in FreeBASIC with SDL
 *              http://syn9.thehideoutgames.com/index_backup.php
 *
 *            Ported to plain C for GCW-Zero handheld by Dmitry Smagin
 *                http://github.com/dmitrysmagin/griffon_legend
 *
 *
 *                 Programming/Graphics: Daniel "Syn9" Kennedy
 *                     Music/Sound effects: David Turner
 *
 *                   Beta testing and gameplay design help:
 *                    Deleter, Cha0s, Aether Fox, and Kiz
 *
 */

#include "common/system.h"

#include "griffon/griffon.h"
#include "griffon/config.h"

namespace Griffon {

// map in inventory menu
const int invmap[4][7][13] = {
	// map 0
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 43, 44, 45, 46, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	},
	// map 1
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 19, 20, 21, 22, 0, 0, 0, 27, 0, 0, 0},
		{0, 0, 16, 17, 18, 0, 0, 0, 29, 30, 31, 0, 0},
		{0, 0, 12, 0, 13, 14, 0, 32, 33, 34, 35, 36, 0},
		{0, 8, 7, 6, 9, 10, 0, 37, 38, 39, 40, 41, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	},
	// map 2
	{
		{0, 0, 0, 0, 0, 0, 67, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 63, 64, 65, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 58, 59, 60, 61, 62, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 55, 56, 57, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 50, 51, 52, 53, 54, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 48, 47, 49, 0, 0, 0, 0, 0}
	},

	// map 3
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 79, 80, 81, 0, 74, 72, 0, 0, 0, 0},
		{0, 0, 0, 78, 0, 0, 0, 73, 70, 69, 68, 0, 0},
		{0, 0, 77, 76, 75, 0, 0, 0, 71, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	}
};


void game_fillrect(Graphics::TransparentSurface *surface, int x, int y, int w, int h, int color) {
	surface->fillRect(Common::Rect(x, y, x + w, y + h), color);
}

void GriffonEngine::drawAnims(int Layer) {
	for (int sx = 0; sx <= 19; sx++) {
		for (int sy = 0; sy <= 14; sy++) {
			int o = _objectMap[sx][sy];

			if (o > -1) {
				int xtiles = _objectInfo[o][1];
				int ytiles = _objectInfo[o][2];
				int cframe = _objectFrame[o][1];

				for (int x = 0; x <= xtiles - 1; x++) {
					for (int y = 0; y <= ytiles - 1; y++) {
						int x1 = (sx + x) * 16;
						int y1 = (sy + y) * 16;

						if (_objectTile[o][cframe][x][y][1] == Layer) {
							int c = _objectTile[o][cframe][x][y][0];
							c = c - 1;
							int curtilel = 3;
							int curtilex = c % 20;
							int curtiley = (c - curtilex) / 20;

							if (_curmap == 58 && _scriptflag[kScriptLever][0] > 0)
								curtilex = 1;
							if (_curmap == 54 && _scriptflag[kScriptLever][0] > 1)
								curtilex = 1;
							rcSrc.left = curtilex * 16;
							rcSrc.top = curtiley * 16;
							rcSrc.setWidth(16);
							rcSrc.setHeight(16);

							rcDest.left = x1;
							rcDest.top = y1;
							rcDest.setWidth(16);
							rcDest.setHeight(16);

							_tiles[curtilel]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
						}

						if (Layer == 1) {
							for (int l = 1; l <= 2; l++) {
								int c = _tileinfo[l][sx + x][sy + y][0];
								if (c > 0) {
									int cl = _tileinfo[l][sx + x][sy + y][1];

									c = c - 1;
									int curtile = c;
									int curtilel = cl;
									int curtilex = c % 20;
									int curtiley = (c - curtilex) / 20;

									rcSrc.left = curtilex * 16;
									rcSrc.top = curtiley * 16;
									rcSrc.setWidth(16);
									rcSrc.setHeight(16);

									rcDest.left = (sx + x) * 16;
									rcDest.top = (sy + y) * 16;
									rcDest.setWidth(16);
									rcDest.setHeight(16);

									int pass = 1;
									if (curtilel == 1) {
										for (int ff = 0; ff <= 5; ff++) {
											int ffa = 20 * 5 - 1 + ff * 20;
											int ffb = 20 * 5 + 4 + ff * 20;
											if (curtile > ffa && curtile < ffb)
												pass = 0;
										}
									}

									if (pass == 1)
										_tiles[curtilel]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
								}
							}
						}
					}
				}
			}
		}
	}
}

int hud_recalc(int a, int b, int c) {
	int result = a * b / c;

	return result > b ? b : result;
}

#define RGB(R, G, B) (_videobuffer->format.RGBToColor((R), (G), (B)))

void GriffonEngine::drawHud() {
	//sprintf(line, "_fps: %i, map: %i, exp: %i/%i", (int)_fps, _curmap, _player.exp, _player.nextlevel);
	//drawString(_videobuffer, line, 0, 0, 0);

	game_fillrect(_videobuffer2, 0, 0, 320, 240, 0);

	for (int i = 0; i < kMaxFloat; i++) {
		if (_floattext[i][0] > 0) {
			int fc = (int)_floattext[i][3];
			int c = fc, c2 = 3;

			if (fc == 4)
				c = 1;
			else if (fc == 5)
				c = 0;

			if (fc == 1 || fc == 3)
				c2 = 2;

			if (fc != 0) {
				drawString(_videobuffer, _floatstri[i], (int)(_floattext[i][1]) + 0, (int)(_floattext[i][2]) - 1, c2);
				drawString(_videobuffer, _floatstri[i], (int)(_floattext[i][1]) + 0, (int)(_floattext[i][2]) + 1, c2);
				drawString(_videobuffer, _floatstri[i], (int)(_floattext[i][1]) - 1, (int)(_floattext[i][2]) + 0, c2);
				drawString(_videobuffer, _floatstri[i], (int)(_floattext[i][1]) + 1, (int)(_floattext[i][2]) + 0, c2);
			}

			drawString(_videobuffer, _floatstri[i], (int)(_floattext[i][1]), (int)(_floattext[i][2]), c);
		}

		if (_floaticon[i][0] > 0) {
			int ico = _floaticon[i][3];
			int ix = _floaticon[i][1];
			int iy = _floaticon[i][2];

			rcDest.left = ix;
			rcDest.top = iy;

			if (ico != 99)
				_itemimg[ico]->blit(*_videobuffer, rcDest.left, rcDest.top);
			if (ico == 99) {
				_spellimg->setAlpha((int)(RND() * 96) + 96, true);

				rcSrc.left = 16 * (int)(RND() * 2);
				rcSrc.top = 80;
				rcSrc.setWidth(16);
				rcSrc.setHeight(16);

				rcDest.left = ix;
				rcDest.top = iy;

				_spellimg->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);

				_spellimg->setAlpha(255, true);
			}
		}
	}

	if (_itemselon == 0) {
		int sy = 211;


		int nx = 19 * 8 + 13;
		rcSrc.left = nx - 17 + 48;
		rcSrc.top = sy;

		// spells in game
		if (_player.foundSpell[0] == 1) {
			for (int i = 0; i < 5; i++) {
				rcSrc.left = rcSrc.left + 17;

				if (_player.foundSpell[i] == 1) {
					_itemimg[7 + i]->blit(*_videobuffer, rcSrc.left, rcSrc.top);

					game_fillrect(_videobuffer, rcSrc.left, sy + 16, 16, 4, RGB(0, 32, 32));
					game_fillrect(_videobuffer, rcSrc.left + 1, sy + 17,
					              hud_recalc(_player.spellCharge[i], 14, 100), 2,
					              ABS(_player.spellCharge[i] - 100) < kEpsilon ? RGB(255, 128, 32) : RGB(0, 224, 64));
				}
			}
		}
		return;
	}

	if (_selenemyon == 0) {
		rcDest.left = 0;
		rcDest.top = 0;
		rcDest.right = 320;
		rcDest.bottom = 240;
		_videobuffer2->fillRect(rcDest, 0);
		_videobuffer2->setAlpha((int)(_player.itemselshade * 4)); // FIXME
		_videobuffer2->blit(*_videobuffer);

		int sy = 202;
		rcSrc.left = 46;
		rcSrc.top = 46;

		_inventoryimg->setAlpha(160, true); // 128
		_inventoryimg->blit(*_videobuffer, rcSrc.left, rcSrc.top);
		_inventoryimg->setAlpha(255, true);

		int sx = 54;
		sy = 55;

		// draw map 9,77
		rcDest.left = 46 + 9;
		rcDest.top = 46 + 77;

		int amap = 0;
		if (_curmap > 46)
			amap = 2;
		if (_curmap > 67)
			amap = 3;
		if (_curmap > 5 && _curmap < 42)
			amap = 1;
		mapimg[amap]->blit(*_videobuffer, rcDest.left, rcDest.top);

		long ccc = _videobuffer->format.RGBToColor(128 + 127 * sin(3.141592 * 2 * _itemyloc / 16), 0, 0);

		for (int b = 0; b <= 6; b++) {
			for (int a = 0; a <= 12; a++) {
				if (invmap[amap][b][a] == _curmap) {
					game_fillrect(_videobuffer, 46 + 9 + a * 9 + 2, 46 + 77 + b * 9 + 1, 6, 6, ccc);
				}
			}
		}

		if (amap == 1) {
			drawString(_videobuffer, "L1", 46 + 9, 46 + 77, 0);
			drawString(_videobuffer, "L2", 46 + 9 + 7 * 9, 46 + 77, 0);
		}

		char line[128];
		sprintf(line, "Health: %i/%i", _player.hp, _player.maxHp);
		drawString(_videobuffer, line, sx, sy, _player.hp <= _player.maxHp * 0.25 ? (int)_player.hpflash : 0);

		sprintf(line, "Level : %i", _player.level);
		if (_player.level == _player.maxLevel)
			strcpy(line, "Level : MAX");
		drawString(_videobuffer, line, sx, sy + 8, 0);

		// experience
		game_fillrect(_videobuffer, sx + 64, sy + 16, 16, 4, RGB(0, 32, 32));
		game_fillrect(_videobuffer, sx + 65, sy + 17,
		              hud_recalc(_player.exp, 14, _player.nextLevel), 2, RGB(0, 224, 64));

		// attack strength
		game_fillrect(_videobuffer, sx + 1, sy + 16, 56, 6, RGB(0, 32, 32));
		game_fillrect(_videobuffer, sx + 1, sy + 17,
		              hud_recalc(_player.attackStrength, 54, 100), 2,
		              ABS(_player.attackStrength - 100) < kEpsilon ? RGB(255, 128, 32) : RGB(0, 64, 224));

		// spell strength
		game_fillrect(_videobuffer, sx + 1, sy + 19,
		              hud_recalc(_player.spellStrength, 54, 100), 2,
		              ABS(_player.spellStrength - 100) < kEpsilon ? RGB(224, 0, 0) : RGB(128, 0, 224));

		// time
		int ase = _secstart + _secsingame;
		int h = ((ase - (ase % 3600)) / 3600);
		ase = (ase - h * 3600);
		int m = ((ase - (ase % 60)) / 60);
		int s = (ase - m * 60);

		sprintf(line, "%02i:%02i:%02i", h, m, s);
		drawString(_videobuffer, line, 46 + 38 - strlen(line) * 4, 46 + 49, 0);

		drawString(_videobuffer, "Use", 193, 55, 0);
		drawString(_videobuffer, "Cast", 236, 55, 0);

		rcSrc.left = 128;
		rcSrc.top = 91;

		int ss = (_player.sword - 1) * 3;
		if (_player.sword == 3)
			ss = 18;
		_itemimg[ss]->blit(*_videobuffer, rcSrc.left, rcSrc.top);

		rcSrc.left = rcSrc.left + 16;
		ss = (_player.shield - 1) * 3 + 1;
		if (_player.shield == 3)
			ss = 19;
		_itemimg[ss]->blit(*_videobuffer, rcSrc.left, rcSrc.top);

		rcSrc.left = rcSrc.left + 16;
		ss = (_player.armour - 1) * 3 + 2;
		if (_player.armour == 3)
			ss = 20;
		_itemimg[ss]->blit(*_videobuffer, rcSrc.left, rcSrc.top);

		for (int i = 0; i <= 4; i++) {
			sx = 188;
			sy = 70 + i * 24;
			rcSrc.left = sx;
			rcSrc.top = sy;
			if (i == 0)
				_itemimg[6]->blit(*_videobuffer, rcSrc.left, rcSrc.top);
			if (i == 1)
				_itemimg[12]->blit(*_videobuffer, rcSrc.left, rcSrc.top);
			if (i == 2)
				_itemimg[17]->blit(*_videobuffer, rcSrc.left, rcSrc.top);
			if (i == 3)
				_itemimg[16]->blit(*_videobuffer, rcSrc.left, rcSrc.top);
			if (i == 4)
				_itemimg[14]->blit(*_videobuffer, rcSrc.left, rcSrc.top);

			sprintf(line, "x%i", _player.inventory[i]);
			drawString(_videobuffer, line, sx + 17, sy + 7, 0);
		}

		// spells in menu
		if (_player.foundSpell[0] == 1) {
			for (int i = 0; i < 5; i++) {
				rcSrc.left = 243;
				rcSrc.top = 67 + i * 24;
				sy = rcSrc.top;

				if (_player.foundSpell[i] == 1) {
					_itemimg[7 + i]->blit(*_videobuffer, rcSrc.left, rcSrc.top);

					game_fillrect(_videobuffer, rcSrc.left, sy + 16, 16, 4, RGB(0, 32, 32));
					game_fillrect(_videobuffer, rcSrc.left + 1, sy + 17,
					              hud_recalc(_player.spellCharge[i], 14, 100), 2,
					              ABS(_player.spellCharge[i] - 100) < kEpsilon ? RGB(255, 128, 32) : RGB(0, 224, 64));
				}
			}
		}

		if (_itemselon == 1) {
			for (int i = 0; i <= 4; i++) {
				if (_curitem == 5 + i) {
					rcDest.left = (float)(243 - 12 + 3 * sin(3.141592 * 2 * _itemyloc / 16));
					rcDest.top = 67 + 24 * i;
					_itemimg[15]->blit(*_videobuffer, rcDest.left, rcDest.top);
				}

				if (_curitem == i) {
					rcDest.left = (float)(189 - 12 + 3 * sin(3.141592 * 2 * _itemyloc / 16));
					rcDest.top = 70 + 24 * i;
					_itemimg[15]->blit(*_videobuffer, rcDest.left, rcDest.top);
				}
			}
		}
	}

	if (_selenemyon == 1) {
		if (_curenemy > _lastnpc) {
			int pst = _curenemy - _lastnpc - 1;
			rcDest.left = postinfo[pst][0];
			rcDest.top = (float)(postinfo[pst][1] - 4 - sin(3.141592 / 8 * _itemyloc));
		} else {
			rcDest.left = _npcinfo[_curenemy].x + 4;
			rcDest.top = (float)(_npcinfo[_curenemy].y + 4 - 16 - sin(3.141592 / 8 * _itemyloc));
		}

		_itemimg[13]->blit(*_videobuffer, rcDest.left, rcDest.top);
	}
}

void GriffonEngine::drawNPCs(int mode) {
	unsigned int ccc = _videobuffer->format.RGBToColor(255, 128, 32);
	int fst = _firsty;
	int lst = _lasty;

	if (mode == 0)
		lst = _player.ysort;
	if (mode == 1)
		fst = _player.ysort;

	for (int yy = fst; yy <= lst; yy++) {

		if (_ysort[yy] > 0) {
			int i = _ysort[yy];

			if (_npcinfo[i].hp > 0) {
				int npx = (int)(_npcinfo[i].x);
				int npy = (int)(_npcinfo[i].y);

				int sprite = _npcinfo[i].spriteset;

				int wdir = _npcinfo[i].walkdir;

				// spriteset1 specific
				if (_npcinfo[i].spriteset == kMonsterBabyDragon) {

					if (_npcinfo[i].attacking == 0) {

						int cframe = _npcinfo[i].cframe;

						rcSrc.left = (int)(cframe / 4) * 24;
						rcSrc.top = wdir * 24;
						rcSrc.setWidth(24);
						rcSrc.setHeight(24);

						rcDest.left = npx;
						rcDest.top = npy;
						rcDest.setWidth(24);
						rcDest.setHeight(24);

						if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
							_npcinfo[i].shake = _ticks + 50;
							rcDest.left += (int)(RND() * 3) - 1;
							rcDest.top += (int)(RND() * 3) - 1;
						}

						_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					} else {
						int cframe = _npcinfo[i].cattackframe;

						rcSrc.left = (int)(cframe / 4) * 24;
						rcSrc.top = wdir * 24;
						rcSrc.setWidth(24);
						rcSrc.setHeight(24);

						rcDest.left = npx;
						rcDest.top = npy;
						rcDest.setWidth(24);
						rcDest.setHeight(24);

						_animsa[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}

				}

				// onewing
				if (_npcinfo[i].spriteset == kMonsterOneWing) {
					for (int f = 0; f < 7; f++) {
						int s = _npcinfo[i].bodysection[f].sprite;
						rcSrc.left = _animset2[s].x;
						rcSrc.top = _animset2[s].y;
						rcSrc.setWidth(_animset2[s].w);
						rcSrc.setHeight(_animset2[s].h);

						rcDest.left = _npcinfo[i].bodysection[f].x - _animset2[s].xofs;
						rcDest.top = _npcinfo[i].bodysection[f].y - _animset2[s].yofs + 2;

						_anims[2]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}

				}

				// twowing
				if (_npcinfo[i].spriteset == kMonsterTwoWing) {
					for (int f = 0; f < 7; f++) {
						int yp = 0;

						if (f == 0 && (_curmap == 53 || _curmap == 57 || _curmap == 61 || _curmap == 65 || _curmap == 56 || _curmap > 66) && _scriptflag[kScriptLever][0] > 0)
							yp = 16;
						int s = _npcinfo[i].bodysection[f].sprite;
						rcSrc.left = _animset9[s].x;
						rcSrc.top = _animset9[s].y + yp;
						rcSrc.setWidth(_animset9[s].w);
						rcSrc.setHeight(_animset9[s].h);

						rcDest.left = _npcinfo[i].bodysection[f].x - _animset9[s].xofs;
						rcDest.top = _npcinfo[i].bodysection[f].y - _animset9[s].yofs + 2;

						_anims[9]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}

				}


				//  boss 1
				if (_npcinfo[i].spriteset == kMonsterBoss1) {
					if (_npcinfo[i].attacking == 0) {
						int cframe = _npcinfo[i].cframe;

						rcSrc.left = (int)(cframe / 4) * 24;
						rcSrc.top = 0;
						rcSrc.setWidth(24);
						rcSrc.setHeight(48);

						rcDest.left = npx - 2;
						rcDest.top = npy - 24;

						_anims[3]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					} else {
						rcSrc.left = 4 * 24;
						rcSrc.top = 0;
						rcSrc.setWidth(24);
						rcSrc.setHeight(48);

						rcDest.left = npx - 2;
						rcDest.top = npy - 24;

						_anims[3]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}

				}

				// black knight
				if (_npcinfo[i].spriteset == kMonsterBlackKnight) {
					if (_npcinfo[i].attacking == 0) {
						int cframe = _npcinfo[i].cframe;

						rcSrc.left = (int)(cframe / 4) * 24;
						rcSrc.top = 0;
						rcSrc.setWidth(24);
						rcSrc.setHeight(48);

						rcDest.left = npx - 2;
						rcDest.top = npy - 24;

						_anims[4]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					} else {
						rcSrc.left = 4 * 24;
						rcSrc.top = 0;
						rcSrc.setWidth(24);
						rcSrc.setHeight(48);

						rcDest.left = npx - 2;
						rcDest.top = npy - 24;

						_anims[4]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}
				}


				// firehydra
				if (_npcinfo[i].spriteset == kMonsterFireHydra) {
					for (int ff = 0; ff <= 2; ff++) {
						if (_npcinfo[i].hp > 10 * ff * 20) {
							rcSrc.left = 16 * (int)(RND() * 2);
							rcSrc.top = 80;
							rcSrc.setWidth(16);
							rcSrc.setHeight(16);

							rcDest.left = _npcinfo[i].bodysection[10 * ff].x - 8;
							rcDest.top = _npcinfo[i].bodysection[10 * ff].y - 8;

							int x = 192 + ((int)(_itemyloc + ff * 5) % 3) * 64;
							if (x > 255)
								x = 255;
							_spellimg->setAlpha(x, true);
							_spellimg->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
							_spellimg->setAlpha(255, true);

							for (int f = 1; f <= 8; f++) {
								rcSrc.left = 16 * (int)(RND() * 2);
								rcSrc.top = 80;
								rcSrc.setWidth(16);
								rcSrc.setHeight(16);

								rcDest.left = _npcinfo[i].bodysection[ff * 10 + f].x - 8 + (int)(RND() * 3) - 1;
								rcDest.top = _npcinfo[i].bodysection[ff * 10 + f].y - 8 + (int)(RND() * 3) - 1;

								x = 192 + f % 3 * 64;
								if (x > 255)
									x = 255;
								_spellimg->setAlpha(x, true);
								_spellimg->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
								_spellimg->setAlpha(255, true);
							}

							rcSrc.left = 0;
							rcSrc.top = 0;
							rcSrc.setWidth(42);
							rcSrc.setHeight(36);

							rcDest.left = _npcinfo[i].bodysection[10 * ff + 9].x - 21;
							rcDest.top = _npcinfo[i].bodysection[10 * ff + 9].y - 21;

							_spellimg->setAlpha(192, true);
							_anims[5]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
							_spellimg->setAlpha(255, true);
						}

					}

				}

				// red dragon
				if (_npcinfo[i].spriteset == kMonsterRedDragon) {
					int cframe = _npcinfo[i].cframe;

					rcSrc.left = (int)(cframe / 4) * 24;
					rcSrc.top = wdir * 24;
					rcSrc.setWidth(24);
					rcSrc.setHeight(24);

					rcDest.left = npx;
					rcDest.top = npy;
					rcDest.setWidth(24);
					rcDest.setHeight(24);

					if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
						_npcinfo[i].shake = _ticks + 50;
						rcDest.left = rcDest.left + (int)(RND() * 3) - 1;
						rcDest.top = rcDest.top + (int)(RND() * 3) - 1;
					}

					_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
				}

				// wizard
				if (_npcinfo[i].spriteset == kMonsterPriest) {
					// if(_npcinfo[i].attacking == 0) {
					int cframe = _npcinfo[i].cframe;

					rcSrc.left = (int)(cframe / 4) * 24;
					rcSrc.top = wdir * 24;
					rcSrc.setWidth(24);
					rcSrc.setHeight(24);

					rcDest.left = npx;
					rcDest.top = npy;
					rcDest.setWidth(24);
					rcDest.setHeight(24);

					if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
						_npcinfo[i].shake = _ticks + 50;
						rcDest.left = rcDest.left + (int)(RND() * 3) - 1;
						rcDest.top = rcDest.top + (int)(RND() * 3) - 1;
					}
					_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					// } else {
					//cframe = _npcinfo[i].cattackframe;

					//rcSrc.left = (int)(cframe / 4) * 24;
					//rcSrc.top = wdir * 24;
					//rcSrc.setWidth(24);
					//rcSrc.setHeight(24);

					//rcDest.left = npx;
					//rcDest.top = npy;
					//rcDest.setWidth(24);
					//rcDest.setHeight(24);
					// _animsa(sprite)->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					// }
				}


				// yellow dragon
				if (_npcinfo[i].spriteset == kMonsterYellowDragon) {
					int cframe = _npcinfo[i].cframe;

					rcSrc.left = (int)(cframe / 4) * 24;
					rcSrc.top = wdir * 24;
					rcSrc.setWidth(24);
					rcSrc.setHeight(24);

					rcDest.left = npx;
					rcDest.top = npy;
					rcDest.setWidth(24);
					rcDest.setHeight(24);

					if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
						_npcinfo[i].shake = _ticks + 50;
						rcDest.left = rcDest.left + (int)(RND() * 3) - 1;
						rcDest.top = rcDest.top + (int)(RND() * 3) - 1;
					}
					_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
				}


				// dragon2
				if (_npcinfo[i].spriteset == kMonsterDragon2) {
					if (_npcinfo[i].attacking == 0) {
						_npcinfo[i].floating = _npcinfo[i].floating + 0.25 * _fpsr;
						while (_npcinfo[i].floating >= 16)
							_npcinfo[i].floating = _npcinfo[i].floating - 16;

						float frame = _npcinfo[i].frame;

						frame += 0.5 * _fpsr;
						while (frame >= 16)
							frame -= 16;

						int cframe = (int)(frame);
						if (cframe < 0)
							cframe = 0;

						_npcinfo[i].frame = frame;
						_npcinfo[i].cframe = cframe;

						rcSrc.left = 74 * wdir;
						rcSrc.top = (int)(cframe / 4) * 48;
						rcSrc.setWidth(74);
						rcSrc.setHeight(48);

						rcDest.left = npx + 12 - 37;
						rcDest.top = (float)(npy + 12 - 32 - 3 * sin(3.141592 * 2 * _npcinfo[i].floating / 16));
						rcDest.setWidth(24);
						rcDest.setHeight(24);

						if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
							_npcinfo[i].shake = _ticks + 50;
							rcDest.left = rcDest.left + (int)(RND() * 3) - 1;
							rcDest.top = rcDest.top + (int)(RND() * 3) - 1;
						}

						_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					} else {
						_npcinfo[i].floating = _npcinfo[i].floating + 0.25 * _fpsr;
						while (_npcinfo[i].floating >= 16)
							_npcinfo[i].floating = _npcinfo[i].floating - 16;

						int cframe = _npcinfo[i].cattackframe;

						rcSrc.left = 74 * wdir;
						rcSrc.top = (int)(cframe / 4) * 48;
						rcSrc.setWidth(74);
						rcSrc.setHeight(48);

						rcDest.left = npx + 12 - 37;
						rcDest.top = (float)(npy + 12 - 32 - 3 * sin(3.141592 * 2 * _npcinfo[i].floating / 16));
						rcDest.setWidth(24);
						rcDest.setHeight(24);

						_animsa[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}
				}

				// end boss
				if (_npcinfo[i].spriteset == kMonsterFinalBoss) {

					_npcinfo[i].floating = _npcinfo[i].floating + .3 * _fpsr;
					while (_npcinfo[i].floating >= 16)
						_npcinfo[i].floating = _npcinfo[i].floating - 16;


					float frame = _npcinfo[i].frame2;

					frame += 0.5 * _fpsr;
					while (frame >= 16)
						frame -= 16;

					_npcinfo[i].frame2 = frame;

					int sx = npx + 12 - 40;
					int sy = (float)(npy + 12 - 50 - 3 * sin(3.141592 * 2 * _npcinfo[i].floating / 16));

					for (int fr = 0; fr <= 3; fr++) {
						_spellimg->setAlpha(128 + (int)(RND() * 96), true);

						rcSrc.left = 16 * (int)(RND() * 2);
						rcSrc.top = 80;
						rcSrc.setWidth(16);
						rcSrc.setHeight(16);

						rcDest.left = sx + 32 + (int)(RND() * 3) - 1;
						rcDest.top = sy - (int)(RND() * 6);

						_spellimg->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}

					for (int ii = 0; ii <= 8; ii++) {
						for (int i2 = 0; i2 <= 3; i2++) {
							rcSrc.left = 16 * (int)(RND() * 2);
							rcSrc.top = 80;
							rcSrc.setWidth(16);
							rcSrc.setHeight(16);

							float fr3 = frame - 3 + i2;
							if (fr3 < 0)
								fr3 += 16;

							rcDest.left = (float)(sx + 36 + ii * 8 - ii * cos(3.14159 * 2 * (fr3 - ii) / 16) * 2);
							rcDest.top = (float)(sy + 16 + ii * sin(3.14159 * 2 * (fr3 - ii) / 16) * 3 - ii); //  * 4

							_spellimg->setAlpha(i2 / 3 * 224, true);

							_spellimg->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);

							int xloc = rcDest.left;
							int yloc = rcDest.top;
							int xdif = (xloc + 8) - (_player.px + 12);
							int ydif = (yloc + 8) - (_player.py + 12);

							if ((abs(xdif) < 8 && abs(ydif) < 8) && _player.pause < _ticks) {
								float damage = (float)_npcinfo[i].spelldamage * (1.0 + RND() * 0.5);

								if (_player.hp > 0) {
									damagePlayer(damage);
									if (config.effects) {
										int snd = playSound(_sfx[kSndFire]);
										setChannelVolume(snd, config.effectsvol);
									}
								}

							}


							rcDest.left = (float)(sx + 36 - ii * 8 + ii * cos(3.14159 * 2 * (fr3 - ii) / 16) * 2);
							rcDest.top = (float)(sy + 16 + ii * sin(3.14159 * 2 * (fr3 - ii) / 16) * 3 - ii); //  * 4

							_spellimg->setAlpha(i2 / 3 * 224, true);

							_spellimg->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);

							xloc = rcDest.left;
							yloc = rcDest.top;
							xdif = (xloc + 8) - (_player.px + 12);
							ydif = (yloc + 8) - (_player.py + 12);

							if ((abs(xdif) < 8 && abs(ydif) < 8) && _player.pause < _ticks) {
								float damage = (float)_npcinfo[i].spelldamage * (1.0 + RND() * 0.5);

								if (_player.hp > 0) {
									damagePlayer(damage);
									if (config.effects) {
										int snd = playSound(_sfx[kSndFire]);
										setChannelVolume(snd, config.effectsvol);
									}
								}
							}
						}
					}

					_spellimg->setAlpha(255, true);

					if (_npcinfo[i].attacking == 0) {
						int cframe = (int)(frame);
						rcSrc.left = 0;
						rcSrc.top = 72 * (int)(cframe / 4);
						rcSrc.setWidth(80);
						rcSrc.setHeight(72);

						rcDest.left = sx;
						rcDest.top = sy;

						if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
							_npcinfo[i].shake = _ticks + 50;
							rcDest.left = rcDest.top + (int)(RND() * 3) - 1;
							rcDest.left = rcDest.top + (int)(RND() * 3) - 1;
						}

						_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					} else {
						int cframe = (int)(_npcinfo[i].cattackframe);

						rcSrc.left = 0;
						rcSrc.top = 72 * (int)(cframe / 4);
						rcSrc.setWidth(80);
						rcSrc.setHeight(72);

						rcDest.left = sx;
						rcDest.top = sy;

						_animsa[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
					}
				}

				// bat kitty
				if (_npcinfo[i].spriteset == kMonsterBatKitty) {
					_npcinfo[i].floating = _npcinfo[i].floating + 1 * _fpsr;
					while (_npcinfo[i].floating >= 16)
						_npcinfo[i].floating = _npcinfo[i].floating - 16;

					float frame = _npcinfo[i].frame;

					frame += 0.5 * _fpsr;
					while (frame >= 16)
						frame -= 16;

					int cframe = (int)(frame);
					if (cframe < 0)
						cframe = 0;

					_npcinfo[i].frame = frame;
					_npcinfo[i].cframe = cframe;

					rcSrc.left = 0;
					rcSrc.top = 0;
					rcSrc.setWidth(99);
					rcSrc.setHeight(80);

					rcDest.left = npx + 12 - 50;
					rcDest.top = (float)(npy + 12 - 64 + 2 * sin(3.141592 * 2 * _npcinfo[i].floating / 16));
					rcDest.setWidth(99);
					rcDest.setHeight(80);

					if (_npcinfo[i].pause > _ticks && _npcinfo[i].shake < _ticks) {
						_npcinfo[i].shake = _ticks + 50;
						rcDest.left = rcDest.left + (int)(RND() * 3) - 1;
						rcDest.top = rcDest.top + (int)(RND() * 3) - 1;
					}

					_anims[sprite]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
				}

				rcDest.left = npx + 4;
				rcDest.top = npy + 22;
				rcDest.setWidth(16);
				rcDest.setHeight(4);

				_videobuffer->fillRect(rcDest, 0);

				rcDest.left = npx + 5;
				rcDest.top = npy + 23;


				int ww = 14 * _npcinfo[i].hp / _npcinfo[i].maxhp;
				if (ww > 14)
					ww = 14;
				if (ww < 1)
					ww = 1;

				rcDest.setWidth(ww);
				rcDest.setHeight(2);


				_videobuffer->fillRect(rcDest, ccc);

				bool pass = true;

				if (_npcinfo[i].spriteset == kMonsterBoss1)
					pass = false;
				if (pass)
					drawOver(npx, npy);

			}
		}
	}
}

void GriffonEngine::drawOver(int modx, int mody) {
	int npx = modx + 12;
	int npy = mody + 20;

	int lx = (int)npx / 16;
	int ly = (int)npy / 16;

	for (int xo = -1; xo <= 1; xo++) {
		for (int yo = -1; yo <= 1; yo++) {

			int sx = lx + xo;
			int sy = ly + yo;

			int sx2 = sx * 16;
			int sy2 = sy * 16;

			if (sx > -1 && sx < 40 && sy > -1 && sy < 24) {

				int curtile = _tileinfo[2][sx][sy][0];
				int curtilel = _tileinfo[2][sx][sy][1];

				if (curtile > 0) {
					curtile = curtile - 1;
					int curtilex = curtile % 20;
					int curtiley = (curtile - curtilex) / 20;

					rcSrc.left = curtilex * 16;
					rcSrc.top = curtiley * 16;
					rcSrc.setWidth(16);
					rcSrc.setHeight(16);

					rcDest.left = sx2;
					rcDest.top = sy2;
					rcDest.setWidth(16);
					rcDest.setHeight(16);

					bool pass = true;
					if (curtilel == 1) {
						for (int ff = 0; ff <= 5; ff++) {
							int ffa = 20 * 5 - 1 + ff * 20;
							int ffb = 20 * 5 + 4 + ff * 20;
							if (curtile > ffa && curtile < ffb)
								pass = false;
						}
					}

					if (pass)
						_tiles[curtilel]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
				}
			}
		}
	}
}

void GriffonEngine::drawPlayer() {
	int f = 0;
	if (_player.armour == 3)
		f = 13;

	if (!attacking) {
		rcSrc.left = (int)(_player.walkFrame / 4) * 24;
		rcSrc.top = _player.walkDir * 24;
		rcSrc.setWidth(24);
		rcSrc.setHeight(24);

		rcDest.left = (int)(_player.px);
		rcDest.top = (int)(_player.py);
		rcDest.setWidth(24);
		rcDest.setHeight(24);

		_anims[f]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);
	} else {
		rcSrc.left = (int)(_player.attackFrame / 4) * 24;
		rcSrc.top = _player.walkDir * 24;
		rcSrc.setWidth(24);
		rcSrc.setHeight(24);

		rcDest.left = (int)(_player.px);
		rcDest.top = (int)(_player.py);
		rcDest.setWidth(24);
		rcDest.setHeight(24);

		_animsa[f]->blit(*_videobuffer, rcDest.left, rcDest.top, Graphics::FLIP_NONE, &rcSrc);

	}

	long ccc = _videobuffer->format.RGBToColor(224, 224, 64);

	bool pass = false;
	if (_player.hp <= _player.maxHp * 0.25)
		pass = true;

	if (pass) {
		ccc = _videobuffer->format.RGBToColor(255, 255, 255);
		if ((int)(_player.hpflash) == 1)
			ccc = _videobuffer->format.RGBToColor(255, 0, 0);
	}

	int sss = 6;
	if (_player.foundSpell[0])
		sss = 8;
	int npx = _player.px;
	int npy = _player.py;
	rcDest.left = npx + 4;
	rcDest.top = npy + 22;
	rcDest.setWidth(16);
	rcDest.setHeight(sss);

	_videobuffer->fillRect(rcDest, 0);

	rcDest.left = npx + 5;
	rcDest.top = npy + 23;


	int ww = 14 * _player.hp / _player.maxHp;
	if (ww > 14)
		ww = 14;
	if (ww < 1)
		ww = 1;

	rcDest.setWidth(ww);
	rcDest.setHeight(2);

	_videobuffer->fillRect(rcDest, ccc);

	ccc = _videobuffer->format.RGBToColor(0, 224, 64);
	if (ABS(_player.attackStrength - 100) < kEpsilon)
		ccc = _videobuffer->format.RGBToColor(255, 128, 32);

	ww = 14 * _player.attackStrength / 100;
	if (ww > 14)
		ww = 14;

	int ww2 = 14 * _player.spellStrength / 100;
	if (ww2 > 14)
		ww2 = 14;

	rcDest.top = rcDest.top + 2;
	rcDest.setWidth(ww);
	rcDest.setHeight(2);

	_videobuffer->fillRect(rcDest, ccc);

	ccc = _videobuffer->format.RGBToColor(128, 0, 224);
	if (ABS(_player.spellStrength - 100) < kEpsilon)
		ccc = _videobuffer->format.RGBToColor(224, 0, 0);

	rcDest.top = rcDest.top + 2;
	rcDest.setWidth(ww2);
	rcDest.setHeight(2);

	_videobuffer->fillRect(rcDest, ccc);
}

void GriffonEngine::drawView() {
	_videobuffer->copyRectToSurface(_mapbg->getPixels(), _mapbg->pitch, 0, 0, _mapbg->w, _mapbg->h);

	updateSpellsUnder();

	drawAnims(0);

	// ------dontdrawover = special case to make boss work right in room 24
	if (dontdrawover == 1)
		drawAnims(1);
	drawNPCs(0);

	drawPlayer();

	drawNPCs(1);
	if (dontdrawover == 0)
		drawAnims(1);

	drawOver((int)_player.px, (int)_player.py);

	updateSpells();

	if (cloudson == 1) {
		Common::Rect rc;
		rc.left = (float)(256 + 256 * cos(3.141592 / 180 * clouddeg));
		rc.top = (float)(192 + 192 * sin(3.141592 / 180 * clouddeg));
		rc.setWidth(320);
		rc.setHeight(240);

		cloudimg->blit(*_videobuffer, 0, 0, Graphics::FLIP_NONE, &rc);
	}

	drawHud();

	g_system->copyRectToScreen(_videobuffer->getPixels(), _videobuffer->pitch, 0, 0, _videobuffer->w, _videobuffer->h);
}

void GriffonEngine::swash() {
	float y = 0.0;
	do {
		y = y + 1 * _fpsr;

		_videobuffer->setAlpha((int)y);
		_videobuffer->fillRect(Common::Rect(0, 0, _videobuffer->w, _videobuffer->h), 0);

		g_system->copyRectToScreen(_videobuffer->getPixels(), _videobuffer->pitch, 0, 0, _videobuffer->w, _videobuffer->h);
		g_system->updateScreen();

		g_system->getEventManager()->pollEvent(_event);
		g_system->delayMillis(10);

		_tickspassed = _ticks;
		_ticks = g_system->getMillis();

		_tickspassed = _ticks - _tickspassed;
		_fpsr = (float)_tickspassed / 24.0;

		_fp++;
		if (_ticks > _nextticks) {
			_nextticks = _ticks + 1000;
			_fps = _fp;
			_fp = 0;
		}

		clouddeg += 0.01 * _fpsr;
		while (clouddeg >= 360)
			clouddeg = clouddeg - 360;

		if (y > 10)
			break;
	} while (1);

	y = 0;
	do {
		y = y + 1 * _fpsr;

		_videobuffer->setAlpha((int)(y * 25));
		_mapbg->blit(*_videobuffer);

		if (cloudson == 1) {
			rcDest.left = (float)(256 + 256 * cos(3.141592 / 180 * clouddeg));
			rcDest.top = (float)(192 + 192 * sin(3.141592 / 180 * clouddeg));
			rcDest.setWidth(320);
			rcDest.setHeight(240);

			cloudimg->blit(*_videobuffer, 0, 0, Graphics::FLIP_NONE, &rcDest);
		}

		g_system->copyRectToScreen(_videobuffer->getPixels(), _videobuffer->pitch, 0, 0, _videobuffer->w, _videobuffer->h);
		g_system->updateScreen();

		g_system->getEventManager()->pollEvent(_event);
		g_system->delayMillis(10);

		_tickspassed = _ticks;
		_ticks = g_system->getMillis();

		_tickspassed = _ticks - _tickspassed;
		_fpsr = (float)_tickspassed / 24.0;

		_fp++;
		if (_ticks > _nextticks) {
			_nextticks = _ticks + 1000;
			_fps = _fp;
			_fp = 0;
		}

		clouddeg += 0.01 * _fpsr;
		while (clouddeg >= 360)
			clouddeg = clouddeg - 360;

		if (y > 10)
			break;
	} while (1);


	_videobuffer->setAlpha(255);
}


} // end of namespace Griffon
