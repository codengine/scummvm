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

#include "bagel/boflib/list.h"

namespace Bagel {

template<class T>
inline int CBofList<T>::GetActualCount() const {
#ifndef RELEASE_BUILD
	CBofListNode<T> *pNode;
	int nCount;

	nCount = 0;
	pNode = m_pHead;
	while (pNode != nullptr) {
		nCount++;
		pNode = pNode->m_pNext;
	}

	// There should be no discrepency
	assert(m_nNumItems == nCount);
#endif

	return m_nNumItems;
}

template<class T>
inline void CBofList<T>::SetNodeItem(int nNodeIndex, T tNewItem) {
	CBofListNode<T> *pNode = GetNode(nNodeIndex);

	assert(pNode != nullptr);

	pNode->SetNodeItem(tNewItem);
}

template<class T>
inline void CBofList<T>::InsertAfter(int nNodeIndex, T cNewItem) {
	assert(!IsEmpty());
	InsertAfter(GetNode(nNodeIndex), cNewItem);
}

template<class T>
inline void CBofList<T>::InsertAfter(CBofListNode<T> *pNode, T cNewItem) {
	assert(pNode != nullptr);
	assert(!IsEmpty());

	CBofListNode<T> *pNewNode;

	if (pNode == m_pTail) {
		AddToTail(cNewItem);
	} else {

		pNewNode = NewNode(cNewItem);
		pNewNode->m_pPrev = pNode;
		pNewNode->m_pNext = pNode->m_pNext;

		if (pNode->m_pNext != nullptr)
			pNode->m_pNext->m_pPrev = pNewNode;

		pNode->m_pNext = pNewNode;
	}

	// one more item in list
	assert(m_nNumItems != 0xFFFF);
	m_nNumItems++;

	RecalcItemList();
}

template<class T>
inline void CBofList<T>::NewItemList() {
	if (m_pItemList != nullptr) {
		BofFree(m_pItemList);
		m_pItemList = nullptr;
	}

	if (m_nNumItems != 0) {
		m_pItemList = (uint32 *)BofAlloc(m_nNumItems * sizeof(uint32));
	}
}

template<class T>
inline void CBofList<T>::InsertBefore(int nNodeIndex, T cNewItem) {
	assert(!IsEmpty());
	InsertBefore(GetNode(nNodeIndex), cNewItem);
}

template<class T>
inline void CBofList<T>::InsertBefore(CBofListNode<T> *pNode, T cNewItem) {
	assert(pNode != nullptr);
	assert(!IsEmpty());

	CBofListNode<T> *pNewNode;

	if (pNode == m_pHead) {
		AddToHead(cNewItem);
	} else {

		pNewNode = NewNode(cNewItem);

		pNewNode->m_pPrev = pNode->m_pPrev;
		pNewNode->m_pNext = pNode;

		if (pNode->m_pPrev != nullptr)
			pNode->m_pPrev->m_pNext = pNewNode;

		pNode->m_pPrev = pNewNode;
	}

	// one more item in list
	assert(m_nNumItems != 0xFFFF);
	m_nNumItems++;

	RecalcItemList();
}

template<class T>
inline CBofListNode<T> *CBofList<T>::GetActualHead() {
	CBofListNode<T> *pNode, *pLast;

	pLast = pNode = m_pHead;
	while (pNode != nullptr) {
		pLast = pNode;
		pNode = pNode->m_pPrev;
	}

	return pLast;
}

template<class T>
inline CBofListNode<T> *CBofList<T>::GetActualTail() {
	CBofListNode<T> *pNode, *pLast;

	pLast = pNode = m_pTail;
	while (pNode != nullptr) {
		pLast = pNode;
		pNode = pLast->m_pNext;
	}

	return pLast;
}

} // namespace Bagel
