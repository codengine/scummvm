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

#include "bagel/spacebar/full_wnd.h"
#include "bagel/baglib/bagel.h"
#include "bagel/baglib/pan_window.h"

namespace Bagel {
namespace SpaceBar {

CBagObject *SBarFullWnd::m_pWieldedObject = NULL;

SBarFullWnd::SBarFullWnd() {
	m_bAllowEventWorld = TRUE;
}

ERROR_CODE SBarFullWnd::Attach() {
	Assert(IsValidObject(this));

	// jwl 12.27.96 if we have something wielded, put it on hold for now.
	if (CBagPanWindow::m_pWieldBmp != NULL) {
		if ((m_pWieldedObject = CBagPanWindow::m_pWieldBmp->GetCurrObj()) != NULL) {
			SDEVMNGR->RemoveObject(CBagPanWindow::m_pWieldBmp->GetName(), m_pWieldedObject->GetRefName());
		}
	}

	if (CBagStorageDevWnd::Attach() == ERR_NONE) {
		if (!m_bAllowEventWorld) {
			g_bWaitOK = FALSE;
		}

		Show();
		InvalidateRect(NULL);
		UpdateWindow();
	}

	return (m_errCode);
}

ERROR_CODE SBarFullWnd::Detach() {
	CBagStorageDevWnd::Detach();

	if (m_pWieldedObject) {
		SDEVMNGR->AddObject(CBagPanWindow::m_pWieldBmp->GetName(), m_pWieldedObject->GetRefName());
		m_pWieldedObject = NULL;
	}

	return ERR_NONE;
}

VOID SBarFullWnd::OnTimer(UINT nTimerId) {
	Assert(IsValidObject(this));

	// If allowing EVENT_WLD to execute
	if (m_bAllowEventWorld) {
		CBagStorageDevWnd::OnTimer(nTimerId);

	} else {
		// Otherwise, don't allow turns to pass
		g_bWaitOK = FALSE;
	}
}

VOID SBarFullWnd::OnMouseMove(UINT nFlags, CBofPoint *pPoint, void *) {
	CBagStorageDevWnd::OnMouseMove(nFlags, pPoint);
}

} // namespace SpaceBar
} // namespace Bagel
