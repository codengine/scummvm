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

#include "bagel/dialogs/start_dialog.h"
#include "bagel/baglib/bagel.h"
#include "bagel/baglib/button_object.h"
#include "bagel/boflib/sound.h"
#include "bagel/dialogs/opt_window.h"
#include "bagel/bagel.h"
#include "bagel/boflib/std_keys.h"

namespace Bagel {

struct ST_BUTTONS {
	const char *m_pszName;
	const char *m_pszUp;
	const char *m_pszDown;
	const char *m_pszFocus;
	const char *m_pszDisabled;
	int m_nLeft;
	int m_nTop;
	int m_nWidth;
	int m_nHeight;
	int m_nID;
};

static const ST_BUTTONS g_stStartButtons[NUM_START_BTNS] = {
	{ "Restore", "start1up.bmp", "start1dn.bmp", "start1gr.bmp", "start1gr.bmp", 110, 396, 120, 40, RESTORE_BTN },
	{ "Restart", "start2up.bmp", "start2dn.bmp", "start2up.bmp", "start2up.bmp", 238, 416, 120, 40, RESTART_BTN },
	{ "Quit", "start3up.bmp", "start3dn.bmp", "start3up.bmp", "start3up.bmp", 366, 436, 120, 40, QUIT_BTN }
};


CBagStartDialog::CBagStartDialog(const char *pszFileName, CBofWindow *pWin)
		: CBofDialog(pszFileName, pWin) {
	// Inits
	_lFlags &= ~BOFDLG_SAVEBACKGND;
	Common::fill(_buttons, _buttons + NUM_START_BTNS, (CBofBmpButton *)nullptr);
}

void CBagStartDialog::onInitDialog() {
	Assert(IsValidObject(this));

	CBofDialog::onInitDialog();
	setReturnValue(-1);

	// Halt all audio when user dies (and at start of game).
	CBofSound::StopSounds();

	// Save off the current game's palette
	_savePalette = CBofApp::GetApp()->GetPalette();

	// Insert ours
	CBofPalette *pPal = _pBackdrop->GetPalette();
	CBofApp::GetApp()->SetPalette(pPal);

	// Build all our buttons
	for (int i = 0; i < NUM_START_BTNS; i++) {
		Assert(_buttons[i] == nullptr);

		if ((_buttons[i] = new CBofBmpButton) != nullptr) {
			CBofBitmap *pUp = LoadBitmap(BuildSysDir(g_stStartButtons[i].m_pszUp), pPal);
			CBofBitmap *pDown = LoadBitmap(BuildSysDir(g_stStartButtons[i].m_pszDown), pPal);
			CBofBitmap *pFocus = LoadBitmap(BuildSysDir(g_stStartButtons[i].m_pszFocus), pPal);
			CBofBitmap *pDis = LoadBitmap(BuildSysDir(g_stStartButtons[i].m_pszDisabled), pPal);

			_buttons[i]->loadBitmaps(pUp, pDown, pFocus, pDis);
			_buttons[i]->create(g_stStartButtons[i].m_pszName, g_stStartButtons[i].m_nLeft, g_stStartButtons[i].m_nTop, g_stStartButtons[i].m_nWidth, g_stStartButtons[i].m_nHeight, this, g_stStartButtons[i].m_nID);
			_buttons[i]->Show();

		} else {
			ReportError(ERR_MEMORY);
			break;
		}
	}

	// Disable the restore button if there are no saved games
	CBagel *pApp = CBagel::getBagApp();
	if ((pApp != nullptr) && !g_engine->savesExist())
		_buttons[0]->setState(BUTTON_DISABLED);

	// Show System cursor
	CBagCursor::showSystemCursor();
}


void CBagStartDialog::onClose() {
	Assert(IsValidObject(this));

	CBagCursor::hideSystemCursor();

	// Destroy all buttons
	for (int i = 0; i < NUM_START_BTNS; i++) {
		if (_buttons[i] != nullptr) {
			delete _buttons[i];
			_buttons[i] = nullptr;
		}
	}

	killBackground();

	CBofDialog::onClose();
}


void CBagStartDialog::onPaint(CBofRect *pRect) {
	Assert(IsValidObject(this));

	PaintBackdrop(pRect);

	ValidateAnscestors();
}


void CBagStartDialog::onKeyHit(uint32 lKey, uint32 nRepCount) {
	Assert(IsValidObject(this));

	switch (lKey) {
	case BKEY_ESC:
		setReturnValue(QUIT_BTN);
		Close();
		break;

	default:
		CBofDialog::onKeyHit(lKey, nRepCount);
		break;
	}
}


void CBagStartDialog::OnBofButton(CBofObject *pObject, int nFlags) {
	Assert(IsValidObject(this));
	Assert(pObject != nullptr);

	if (nFlags != BUTTON_CLICKED)
		return;

	CBofBmpButton *pButton = (CBofBmpButton *)pObject;
	int nId = pButton->GetControlID();

	if (nId == RESTORE_BTN) {
		CBagel *pApp = CBagel::getBagApp();
		if (pApp != nullptr) {
			CBagMasterWin *pWin = pApp->getMasterWnd();

			if ((pWin != nullptr) && pWin->ShowRestoreDialog(this)) {
				Close();
			}
		}
	} else {
		setReturnValue(nId);
		Close();
	}
}

} // namespace Bagel
