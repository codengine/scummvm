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

#include "bagel/spacebar/computer.h"
#include "bagel/baglib/master_win.h"
#include "bagel/baglib/button_object.h"
#include "bagel/boflib/sound.h"
#include "bagel/baglib/inv.h"

namespace Bagel {
namespace SpaceBar {

#if BOF_MAC || BOF_WINMAC
#define DRINKFILE       "$SBARDIR:BAR:CLOSEUP:BDCA:DRINKS.TXT"
#define INGRDFILE       "$SBARDIR:BAR:CLOSEUP:BDCA:ING.TXT"
#define BDCADIR         "$SBARDIR:BAR:CLOSEUP:BDCA:"
// scg 01.07.97
#if !PLAYWAVONMAC
#define ORDERAUDIO      "BDNDPSC1.SND"
#define REFUSEAUDIO     "BDTOORC1.SND"
#define ONAUDIO         "ON.SND"
#else
#define ORDERAUDIO      "BDNDPSC1.WAV"
#define REFUSEAUDIO     "BDTOORC1.WAV"
#define ONAUDIO         "ON.WAV"
#endif
#else
#define DRINKFILE       "$SBARDIR\\BAR\\CLOSEUP\\BDCA\\DRINKS.TXT"
#define INGRDFILE       "$SBARDIR\\BAR\\CLOSEUP\\BDCA\\ING.TXT"
#define BDCADIR         "$SBARDIR\\BAR\\CLOSEUP\\BDCA\\"
#define ORDERAUDIO      "BDNDPSC1.WAV"
#define REFUSEAUDIO     "BDTOORC1.WAV"
#define ONAUDIO         "ON.WAV"
#endif

#define szBroke "You have insufficient funds for that purchase."
#define szRefuse "The computer politely informs you that the House has a policy against two-fisted drinking."

CBofRect CompDisplay(165, 36, 430, 220);
static CBofRect gCompTextWindow(0, 0, 639, 21);

#define TWOLISTS (1)

typedef struct {
	const CHAR *m_pszName;
	const CHAR *m_pszUp;
	const CHAR *m_pszDown;
	const CHAR *m_pszFocus;
	const CHAR *m_pszDisabled;
	INT m_nLeft;
	INT m_nTop;
	INT m_nWidth;
	INT m_nHeight;
	INT m_nID;

} ST_BUTTONS;

static ST_BUTTONS g_stButtons[NUM_COMPBUTT] = {
	{ "Off", "bdnb1.bmp", "bdnb1.bmp", "bdnb1.bmp", "bdnb1.bmp", 144, 323, 92, 48, OFFBUT },
	{ "On", "bdnb2.bmp", "bdnb2.bmp", "bdnb2.bmp", "bdnb2.bmp",  144, 323, 92, 48, ONBUT },
	{ "Drinks", "bdnr1.bmp", "bdnr2.bmp", "bdnr1.bmp", "bdnr1.bmp", 238, 318, 112, 60, DRINKS },
	{ "Ingred", "bdnq1.bmp", "bdnq2.bmp", "bdnq1.bmp", "bdnq1.bmp",  238, 318, 112, 60, INGRED },
	{ "ListD", "bdnc1.bmp", "bdnc2.bmp", "bdnc2.bmp", "bdnc1.bmp", 354, 318, 112, 60, LISTD },
	{ "ListI", "bdnc4.bmp", "bdnc5.bmp", "bdnc4.bmp", "bdnc3.bmp", 354, 318, 112, 60, LISTI },
	{ "Order", "bdnd1.bmp", "bdnd2.bmp", "bdnd1.bmp", "bdnd1.bmp", 238, 378, 112, 60, ORDER },
	{ "Page Up", "bdns1.bmp", "bdns2.bmp", "bdns1.bmp", "bdns1.bmp", 188, 392, 44, 35, PGUP },
	{ "Page Down", "bdnt1.bmp", "bdnt2.bmp", "bdnt1.bmp", "bdnt1.bmp", 356, 392, 44, 35, PGDOWN },
	{ "Back", "backup.bmp", "backdn.bmp", "backup.bmp", "backup.bmp", 354, 318, 112, 60, BCBACK },
	{ "Help", "helpup.bmp", "helpdown.bmp", "helpup.bmp", "helpup.bmp", 31, 445, 200, 30, BCHELP },
	{ "Quit", "quitup.bmp", "quitdown.bmp", "quitup.bmp", "quitup.bmp", 407, 445, 200, 30, BCQUIT }
};

// Local functions
const CHAR *BuildBarcDir(const CHAR *pszFile);

SBarComputer::SBarComputer() : CBagStorageDevWnd() {
	m_pDrinkBuff = NULL;
	m_pIngBuff = NULL;
#if TWOLISTS
	m_pDrinkBox = NULL;
	m_pIngBox = NULL;
#else
	m_pLBox = NULL;
#endif
	m_pTBox = NULL;
	m_pDrinkList = NULL;
	m_pIngList = NULL;
	//  m_nSelection = -1;
	m_nDrinkSelect = -1;
	m_nIngSelect = -1;
	m_eMode = OFFMODE;
	m_ePrevMode = DRINKMODE;

	for (int i = 0; i < NUM_COMPBUTT; i++) {
		m_pButtons[i] = NULL;
	}

	// Call this thing a closeup so that time won't go by when
	// entering the closeup
	SetCloseup(TRUE);
}
SBarComputer::~SBarComputer() {
}

VOID SBarComputer::OnMainLoop() {
#if BOF_MAC
	CBofCursor::Show();
#endif
	if (m_bFirstPaint) {
		m_bFirstPaint = FALSE;
		AttachActiveObjects();
	}
}

VOID SBarComputer::EraseBackdrop() {
	InvalidateRect(&CompDisplay);
#if !BOF_MAC
	UpdateWindow();
#endif
}

VOID  SBarComputer::OnPaint(CBofRect *pRect) {
	ERROR_CODE errCode = ERR_NONE;

	if (GetBackdrop()) {
		Assert(GetWorkBmp() != NULL);
		// erase everything from the background
		GetWorkBmp()->Paint(GetBackdrop(), pRect, pRect);
		// paint all the objects to the background
		errCode = PaintStorageDevice(NULL, GetBackdrop(), pRect);
	}

	if (m_pTBox != NULL)
		m_pTBox->Display();

	// Paint the backdrop
	if (GetBackdrop())
		PaintBackdrop();

	// The backdrop is not painted with the state of the
	// on/off button taken into consideration... handle that here.

#if BOF_MAC
	if (m_eMode == DRINKMODE) {
		m_pButtons[ONBUT]->Paint(NULL);
	}
#endif
}

ERROR_CODE SBarComputer::Attach() {
	LogInfo("Attaching SBarComputer...");

	CBofPalette *pPal;
	ERROR_CODE          rc = ERR_NONE;

	if ((rc = CBagStorageDevWnd::Attach()) == ERR_NONE) {
		g_bWaitOK = FALSE;

		m_pDrinkList = new CBofList<SBarCompItem>;
		m_pIngList = new CBofList<SBarCompItem>;

		rc = ReadDrnkFile();
		if (rc == ERR_NONE)
			rc = ReadIngFile();

		// Create the list box that display the lists
		CreateDrinksListBox();
		CreateIngListBox();

		// Must have a valid backdrop by now
		Assert(m_pBackdrop != NULL);
		pPal = m_pBackdrop->GetPalette();

#if BOF_MAC
		Show(); // scg 02.02.97
		ForcePaint(); // scg 02.02.97
#endif
		// Build all our buttons
		for (int i = 0; i < NUM_COMPBUTT; i++) {
			if ((m_pButtons[i] = new CBofBmpButton) != NULL) {

				CBofBitmap *pUp, *pDown, *pFocus, *pDis;

				pUp = LoadBitmap(BuildBarcDir(g_stButtons[i].m_pszUp), pPal);
				pDown = LoadBitmap(BuildBarcDir(g_stButtons[i].m_pszDown), pPal);
				pFocus = LoadBitmap(BuildBarcDir(g_stButtons[i].m_pszFocus), pPal);
				pDis = LoadBitmap(BuildBarcDir(g_stButtons[i].m_pszDisabled), pPal);

				m_pButtons[i]->LoadBitmaps(pUp, pDown, pFocus, pDis);

#if BOF_MAC
				// Make this our own custom window such that no frame is drawn
				// around the window/button
				m_pButtons[i]->SetCustomWindow(true);
#endif
				m_pButtons[i]->Create(g_stButtons[i].m_pszName, g_stButtons[i].m_nLeft, g_stButtons[i].m_nTop, g_stButtons[i].m_nWidth, g_stButtons[i].m_nHeight, this, g_stButtons[i].m_nID);
#if BOF_MAC
				m_pButtons[i]->SelectPalette(pPal);
#endif

			}
		}

		Show();
		m_pButtons[OFFBUT]->Show();
		m_pButtons[BCHELP]->Show();
		m_pButtons[BCQUIT]->Show();

#if BOF_MAC
		m_pButtons[OFFBUT]->ForcePaint();
		m_pButtons[BCHELP]->ForcePaint();
		m_pButtons[BCQUIT]->ForcePaint();
#endif

#if !BOF_MAC
		// Order these windows properly... the show code does an invalidate.
		InvalidateRect(NULL);
#endif

		// Fix drink already selected bug
		//
		if (m_pDrinkBox != NULL) {
			m_pDrinkBox->SetSelectedItem(-1, FALSE);
		}
		if (m_pIngBox != NULL) {
			m_pIngBox->SetSelectedItem(-1, FALSE);
		}

		UpdateWindow();
	}

	CBofCursor::Show();

	return rc;
}

ERROR_CODE SBarComputer::Detach() {
	CBofCursor::Hide();

	if (m_pDrinkBuff != NULL) {
		delete m_pDrinkBuff;
		m_pDrinkBuff = NULL;
	}

	if (m_pIngBuff != NULL) {
		delete m_pIngBuff;
		m_pIngBuff = NULL;
	}

	DeleteListBox();
	DeleteTextBox();

	if (m_pDrinkList != NULL) {
		delete m_pDrinkList;
		m_pDrinkList = NULL;
	}

	if (m_pIngList != NULL) {
		delete m_pIngList;
		m_pIngList = NULL;
	}

	// Destroy all buttons
	for (int i = 0; i < NUM_COMPBUTT; i++) {

		if (m_pButtons[i] != NULL) {
			delete m_pButtons[i];
			m_pButtons[i] = NULL;
		}
	}

	m_nDrinkSelect = -1;
	m_nIngSelect = -1;

	m_eMode = OFFMODE;

	CBagStorageDevWnd::Detach();

#if PATCHSETENTRIES
	SetBlankingOption(FORCEFULLSCREEN);
#endif

	// Going into mr drinkmaster makes 1 turn go by
	VARMNGR->IncrementTimers();

	LogInfo("Detached SBarComputer");

	return ERR_NONE;
}

ERROR_CODE SBarComputer::ReadDrnkFile() {
	char *pPosInBuff;
	SBarCompItem *pCompItem;

	CBofString DrinkString(DRINKFILE);

	MACROREPLACE(DrinkString);

	// Open the text files
	CBofFile fpDrinkFile(DrinkString);
	if (fpDrinkFile.GetErrorCode() != ERR_NONE)
		return fpDrinkFile.GetErrorCode();

	// Check that buffers are null
	if (m_pDrinkBuff) {
		delete m_pDrinkBuff;
		m_pDrinkBuff = NULL;
	}

	// Allocate the buffers
	m_pDrinkBuff = (char *)BofAlloc(fpDrinkFile.GetLength() + 1);
	if (m_pDrinkBuff == NULL)
		return ERR_MEMORY;

	// Read the text file into buffers
	fpDrinkFile.Read(m_pDrinkBuff, fpDrinkFile.GetLength());

	// Get pointers indexing into Drink buffers
	pPosInBuff = m_pDrinkBuff;
	while (pPosInBuff < m_pDrinkBuff + fpDrinkFile.GetLength()) {
		pCompItem = new SBarCompItem();
		if (pCompItem) {
			pCompItem->m_pItem = NULL;
			pCompItem->m_pList = NULL;
			pCompItem->m_pDrink = NULL;
		}

		Assert(pCompItem != NULL);

		// get the item pointer pointing to item
		pCompItem->m_pItem = pPosInBuff;

		// search for @ - field delimeter
		while (*pPosInBuff != '@')
			pPosInBuff++;
		*pPosInBuff = '\0'; // replace with \0
		pPosInBuff++; // Increment past it

		// Get the list item pointing to list
		pCompItem->m_pList = pPosInBuff;

		// search for @ - field delimeter
		while (*pPosInBuff != '@')
			pPosInBuff++;
		*pPosInBuff = '\0'; // replace with \0
		pPosInBuff++; // Increment past it

		// Get the drink item pointing to list
		pCompItem->m_pDrink = pPosInBuff;

		// search for $ - record delimeter
		while (*pPosInBuff != '$')
			pPosInBuff++;
		*pPosInBuff = '\0'; // replace with \0
		pPosInBuff++;   // Increment past it

		// search record delimeter from beginning of next
		while ((pPosInBuff < m_pDrinkBuff + fpDrinkFile.GetLength()) && (*pPosInBuff != '$'))
			pPosInBuff++;

		pPosInBuff++;   // Increment past it

		m_pDrinkList->AddToTail(*pCompItem);
		delete pCompItem;

	}
	fpDrinkFile.Close();
	return ERR_NONE;
}

ERROR_CODE SBarComputer::ReadIngFile() {
	char *pPosInBuff;
	SBarCompItem *pCompItem;

	CBofString IngString(INGRDFILE);

	MACROREPLACE(IngString);

	// Open the text files
	CBofFile fpIngFile(IngString);
	if (fpIngFile.GetErrorCode() != ERR_NONE)
		return fpIngFile.GetErrorCode();

	// Check that buffers are null
	if (m_pIngBuff) {
		delete m_pIngBuff;
		m_pIngBuff = NULL;
	}

	// Allocate the buffers
	m_pIngBuff = (char *)BofAlloc(fpIngFile.GetLength() + 1);
	if (m_pIngBuff == NULL)
		return ERR_MEMORY;

	// Read the text file into buffers
	fpIngFile.Read(m_pIngBuff, fpIngFile.GetLength());

	// Get pointers indexing into Ingredient buffers
	pPosInBuff = m_pIngBuff;
	while (pPosInBuff < m_pIngBuff + fpIngFile.GetLength()) {
		pCompItem = new SBarCompItem();
		if (pCompItem) {
			pCompItem->m_pItem = NULL;
			pCompItem->m_pList = NULL;
			pCompItem->m_pDrink = NULL;
		}

		// get the item pointer pointing to item
		pCompItem->m_pItem = pPosInBuff;

		// search for @ - field delimeter
		while (*pPosInBuff != '@')
			pPosInBuff++;
		*pPosInBuff = '\0'; // replace with /0
		pPosInBuff++; // Increment past it

		// Get the list item pointing to list
		pCompItem->m_pList = pPosInBuff;

		// search for $ - record delimeter
		while (*pPosInBuff != '$')
			pPosInBuff++;
		*pPosInBuff = '\0'; // replace with /0
		pPosInBuff++;   // Increment past it

		// search record delimeter from beginning of next
		while ((pPosInBuff < m_pIngBuff + fpIngFile.GetLength()) && (*pPosInBuff != '$'))
			pPosInBuff++;

		pPosInBuff++;   // Increment past it

		m_pIngList->AddToTail(*pCompItem);
		delete pCompItem;
	}

	fpIngFile.Close();
	return ERR_NONE;
}

VOID SBarComputer::CreateTextBox(CBofString &newText) {
	if (m_pTBox == NULL) {
		m_pTBox = new CBofTextBox(GetBackdrop(), &CompDisplay, newText);
		Assert(m_pTBox != NULL);
		m_pTBox->SetTextAttribs(12, TEXT_NORMAL, RGB(0, 0, 0));
	} else {
		EraseBackdrop();
		m_pTBox->Erase();
		m_pTBox->FlushBackground();
		m_pTBox->SetText(newText);
	}

	if (m_pButtons[ONBUT]) {
		m_pButtons[ONBUT]->Show();
		m_pButtons[ONBUT]->InvalidateRect(NULL);
	}
}

VOID SBarComputer::DeleteTextBox() {
	if (m_pTBox) {
		delete m_pTBox;
		m_pTBox = NULL;
	}
}

VOID SBarComputer::DeleteListBox() {
	if (m_pDrinkBox) {
		delete m_pDrinkBox;
		m_pDrinkBox = NULL;
	}
	if (m_pIngBox) {
		delete m_pIngBox;
		m_pIngBox = NULL;
	}
}

ERROR_CODE SBarComputer::CreateDrinksListBox() {
	ERROR_CODE error = ERR_NONE;
	CBofPalette *pPal;

	if (m_pDrinkBox == NULL) { // We need to create one
		if ((m_pDrinkBox = new CBofListBox) != NULL) {
#if BOF_MAC
			// jwl 08.21.96 make this our own custom window such that no frame is drawn
			// around the window/button
			m_pDrinkBox->SetCustomWindow(true);
#endif
			error = m_pDrinkBox->Create("ListBox", &CompDisplay, this);
			if (error != ERR_NONE) {
				return error;
			}
			m_pDrinkBox->SetPointSize(12);
			m_pDrinkBox->SetItemHeight(20);

			pPal = m_pBackdrop->GetPalette();

			UBYTE PalIdx = pPal->GetNearestIndex(RGB(255, 0, 0));

			m_pDrinkBox->SetHighlightColor(pPal->GetColor(PalIdx));

			// populate listbox
			SBarCompItem CompItem;

			int numItems = m_pDrinkList->GetCount();

			for (int i = 0; i < numItems; ++i) {
				CompItem = m_pDrinkList->GetNodeItem(i);
				m_pDrinkBox->AddToTail(CBofString(CompItem.m_pItem), FALSE);
			}

		} else
			return ERR_MEMORY;
	}
	return error;
}

ERROR_CODE SBarComputer::CreateIngListBox() {
	ERROR_CODE error = ERR_NONE;
	CBofPalette *pPal;

	if (m_pIngBox == NULL) {
		// We need to create one
		if ((m_pIngBox = new CBofListBox) != NULL) {
#if BOF_MAC
			// jwl 08.21.96 make this our own custom window such that no frame is drawn
			// around the window/button
			m_pIngBox->SetCustomWindow(true);
#endif
			error = m_pIngBox->Create("ListBox", &CompDisplay, this);
			if (error != ERR_NONE) {
				return error;
			}
			m_pIngBox->SetPointSize(12);
			m_pIngBox->SetItemHeight(20);

			pPal = m_pBackdrop->GetPalette();

			UBYTE PalIdx = pPal->GetNearestIndex(RGB(255, 0, 0));

			m_pIngBox->SetHighlightColor(pPal->GetColor(PalIdx));

			SBarCompItem CompItem;

			int numItems = m_pIngList->GetCount();

			// populate listbox
			for (int i = 0; i < numItems; ++i) {
				CompItem = m_pIngList->GetNodeItem(i);
				m_pIngBox->AddToTail(CBofString(CompItem.m_pItem), FALSE);
			}

		} else
			return ERR_MEMORY;
	}

	return error;
}

VOID SBarComputer::OnBofListBox(CBofObject * /*pListBox*/, INT nItemIndex) {
	if (m_eMode == DRINKMODE) {
		m_nDrinkSelect = nItemIndex;

		// Prevents the white flash when the show window is performed
		m_pButtons[ORDER]->Select();
		m_pButtons[LISTD]->Select();

		m_pButtons[ORDER]->Show();
		m_pButtons[LISTD]->Show();

		// Paint to this button immediately, this minimizes the white
		// flash of bringing the window frontmost.
#if BOF_MAC
		m_pButtons[ORDER]->Paint(NULL);
		m_pButtons[LISTD]->Paint(NULL);
#endif
		m_pDrinkBox->RepaintAll();

	} else {
		m_nIngSelect = nItemIndex;
		// Prevents the white flash when the show window is performed
		m_pButtons[LISTI]->Select();

		m_pButtons[LISTI]->Show();
		// Paint to this button immediately, this minimizes the white
		// flash of bringing the window frontmost.
#if BOF_MAC
		m_pButtons[LISTI]->Paint(NULL);
#endif

		m_pIngBox->RepaintAll();

	}

#if !TWOLISTS
	// Highlight
	if (m_pLBox)
		m_pLBox->RepaintAll();
#endif

#if !BOF_MAC
#else
#endif
	ValidateAnscestors(NULL);
	if (m_eMode == DRINKMODE) {
		m_pButtons[LISTD]->InvalidateRect(NULL);
	} else {
		m_pButtons[LISTI]->InvalidateRect(NULL);
	}
	m_pButtons[ORDER]->InvalidateRect(NULL);
	m_pButtons[PGUP]->InvalidateRect(NULL);
	m_pButtons[PGDOWN]->InvalidateRect(NULL);

	UpdateWindow();
}

VOID SBarComputer::SetOn() {
	// Prevents the white flash when the show window is performed
	m_pButtons[ONBUT]->Select();

	m_pButtons[OFFBUT]->Hide();
	m_pButtons[ONBUT]->Show();

#if BOF_MAC
	// Whenever dealing with the on/off button, make sure to
	// paint the new bitmap.
	m_pButtons[ONBUT]->Paint(NULL);
#endif
	// Added switching-on sound
	BofPlaySound(BuildBarcDir(ONAUDIO), SOUND_MIX);

	SetDrink();
}

VOID SBarComputer::SetOff() {
	if (m_eMode != OFFMODE) {

		// Fix drink already selected bug
		// copied here from Attach bar 12-06-96
		if (m_pDrinkBox != NULL) {
			m_pDrinkBox->SetSelectedItem(-1, FALSE);
		}
		if (m_pIngBox != NULL) {
			m_pIngBox->SetSelectedItem(-1, FALSE);
		}

		m_nDrinkSelect = -1;

#if TWOLISTS
		m_pDrinkBox->Hide();
		m_pIngBox->Hide();
#else
		DeleteListBox();
#endif

		DeleteTextBox();

		m_eMode = OFFMODE;

		// Prevents the white flash when the show window is performed
		m_pButtons[OFFBUT]->Select();
		m_pButtons[ONBUT]->Hide();
		m_pButtons[OFFBUT]->Show();
		// bar 11/27/96 added switching-off sound
		BofPlaySound(BuildBarcDir(ONAUDIO), SOUND_MIX);
#if BOF_MAC
		// Whenever dealing with the on/off button, make sure to
		// paint the new bitmap.
		m_pButtons[OFFBUT]->Paint(NULL);
#endif
		for (int i = 1; i < NUM_COMPBUTT; i++) {
			// Hide all the buttons but HELP and QUIT
			if ((i != BCHELP) && (i != BCQUIT)) {
				m_pButtons[i]->Hide();
			}
		}
	}
	InvalidateRect(&CompDisplay);
	UpdateWindow();

}
VOID SBarComputer::SetDrink() {
//	ERROR_CODE error = ERR_NONE;

	if (m_eMode != DRINKMODE) {

#if !TWOLISTS

		SBarCompItem CompItem;
		int numItems;

		error = CreateListBox();
		Assert(error == ERR_NONE);

		numItems = m_pDrinkList->GetCount();

		// populate listbox
		for (int i = 0; i < numItems; ++i) {
			CompItem = m_pDrinkList->GetNodeItem(i);
			//CBofString cText(CompItem.m_pItem);
			// m_pLBox->AddToTail( cText, TRUE);
			m_pLBox->AddToTail(CBofString(CompItem.m_pItem), FALSE);
		}
		// show list box
		m_nSelection = -1;
#endif

		DeleteTextBox();

		// Prevents the white flash when the show window is performed
		m_pButtons[INGRED]->Select();

		m_pButtons[DRINKS]->Hide();
		m_pButtons[INGRED]->Show();
#if BOF_MAC
		m_pButtons[INGRED]->Paint(NULL);
#endif

		//m_nIngSelect = -1;
		m_pButtons[LISTI]->Hide();

		// Prevents the white flash when the show window is performed
		m_pButtons[PGUP]->Select();
		m_pButtons[PGDOWN]->Select();

		m_pButtons[PGUP]->Show();
		m_pButtons[PGDOWN]->Show();
#if BOF_MAC
		m_pButtons[PGUP]->Paint(NULL);
		m_pButtons[PGDOWN]->Paint(NULL);
#endif

		m_pButtons[BCBACK]->Hide();

		if (m_nDrinkSelect != -1) {
			// Prevents the white flash when the show window is performed
			m_pButtons[LISTD]->Select();

			m_pButtons[LISTD]->Show();
			// Paint to this button immediately, this minimizes the white
			// flash of bringing the window frontmost.
#if BOF_MAC
			m_pButtons[LISTD]->Paint(NULL);
#endif
		}

		m_pIngBox->Hide();

		m_pDrinkBox->Select();
		m_pDrinkBox->Show();

		EraseBackdrop();

#if BOF_MAC
#endif
		m_eMode = DRINKMODE;
	}
}

VOID SBarComputer::SetIng() {
	if (m_eMode != INGMODE) {
		DeleteTextBox();

#if !TWOLISTS

		SBarCompItem CompItem;
		int numItems;

		error = CreateListBox();
		Assert(error == ERR_NONE);

		numItems = m_pIngList->GetCount();

		// populate listbox
		for (int i = 0; i < numItems; ++i) {
			CompItem = m_pIngList->GetNodeItem(i);
			m_pLBox->AddToTail(CBofString(CompItem.m_pItem), FALSE);
		}

		// show list box
		m_nSelection = -1;
#endif

		// Prevents the white flash when the show window is performed
		m_pButtons[DRINKS]->Select();

		// set up buttons
		m_pButtons[INGRED]->Hide();
		m_pButtons[DRINKS]->Show();

		// Paint to this button immediately, this minimizes the white
		// flash of bringing the window frontmost.
#if BOF_MAC
		m_pButtons[DRINKS]->Paint(NULL);
#endif

		// hide list drink ingrediant button
		m_pButtons[LISTD]->Hide();
		//m_nDrinkSelect = -1;

		// Prevents the white flash when the show window is performed
		m_pButtons[PGUP]->Select();
		m_pButtons[PGDOWN]->Select();

		m_pButtons[PGUP]->Show();
		m_pButtons[PGDOWN]->Show();
		m_pButtons[BCBACK]->Hide();

		// Paint to this button immediately, this minimizes the white
		// flash of bringing the window frontmost.
#if BOF_MAC
		m_pButtons[PGUP]->Paint(NULL);
		m_pButtons[PGDOWN]->Paint(NULL);
#endif

		if (m_nIngSelect != -1) {
			// Prevents the white flash when the show window is performed
			m_pButtons[LISTI]->Select();
			m_pButtons[LISTI]->Show();
			// Paint to this button immediately, this minimizes the white
			// flash of bringing the window frontmost.
#if BOF_MAC
			m_pButtons[LISTI]->Paint(NULL);
#endif
		}

		m_pDrinkBox->Hide();
		m_pIngBox->Select();
		m_pIngBox->Show();

		// m_pLBox->UpdateWindow();
		EraseBackdrop();

		m_eMode = INGMODE;
	}
}


VOID SBarComputer::SetList() {
	SBarCompItem CompItem;

	if (m_eMode != LISTMODE) {

#if TWOLISTS
		m_pDrinkBox->Hide();
		m_pIngBox->Hide();
#else
		m_pLBox->Hide();
#endif
		if (m_eMode == DRINKMODE) {
			Assert(m_nDrinkSelect != -1);
			CompItem = m_pDrinkList->GetNodeItem(m_nDrinkSelect);

		} else {

			Assert(m_nIngSelect != -1);
			CompItem = m_pIngList->GetNodeItem(m_nIngSelect);
		}

		CBofString cText(CompItem.m_pList);

		m_pDrinkBox->Hide();
		m_pIngBox->Hide();

		CreateTextBox(cText);

		// Save off the previous mode for BACK
		m_ePrevMode = m_eMode;

		// Prevents the white flash when the show window is performed
		m_pButtons[BCBACK]->Select();
		// Set up buttons
		m_pButtons[PGDOWN]->Hide();
		m_pButtons[BCBACK]->Show();

		// Paint to this button immediately, this minimizes the white
		// flash of bringing the window frontmost.
#if BOF_MAC
		m_pButtons[BCBACK]->Paint(NULL);
#endif

		m_pButtons[LISTD]->Hide();
		m_pButtons[LISTI]->Hide();

		// m_pButtons[ORDER]->Hide();
		m_pButtons[PGUP]->Hide();
		m_pButtons[PGDOWN]->Hide();

		m_pTBox->SetPageLength(10);
		//m_pTBox->Display();

		m_eMode = LISTMODE;
	}
}

VOID SBarComputer::Back() {
	if (m_ePrevMode == DRINKMODE)
		SetDrink();
	else
		SetIng();

	m_pButtons[BCBACK]->Hide();
}

VOID SBarComputer::Order() {
	SBarCompItem CompItem;
	// CBagStorageDev* pInventory;

	if (m_nDrinkSelect != -1) {

		// Get the associated drink name
		CompItem = m_pDrinkList->GetNodeItem(m_nDrinkSelect);

		// Deduct 1 Nugget from the player
		// Read in their total nuggets from game
		CBagVar *pVar = NULL;
		CBagVar *pVar2 = NULL;

		pVar = VARMNGR->GetVariable("NUGGETS");
		pVar2 = VARMNGR->GetVariable("HAVEDRINK");

		if (pVar) {
			int nCredits = pVar->GetNumValue();
			int nHaveDrink = pVar2->GetNumValue();
			// If the player is out of nuggets, then put up a
			// text message.
			if (nCredits < 1) {
				CBofBitmap saveBackground(640, 480, (CBofPalette *)NULL, FALSE);
				saveBackground.CaptureScreen(this, &gCompTextWindow);
				PaintBeveledText(this, &gCompTextWindow, szBroke, FONT_15POINT, TEXT_NORMAL, RGB(255, 255, 255), JUSTIFY_WRAP, FORMAT_TOP_LEFT);
#if BOF_MAC
				while (!::Button())
					;
				::FlushEvents(everyEvent, 0);       // swallow the mousedown, don't want it processed
#else
				WaitForInput();
#endif
				saveBackground.Paint(this, &gCompTextWindow);
			} else {
				CBagStorageDev *pSoldierSDev = NULL;
				CBagObject *pDrinkObj = NULL;
				pSoldierSDev = SDEVMNGR->GetStorageDevice("SOLDIER_WLD");

				CBofBitmap saveBackgroundTwo(640, 480, (CBofPalette *)NULL, FALSE);
				saveBackgroundTwo.CaptureScreen(this, &gCompTextWindow);

				// Don't allow him to order if he has other drinks in the Soldier CIC or stash
				if (pSoldierSDev) {
					BOOL bRefuse = FALSE;
					if (pDrinkObj = pSoldierSDev->GetObject("DRINK1", TRUE))
						bRefuse = TRUE;
					else if (pDrinkObj = pSoldierSDev->GetObject("DRINK2", TRUE))
						bRefuse = TRUE;
					else if (pDrinkObj = pSoldierSDev->GetObject("DRINK3", TRUE))
						bRefuse = TRUE;
					else if (pDrinkObj = pSoldierSDev->GetObject("DRINK4", TRUE))
						bRefuse = TRUE;
					else if (pDrinkObj = pSoldierSDev->GetObject("DRINK5", TRUE))
						bRefuse = TRUE;
					else if (pDrinkObj = pSoldierSDev->GetObject("DRINK6", TRUE))
						bRefuse = TRUE;
					else if (pDrinkObj = pSoldierSDev->GetObject("DRINK7", TRUE))
						bRefuse = TRUE;
					else if (nHaveDrink > 0)
						bRefuse = TRUE;
					else {
						pSoldierSDev->ActivateLocalObject(CompItem.m_pDrink);
						BofPlaySound(BuildBarcDir(ORDERAUDIO), SOUND_MIX);
						pVar->SetValue(nCredits - 1);
						pVar2->SetValue(1);
					}
					if (bRefuse) {
						PaintBeveledText(this, &gCompTextWindow, szRefuse, FONT_15POINT, TEXT_NORMAL, RGB(255, 255, 255), JUSTIFY_WRAP, FORMAT_TOP_LEFT);
#if BOF_MAC
						while (!::Button())
							;
						::FlushEvents(everyEvent, 0);       // swallow the mousedown, don't want it processed
#else
						WaitForInput();
#endif
						saveBackgroundTwo.Paint(this, &gCompTextWindow);
					}
				}

			}
		}
	}
}

VOID SBarComputer::PageUp() {
#if TWOLISTS
	if (m_eMode == DRINKMODE) {
		if (m_pDrinkBox) {
			m_pDrinkBox->PageUp();
		}
	} else {
		if (m_pIngBox) {
			m_pIngBox->PageUp();
		}
	}
#else
	if (m_pLBox) {
		m_pLBox->PageUp();
	}
#endif
}

VOID SBarComputer::PageDown() {
#if TWOLISTS
	if (m_eMode == DRINKMODE) {
		if (m_pDrinkBox) {
			m_pDrinkBox->PageDown();
		}
	} else {
		if (m_pIngBox) {
			m_pIngBox->PageDown();
		}
	}
#else
	if (m_pLBox) {
		m_pLBox->PageDown();
	}
#endif
}

VOID SBarComputer::OnBofButton(CBofObject *pObject, INT nState) {
	Assert(IsValidObject(this));
	Assert(pObject != NULL);

	CBofButton *pButton;

	pButton = (CBofButton *)pObject;

	if (nState == BUTTON_CLICKED) {

		switch (pButton->GetControlID()) {
		case OFFBUT:
			SetOn();
			break;
		case ONBUT:
			SetOff();
			break;
		case DRINKS:
			SetDrink();
			break;
		case INGRED:
			SetIng();
			break;
		case LISTD:
			SetList();
			break;
		case LISTI:
			SetList();
			break;
		case ORDER:
			Order();
			break;
		case PGUP:
			PageUp();
			break;
		case PGDOWN:
			PageDown();
			break;
		case BCBACK:
			Back();
			break;
		case BCQUIT:
			LogInfo("\tClicked Quit");
			Close();
			break;

		case BCHELP:
			LogInfo("\tClicked Help");

			CBagel *pApp;
			CBagMasterWin *pWin;

			if ((pApp = CBagel::GetBagApp()) != NULL) {
				if ((pWin = pApp->GetMasterWnd()) != NULL) {
					pWin->OnHelp(BuildBarcDir("BARCOMP.TXT"));
				}
			}
			break;
		default:
			LogWarning(BuildString("Clicked Unknown Button with ID %d", pButton->GetControlID()));
			break;
		}
	}
}
VOID SBarComputer::OnKeyHit(ULONG lKey, ULONG nRepCount) {
	Assert(IsValidObject(this));

	switch (lKey) {

	case BKEY_UP:
#if TWOLISTS
		if (m_eMode == DRINKMODE) {

			if (m_pDrinkBox) {
				m_pDrinkBox->LineUp();
			}
		} else {

			if (m_pIngBox) {
				m_pIngBox->LineUp();
			}
		}
#else
		if (m_pLBox != NULL) {
			m_pLBox->LineUp();
		}
#endif

		break;

	case BKEY_DOWN:
#if TWOLISTS
		if (m_eMode == DRINKMODE) {

			if (m_pDrinkBox) {
				m_pDrinkBox->LineDown();
			}
		} else {
			if (m_pIngBox) {
				m_pIngBox->LineDown();
			}
		}
#else
		if (m_pLBox != NULL) {
			m_pLBox->LineDown();
		}
#endif

		break;

	case BKEY_PAGEUP:

#if TWOLISTS
		if (m_eMode == DRINKMODE) {

			if (m_pDrinkBox) {
				m_pDrinkBox->PageUp();
			}

		} else {
			if (m_pIngBox) {
				m_pIngBox->PageUp();
			}
		}
#else
		if (m_pLBox != NULL) {
			m_pLBox->PageUp();
		}
#endif

		break;

	case BKEY_PAGEDOWN:
#if TWOLISTS
		if (m_eMode == DRINKMODE) {

			if (m_pDrinkBox) {
				m_pDrinkBox->PageDown();
			}
		} else {

			if (m_pIngBox) {
				m_pIngBox->PageDown();
			}
		}
#else
		if (m_pLBox != NULL) {
			m_pLBox->PageDown();
		}
#endif

		break;
	default:
		CBagStorageDevWnd::OnKeyHit(lKey, nRepCount);
		break;
	}
}

VOID SBarComputer::OnMouseMove(UINT nFlags, CBofPoint *xPoint, void *) {
	// change it to the pointy hand
	CBagel::GetBagApp()->SetActiveCursor(1);

	// but let CBagStorageDevWnd check for EXIT area
	CBagStorageDevWnd::OnMouseMove(nFlags, xPoint);
}

const CHAR *BuildBarcDir(const CHAR *pszFile) {
	Assert(pszFile != NULL);

	// Where are the Bar Computer assets

	static CHAR szBuf[MAX_DIRPATH];

	Common::sprintf_s(szBuf, "%s%s%s", BDCADIR, PATH_DELIMETER, pszFile);

	CBofString sBarcDir(szBuf, MAX_DIRPATH);
	MACROREPLACE(sBarcDir);

	return &szBuf[0];
}

} // namespace SpaceBar
} // namespace Bagel
