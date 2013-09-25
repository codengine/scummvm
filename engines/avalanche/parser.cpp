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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This code is based on the original source code of Lord Avalot d'Argent version 1.3.
 * Copyright (c) 1994-1995 Mike, Mark and Thomas Thurman.
 */

#include "avalanche/avalanche.h"
#include "avalanche/parser.h"
#include "avalanche/dialogs.h"
#include "avalanche/timer.h"
#include "avalanche/animation.h"
#include "avalanche/background.h"
#include "avalanche/pingo.h"
#include "avalanche/sequence.h"

#include "common/textconsole.h"

#include <cstring>
#include <cmath>

namespace Avalanche {

Parser::Parser(AvalancheEngine *vm) {
	_vm = vm;
}

void Parser::init() {
	if (!_inputText.empty())
		_inputText.clear();
	_inputTextPos = 0;

	_vm->_avalot->_weirdWord = false;

	// Initailaze the vocabulary.
	// Verbs: 1-49
	_vocabulary[0].init(1, "EXAMINE");
	_vocabulary[1].init(1, "READ");
	_vocabulary[2].init(1, "XAM");
	_vocabulary[3].init(2, "OPEN");
	_vocabulary[4].init(2, "LEAVE");
	_vocabulary[5].init(2, "UNLOCK");
	_vocabulary[6].init(3, "PAUSE");
	_vocabulary[7].init(47, "TA"); // Early to avoid Take and Talk.
	_vocabulary[8].init(4, "TAKE");
	_vocabulary[9].init(4, "GET");
	_vocabulary[10].init(4, "PICK");
	_vocabulary[11].init(5, "DROP");
	_vocabulary[12].init(6, "INVENTORY");
	_vocabulary[13].init(7, "TALK");
	_vocabulary[14].init(7, "SAY");
	_vocabulary[15].init(7, "ASK");
	_vocabulary[16].init(8, "GIVE");
	_vocabulary[17].init(9, "DRINK");
	_vocabulary[18].init(9, "IMBIBE");
	_vocabulary[19].init(9, "DRAIN");
	_vocabulary[20].init(10, "LOAD");
	_vocabulary[21].init(10, "RESTORE");
	_vocabulary[22].init(11, "SAVE");
	_vocabulary[23].init(12, "BRIBE");
	_vocabulary[24].init(12, "PAY");
	_vocabulary[25].init(13, "LOOK");
	_vocabulary[26].init(14, "BREAK");
	_vocabulary[27].init(15, "QUIT");
	_vocabulary[28].init(15, "EXIT");
	_vocabulary[29].init(16, "SIT");
	_vocabulary[30].init(16, "SLEEP");
	_vocabulary[31].init(17, "STAND");

	_vocabulary[32].init(18, "GO");
	_vocabulary[33].init(19, "INFO");
	_vocabulary[34].init(20, "UNDRESS");
	_vocabulary[35].init(20, "DOFF");
	_vocabulary[36].init(21, "DRESS");
	_vocabulary[37].init(21, "WEAR");
	_vocabulary[38].init(21, "DON");
	_vocabulary[39].init(22, "PLAY");
	_vocabulary[40].init(22, "STRUM");
	_vocabulary[41].init(23, "RING");
	_vocabulary[42].init(24, "HELP");
	_vocabulary[43].init(25, "KENDAL");
	_vocabulary[44].init(26, "CAPYBARA");
	_vocabulary[45].init(27, "BOSS");
	_vocabulary[46].init(255, "NINET"); // block for NINETY
	_vocabulary[47].init(28, "URINATE");
	_vocabulary[48].init(28, "MINGITE");
	_vocabulary[49].init(29, "NINETY");
	_vocabulary[50].init(30, "ABRACADABRA");
	_vocabulary[51].init(30, "PLUGH");
	_vocabulary[52].init(30, "XYZZY");
	_vocabulary[53].init(30, "HOCUS");
	_vocabulary[54].init(30, "POCUS");
	_vocabulary[55].init(30, "IZZY");
	_vocabulary[56].init(30, "WIZZY");
	_vocabulary[57].init(30, "PLOVER");
	_vocabulary[58].init(30, "MELENKURION");
	_vocabulary[59].init(30, "ZORTON");
	_vocabulary[60].init(30, "BLERBI");
	_vocabulary[61].init(30, "THURB");
	_vocabulary[62].init(30, "SNOEZE");
	_vocabulary[63].init(30, "SAMOHT");
	_vocabulary[64].init(30, "NOSIDE");
	_vocabulary[65].init(30, "PHUGGG");
	_vocabulary[66].init(30, "KNERL");
	_vocabulary[67].init(30, "MAGIC");
	_vocabulary[68].init(30, "KLAETU");
	_vocabulary[69].init(30, "VODEL");
	_vocabulary[70].init(30, "BONESCROLLS");
	_vocabulary[71].init(30, "RADOF");

	_vocabulary[72].init(31, "RESTART");
	_vocabulary[73].init(32, "SWALLOW");
	_vocabulary[74].init(32, "EAT");
	_vocabulary[75].init(33, "LISTEN");
	_vocabulary[76].init(33, "HEAR");
	_vocabulary[77].init(34, "BUY");
	_vocabulary[78].init(34, "PURCHASE");
	_vocabulary[79].init(34, "ORDER");
	_vocabulary[80].init(34, "DEMAND");
	_vocabulary[81].init(35, "ATTACK");
	_vocabulary[82].init(35, "HIT");
	_vocabulary[83].init(35, "KILL");
	_vocabulary[84].init(35, "PUNCH");
	_vocabulary[85].init(35, "KICK");
	_vocabulary[86].init(35, "SHOOT");
	_vocabulary[87].init(35, "FIRE");

	// Passwords: 36
	_vocabulary[88].init(36, "TIROS");
	_vocabulary[89].init(36, "WORDY");
	_vocabulary[90].init(36, "STACK");
	_vocabulary[91].init(36, "SHADOW");
	_vocabulary[92].init(36, "OWL");
	_vocabulary[93].init(36, "ACORN");
	_vocabulary[94].init(36, "DOMESDAY");
	_vocabulary[95].init(36, "FLOPPY");
	_vocabulary[96].init(36, "DIODE");
	_vocabulary[97].init(36, "FIELD");
	_vocabulary[98].init(36, "COWSLIP");
	_vocabulary[99].init(36, "OSBYTE");
	_vocabulary[100].init(36, "OSCLI");
	_vocabulary[101].init(36, "TIMBER");
	_vocabulary[102].init(36, "ADVAL");
	_vocabulary[103].init(36, "NEUTRON");
	_vocabulary[104].init(36, "POSITRON");
	_vocabulary[105].init(36, "ELECTRON");
	_vocabulary[106].init(36, "CIRCUIT");
	_vocabulary[107].init(36, "AURUM");
	_vocabulary[108].init(36, "PETRIFY");
	_vocabulary[109].init(36, "EBBY");
	_vocabulary[110].init(36, "CATAPULT");
	_vocabulary[111].init(36, "GAMERS");
	_vocabulary[112].init(36, "FUDGE");
	_vocabulary[113].init(36, "CANDLE");
	_vocabulary[114].init(36, "BEEB");
	_vocabulary[115].init(36, "MICRO");
	_vocabulary[116].init(36, "SESAME");
	_vocabulary[117].init(36, "LORDSHIP");

	_vocabulary[118].init(37, "DIR");
	_vocabulary[119].init(37, "LS");
	_vocabulary[120].init(38, "DIE");
	_vocabulary[121].init(39, "SCORE");
	_vocabulary[122].init(40, "PUT");
	_vocabulary[123].init(40, "INSERT");
	_vocabulary[124].init(41, "KISS");
	_vocabulary[125].init(41, "SNOG");
	_vocabulary[126].init(41, "CUDDLE");
	_vocabulary[127].init(42, "CLIMB");
	_vocabulary[128].init(42, "CLAMBER");
	_vocabulary[129].init(43, "JUMP");
	_vocabulary[130].init(44, "HIGHSCORES");
	_vocabulary[131].init(44, "HISCORES");
	_vocabulary[132].init(45, "WAKEN");
	_vocabulary[133].init(45, "AWAKEN");
	_vocabulary[134].init(46, "HELLO");
	_vocabulary[135].init(46, "HI");
	_vocabulary[136].init(46, "YO");
	_vocabulary[137].init(47, "THANKS"); // = 47, "ta", which was defined earlier.

	// Nouns - Objects: 50-100
	_vocabulary[138].init(50, "WINE");
	_vocabulary[139].init(50, "BOOZE");
	_vocabulary[140].init(50, "NASTY");
	_vocabulary[141].init(50, "VINEGAR");
	_vocabulary[142].init(51, "MONEYBAG");
	_vocabulary[143].init(51, "BAG");
	_vocabulary[144].init(51, "CASH");
	_vocabulary[145].init(51, "DOSH");
	_vocabulary[146].init(51, "WALLET");
	_vocabulary[147].init(52, "BODKIN");
	_vocabulary[148].init(52, "DAGGER");
	_vocabulary[149].init(53, "POTION");
	_vocabulary[150].init(54, "CHASTITY");
	_vocabulary[151].init(54, "BELT");
	_vocabulary[152].init(55, "BOLT");
	_vocabulary[153].init(55, "ARROW");
	_vocabulary[154].init(55, "DART");
	_vocabulary[155].init(56, "CROSSBOW");
	_vocabulary[156].init(56, "BOW");
	_vocabulary[157].init(57, "LUTE");
	_vocabulary[158].init(58, "PILGRIM");
	_vocabulary[159].init(58, "BADGE");
	_vocabulary[160].init(59, "MUSHROOMS");
	_vocabulary[161].init(59, "TOADSTOOLS");
	_vocabulary[162].init(60, "KEY");
	_vocabulary[163].init(61, "BELL");
	_vocabulary[164].init(62, "PRESCRIPT");
	_vocabulary[165].init(62, "SCROLL");
	_vocabulary[166].init(62, "MESSAGE");
	_vocabulary[167].init(63, "PEN");
	_vocabulary[168].init(63, "QUILL");
	_vocabulary[169].init(64, "INK");
	_vocabulary[170].init(64, "INKPOT");
	_vocabulary[171].init(65, "CLOTHES");
	_vocabulary[172].init(66, "HABIT");
	_vocabulary[173].init(66, "DISGUISE");
	_vocabulary[174].init(67, "ONION");

	_vocabulary[175].init(99, "PASSWORD");

	// Objects from Also are placed between 101 and 131.
	// Nouns - People - Male: 150-174
	_vocabulary[176].init(150, "AVVY");
	_vocabulary[177].init(150, "AVALOT");
	_vocabulary[178].init(150, "YOURSELF");
	_vocabulary[179].init(150, "ME");
	_vocabulary[180].init(150, "MYSELF");
	_vocabulary[181].init(151, "SPLUDWICK");
	_vocabulary[182].init(151, "THOMAS");
	_vocabulary[183].init(151, "ALCHEMIST");
	_vocabulary[184].init(151, "CHEMIST");
	_vocabulary[185].init(152, "CRAPULUS");
	_vocabulary[186].init(152, "SERF");
	_vocabulary[187].init(152, "SLAVE");
	_vocabulary[188].init(158, "DU"); // Put in early for Baron DU Lustie to save confusion with Duck & Duke.
	_vocabulary[189].init(152, "CRAPPY");
	_vocabulary[190].init(153, "DUCK");
	_vocabulary[191].init(153, "DOCTOR");
	_vocabulary[192].init(154, "MALAGAUCHE");
	_vocabulary[193].init(155, "FRIAR");
	_vocabulary[194].init(155, "TUCK");
	_vocabulary[195].init(156, "ROBIN");
	_vocabulary[196].init(156, "HOOD");
	_vocabulary[197].init(157, "CWYTALOT");
	_vocabulary[198].init(157, "GUARD");
	_vocabulary[199].init(157, "BRIDGEKEEP");
	_vocabulary[200].init(158, "BARON");
	_vocabulary[201].init(158, "LUSTIE");
	_vocabulary[202].init(159, "DUKE");
	_vocabulary[203].init(159, "GRACE");
	_vocabulary[204].init(160, "DOGFOOD");
	_vocabulary[205].init(160, "MINSTREL");
	_vocabulary[206].init(161, "TRADER");
	_vocabulary[207].init(161, "SHOPKEEPER");
	_vocabulary[208].init(161, "STALLHOLDER");
	_vocabulary[209].init(162, "PILGRIM");
	_vocabulary[210].init(162, "IBYTHNETH");
	_vocabulary[211].init(163, "ABBOT");
	_vocabulary[212].init(163, "AYLES");
	_vocabulary[213].init(164, "PORT");
	_vocabulary[214].init(165, "SPURGE");
	_vocabulary[215].init(166, "JACQUES");
	_vocabulary[216].init(166, "SLEEPER");
	_vocabulary[217].init(166, "RINGER");

	// Nouns - People - Female: 175-199
	_vocabulary[218].init(175, "WIFE");
	_vocabulary[219].init(175, "ARKATA");
	_vocabulary[220].init(176, "GEDALODAVA");
	_vocabulary[221].init(176, "GEIDA");
	_vocabulary[222].init(176, "PRINCESS");
	_vocabulary[223].init(178, "WISE");
	_vocabulary[224].init(178, "WITCH");

	// Pronouns: 200-224
	_vocabulary[225].init(200, "HIM");
	_vocabulary[226].init(200, "MAN");
	_vocabulary[227].init(200, "GUY");
	_vocabulary[228].init(200, "DUDE");
	_vocabulary[229].init(200, "CHAP");
	_vocabulary[230].init(200, "FELLOW");
	_vocabulary[231].init(201, "HER");
	_vocabulary[232].init(201, "GIRL");
	_vocabulary[233].init(201, "WOMAN");
	_vocabulary[234].init(202, "IT");
	_vocabulary[235].init(202, "THING");
	_vocabulary[236].init(203, "MONK");
	_vocabulary[237].init(204, "BARMAN");
	_vocabulary[238].init(204, "BARTENDER");

	// Prepositions: 225-249
	_vocabulary[239].init(225, "TO");
	_vocabulary[240].init(226, "AT");
	_vocabulary[241].init(227, "UP");
	_vocabulary[242].init(228, "INTO");
	_vocabulary[243].init(228, "INSIDE");
	_vocabulary[244].init(229, "OFF");
	_vocabulary[245].init(230, "UP");
	_vocabulary[246].init(231, "DOWN");
	_vocabulary[247].init(232, "ON");

	// Please: 251
	_vocabulary[248].init(251, "PLEASE");

	// About: 252
	_vocabulary[249].init(252, "ABOUT");
	_vocabulary[250].init(252, "CONCERNING");

	// Swear words: 253
	/*		  I M P O R T A N T    M E S S A G E

	DO *NOT* READ THE LINES BELOW IF YOU ARE OF A SENSITIVE
	DISPOSITION. THOMAS IS *NOT* RESPONSIBLE FOR THEM.
	GOODNESS KNOWS WHO WROTE THEM.
	READ THEM AT YOUR OWN RISK. BETTER STILL, DON'T READ THEM.
	WHY ARE YOU SNOOPING AROUND IN MY PROGRAM, ANYWAY? */
	_vocabulary[251].init(253, "SHIT");
	_vocabulary[252].init(28 , "PISS");
	_vocabulary[253].init(28 , "PEE");
	_vocabulary[254].init(253, "FART");
	_vocabulary[255].init(253, "FUCK");
	_vocabulary[256].init(253, "BALLS");
	_vocabulary[257].init(253, "BLAST");
	_vocabulary[258].init(253, "BUGGER");
	_vocabulary[259].init(253, "KNICKERS");
	_vocabulary[260].init(253, "BLOODY");
	_vocabulary[261].init(253, "HELL");
	_vocabulary[262].init(253, "DAMN");
	_vocabulary[263].init(253, "SMEG");
	// ...and other even ruder words. You didn't read them, did you? Good.

	// Answer-back smart-alec words: 249
	_vocabulary[264].init(249, "YES");
	_vocabulary[265].init(249, "NO");
	_vocabulary[266].init(249, "BECAUSE");

	// Noise words: 255
	_vocabulary[267].init(255, "THE");
	_vocabulary[268].init(255, "A");
	_vocabulary[269].init(255, "NOW");
	_vocabulary[270].init(255, "SOME");
	_vocabulary[271].init(255, "AND");
	_vocabulary[272].init(255, "THAT");
	_vocabulary[273].init(255, "POCUS");
	_vocabulary[274].init(255, "HIS");
	_vocabulary[275].init(255, "THIS");
	_vocabulary[276].init(255, "SENTINEL"); // for "Ken SENT Me"
}

void Parser::handleInputText(const Common::Event &event) {
	byte inChar = event.kbd.ascii;
	warning("STUB: Parser::handleInputText()");
//	if (_vm->_menu->_activeMenuItem._activeNow) {
//		_vm->_menu->parseKey(inChar, _vm->_enhanced->extd);
//	} else {
		if (_inputText.size() < 76) {
			if ((inChar == '"') || (inChar == '`')) {
				if (_quote)
					inChar = '`';
				else
					inChar = '"';
				_quote = !_quote;  // quote - unquote
			}

			_inputText.insertChar(inChar, _inputTextPos);
			_inputTextPos++;
			plotText();
		} else
			_vm->_sound->blip();
//	}
}

void Parser::handleBackspace() {
	if (_vm->_menu->_activeMenuItem._activeNow)
		return;

	if (_inputTextPos > 0) {
		_inputTextPos--;
		if ((_inputText[_inputTextPos] == '"') || (_inputText[_inputTextPos] == '`'))
			_quote = !_quote;
		_inputText.deleteChar(_inputTextPos);
		plotText();
	} else
		_vm->_sound->blip();
}

void Parser::handleReturn() {
	if (_vm->_menu->_activeMenuItem._activeNow)
		tryDropdown();
	else if (!_inputText.empty()) {
		_inputTextBackup = _inputText;
		parse();
		doThat();
		_inputText.clear();
		wipeText();
	}
}

void Parser::handleFunctionKey(const Common::Event &event) {
	switch (event.kbd.keycode) {
	case Common::KEYCODE_F5: {
		_person = kPeoplePardon;
		_thing = kPardon;
		Common::String f5does = _vm->_avalot->f5Does();
		VerbCode verb = (VerbCode)f5does[0];
		_vm->_avalot->callVerb(verb);
		}
		break;
	case Common::KEYCODE_F7:
		_vm->_avalot->callVerb(kVerbCodeOpen);
		break;
	default:
		break;
	}
}

void Parser::plotText() {
	CursorMan.showMouse(false);
	cursorOff();

	_vm->_graphics->_surface.fillRect(Common::Rect(24, 161, 640, 169), kColorBlack); // Black out the line of the text.
	_vm->_graphics->drawText(_vm->_graphics->_surface, _inputText, _vm->_avalot->_font, 8, 24, 161, kColorWhite);

	cursorOn();
	CursorMan.showMouse(true);
}

void Parser::cursorOn() {
	if (_cursorState == true)
		return;
	drawCursor();
	_cursorState = true;
}

void Parser::cursorOff() {
	if (_cursorState == false)
		return;
	drawCursor();
	_cursorState = false;
}

void Parser::tryDropdown() {
	warning("STUB: Parser::tryDropdown()"); // TODO: Implement at the same time with Dropdown's keyboard handling.
}

int16 Parser::getPos(const Common::String &crit, const Common::String &src) {
	if (src.contains(crit))
		return strstr(src.c_str(),crit.c_str()) - src.c_str();
	else
		return -1;
}

void Parser::drawCursor() {
	// Draw the '_' character.
	for (int bit = 0; bit < 8; bit++)
		*(byte *)_vm->_graphics->_surface.getBasePtr(24 + _inputTextPos * 8 + 7 - bit, 168) = kColorWhite;
}

void Parser::wipeText() {
	CursorMan.showMouse(false);
	cursorOff();

	_vm->_graphics->_surface.fillRect(Common::Rect(24, 161, 640, 169), kColorBlack); // Black out the line of the text.

	_quote = true;
	_inputTextPos = 0;

	cursorOn();
	CursorMan.showMouse(true);
}

void Parser::clearWords() {
	for (int i = 0; i < 11; i++) {
		if (!_realWords[i].empty())
			_realWords[i].clear();
	}
}

byte Parser::wordNum(Common::String word) {
	if (word.empty())
		return 0;

	for (int32 i = kParserWordsNum - 1; i >= 0; i--) {
		if (_vocabulary[i]._word == word)
			return _vocabulary[i]._number;
	}

	// If not found as a whole, we look for it as a substring.
	for (int32 i = kParserWordsNum - 1; i >= 0; i--) {
		if (Common::String(_vocabulary[i]._word.c_str(), word.size()) == word)
			return _vocabulary[i]._number;
	}

	return kPardon;
}

void Parser::replace(Common::String oldChars, byte newChar) {
	int16 pos = getPos(oldChars, _thats);
	while (pos != -1) {
		if (newChar == 0)
			_thats.deleteChar(pos);
		else {
			for (uint i = pos; i < pos + oldChars.size(); i++)
				_thats.deleteChar(pos);
			_thats.insertChar(newChar, pos);
		}
		pos = getPos(oldChars, _thats);
	}
}

Common::String Parser::rank() {
	static const RankType kRanks[9] = {
		{0, "Beginner"},     {10, "Novice"},
		{20, "Improving"},   {35, "Not bad"},
		{50, "Passable"},    {65, "Good"},
		{80, "Experienced"}, {108, "The BEST!"},
		{32767, "copyright'93"}
	};

	for (int i = 0; i < 8; i++) {
		if ((_vm->_avalot->_dnascore >= kRanks[i]._score) && (_vm->_avalot->_dnascore < kRanks[i + 1]._score)) {
			return kRanks[i]._title;
		}
	}
	return "";
}

Common::String Parser::totalTime() {
	// There are 65535 clock ticks in a second, 1092.25 in a minute, and 65535 in an hour.
	const double ticksInOneSec = (double)(65535) / 3600;
	uint16 h, m, s;

	h = (uint16)floor(_vm->_avalot->_totalTime / ticksInOneSec); // No. of seconds.
	m = h % 3600;
	h /= 3600;
	s = m % 60;
	m /= 60;

	Common::String result = "You've been playing for ";
	if (h > 0)
		result += Common::String::format("%d hours, ", h);
	if ((m > 0) || (h != 0))
		result = Common::String::format("%d minutes and ", m);
	return result + Common::String::format("%d seconds", s);
}

void Parser::cheatParse(Common::String codes) {
	warning("STUB: Parser::cheatParse()");
}



void Parser::stripPunctuation(Common::String &word) {
	const char punct[] = "~`!@#$%^&*()_+-={}[]:\"|;'\\,./<>?";

	for (int i = 0; i < 32; i++) {
		for (;;) {
			int16 pos = getPos(Common::String(punct[i]), word);
			if (pos == -1)
				break;
			word.deleteChar(pos);
		}
	}
}

void Parser::displayWhat(byte target, bool animate, bool &ambiguous) {
	if (target == kPardon) {
		ambiguous = true;
		if (animate)
			_vm->_dialogs->displayText("Whom?");
		else
			_vm->_dialogs->displayText("What?");
	} else {
		if (animate) {
			Common::String tmpStr = Common::String::format("{ %s }", _vm->_avalot->getName((People)target).c_str());
			_vm->_dialogs->displayText(tmpStr);
		} else {
			Common::String z = _vm->_avalot->getItem(target);
			if (z != "") {
				Common::String tmpStr = Common::String::format("{ %s }", z.c_str());
				_vm->_dialogs->displayText(tmpStr);
			}
		}
	}
}

bool Parser::doPronouns() {
	bool ambiguous = false;

	for (uint i = 0; i < _thats.size(); i++) {
		byte wordCode = _thats[i];
		switch (wordCode) {
		case 200:
			displayWhat(_vm->_avalot->_him, true, ambiguous);
			_thats.setChar(_vm->_avalot->_him, i);
			break;
		case 201:
			displayWhat(_vm->_avalot->_her, true, ambiguous);
			_thats.setChar(_vm->_avalot->_her, i);
			break;
		case 202:
			displayWhat(_vm->_avalot->_it, false, ambiguous);
			_thats.setChar(_vm->_avalot->_it, i);
			break;
		}
	}

	return ambiguous;
}

void Parser::properNouns() {
	_inputText.toLowercase();

	// We set every word's first character to uppercase.
	for (uint i = 1; i < (_inputText.size() - 1); i++) {
		if (_inputText[i] == ' ')
			_inputText.setChar(toupper(_inputText[i + 1]), i + 1);
	}

	// And the first character as well.
	_inputText.setChar(toupper(_inputText[0]), 0);
}

void Parser::sayIt() {
	Common::String x = _inputText;
	x.setChar(toupper(x[0]), 0);
	Common::String tmpStr = Common::String::format("%c1%s.%c%c2", Dialogs::kControlRegister, x.c_str(), 
		                                           Dialogs::kControlSpeechBubble, Dialogs::kControlRegister);
	_vm->_dialogs->displayText(tmpStr);
}

void Parser::storeInterrogation(byte interrogation) {
	if (_inputText.empty())
		return;

	// Strip _inputText:
	while ((_inputText[0] == ' ') && (!_inputText.empty()))
		_inputText.deleteChar(0);
	while ((_inputText.lastChar() == ' ') && (!_inputText.empty()))
		_inputText.deleteLastChar();

	_vm->_timer->loseTimer(Timer::kReasonCardiffsurvey); // If you want to use any other timer, put this into the case statement.

	switch (interrogation) {
	case 1:
		_inputText.toLowercase();
		sayIt();
		_vm->_avalot->_favouriteDrink = _inputText;
		_vm->_avalot->_cardiffQuestionNum = 2;
		break;
	case 2:
		properNouns();
		sayIt();
		_vm->_avalot->_favouriteSong = _inputText;
		_vm->_avalot->_cardiffQuestionNum = 3;
		break;
	case 3:
		properNouns();
		sayIt();
		_vm->_avalot->_worstPlaceOnEarth = _inputText;
		_vm->_avalot->_cardiffQuestionNum = 4;
		break;
	case 4:
		_inputText.toLowercase();
		sayIt();
		if (!_vm->_avalot->_spareEvening.empty())
			_vm->_avalot->_spareEvening.clear();
		_vm->_avalot->_spareEvening = _inputText;
		_vm->_dialogs->displayScrollChain('z', 5); // His closing statement...
		_vm->_animation->_sprites[1].walkTo(3); // The end of the drawbridge
		_vm->_animation->_sprites[1]._vanishIfStill = true; // Then go away!
		_vm->_avalot->_magics[1]._operation = Avalot::kMagicNothing;
		_vm->_avalot->_cardiffQuestionNum = 5;
		break;
	case 99:
		//store_high(_inputText);
		warning("STUB: Parser::store_interrogation()");
		break;
	}

	if (interrogation < 4)
		_vm->_timer->cardiffSurvey();
}



void Parser::parse() {
	// First parsing - word identification
	if (!_thats.empty())
		_thats.clear();

	byte n = 0;
	_polite = false;
	_verb = kVerbCodePardon;
	_thing = kPardon;
	_thing2 = kPardon;
	_person = kPeoplePardon;
	clearWords();


	// A cheat mode attempt.
	if (_inputText[0] == '.') {
		cheatParse(_inputText);
		_thats = kNothing;
		return;
	}

	// Are we being interrogated right now?
	if (_vm->_avalot->_interrogation > 0) {
		storeInterrogation(_vm->_avalot->_interrogation);
		_vm->_avalot->_weirdWord = true;
		return;
	}

	// Actually process the command.
	Common::String inputText = _inputText + ' ';
	Common::String inputTextUpper = inputText;
	inputTextUpper.toUppercase();
	while (!inputTextUpper.empty()) {
		while ((!inputTextUpper.empty()) && (inputTextUpper[0] == ' ')) {
			inputTextUpper.deleteChar(0);
			inputText.deleteChar(0);
		}
		if (inputTextUpper.empty())
			break;

		// Get the following word of the strings.
		byte size = getPos(Common::String(' '), inputTextUpper) + 1;
		char *subStr = new char[size];
		Common::strlcpy(subStr, inputTextUpper.c_str(), size);
		Common::String thisword = subStr;
		Common::strlcpy(subStr, inputText.c_str(), size);
		_realWords[n] = subStr;
		delete[] subStr;

		stripPunctuation(inputTextUpper);

		bool notfound = true;

		// Check also[] first, which contains words about the actual room.
		if (!thisword.empty()) {
			for (int i = 0; i < 31; i++) {
				if ((_vm->_avalot->_also[i][0] != 0) && (getPos(',' + thisword, *_vm->_avalot->_also[i][0]) > -1)) {
					_thats += Common::String(99 + i);
					notfound = false;
				}
			}
		}

		// Check Accis's own table (words[]) for "global" commands.
		if (notfound) {
			byte answer = wordNum(thisword);
			if (answer == kPardon) {
				notfound = true;
				_thats = _thats + kPardon;
			} else
				_thats = _thats + answer;
			n++;
		}

		// Delete words we already processed.
		int16 spacePos = getPos(Common::String(' '), inputTextUpper);
		if (spacePos > -1) {
			for (int i = 0; i <= spacePos; i++)
				inputTextUpper.deleteChar(0);
		}

		spacePos = getPos(Common::String(' '), inputText);
		if (spacePos > -1) {
			for (int i = 0; i <= spacePos; i++)
				inputText.deleteChar(0);
		}
	}

	Common::String unkString;
	int16 pos = getPos(Common::String('\xFE'), _thats);
	if (pos > -1)
		unkString = _realWords[pos];
	else
		unkString.clear();

	// Replace words' codes that mean the same.
	replace(Common::String("\xFF"),     0); // zap noise words
	replace(Common::String("\xD\xE2"),  1); // "look at" = "examine"
	replace(Common::String("\xD\xE4"),  1); // "look in" = "examine"
	replace(Common::String("\x4\xE6"),  17); // "get up" = "stand"
	replace(Common::String("\x4\xE7"),  17); // "get down" = "stand"... well, why not?
	replace(Common::String("\x12\xE4"), 2); // "go in" = "open [door]"
	replace(Common::String("\x1C\xE5"), 253); // "P' off" is a swear word
	replace(Common::String("\x4\x6"),   6); // "Take inventory" (remember Colossal Adventure?)
	replace(Common::String("\x28\xE8"), 21); // "put on" = "don"
	replace(Common::String("\x4\xE5"),  20); // "take off" = "doff"

	// Words that could mean more than one _person
	if (_vm->_avalot->_room == kRoomNottsPub)
		replace(Common::String('\xCC'), 164); // Barman = Port
	else
		replace(Common::String('\xCC'), 154); // Barman = Malagauche

	switch (_vm->_avalot->_room) {
	case kRoomAylesOffice:
		replace(Common::String('\xCB'), 163); // Monk = Ayles
		break;
	case kRoomMusicRoom:
		replace(Common::String('\xCB'), 166); // Monk = Jacques
		break;
	default:
		replace(Common::String('\xCB'), 162); // Monk = Ibythneth
	}

	if (doPronouns()) {
		_vm->_avalot->_weirdWord = true;
		_thats = kNothing;
		return;
	}

	// Second parsing.
	if (!_vm->_avalot->_subject.empty())
		_vm->_avalot->_subject.clear();
	_vm->_avalot->_subjectNum = 0; // Find subject of conversation.

	for (int i = 0; (i < 11) && !_realWords[i].empty(); i++) {
		if ((_realWords[i][0] == '\'') || (_realWords[i][0] == '\"')) {
			_vm->_avalot->_subjectNum = (byte)_thats[i];
			_thats.setChar(kMoved, i);
			break;
		}
	}

	if ((_vm->_avalot->_subjectNum == 0) && !_thats.empty()) { // Still not found.
		for (uint16 i = 0; i < _thats.size() - 1; i++) {
			if ((byte)_thats[i] == 252) { // The word is "about", or something similar.
				_vm->_avalot->_subjectNum = (byte)_thats[i + 1];
				_thats.setChar(0, i + 1);
				break;
			}
		}
	}

	if ((_vm->_avalot->_subjectNum == 0) && !_thats.empty()) { // STILL not found! Must be the word after "say".
		for (uint16 i = 0; i < _thats.size() - 1; i++) {
			if (((byte)_thats[i] == 7) && ((byte)_thats[i + 1] != 0) && !((225 <= (byte)_thats[i + 1]) && ((byte)_thats[i + 1] <= 229))) {
				// SAY not followed by a preposition
				_vm->_avalot->_subjectNum = (byte)_thats[i + 1];
				_thats.setChar(0, i + 1);
				break;
			}
		}
	}

	for (int16 i = _thats.size() - 1; i >= 0; i--) { // Reverse order, so first will be used.
		byte curChar = (byte)_thats[i];
		if ((curChar == 253) || (curChar == 249) || ((1 <= curChar) && (curChar <= 49)))
			_verb = (VerbCode)curChar;
		else if ((50 <= curChar) && (curChar <= 149)) {
			_thing2 = _thing;
			_thing = curChar;
		} else if ((150 <= curChar) && (curChar <= 199))
			_person = (People)curChar;
		else if (curChar == 251)
			_polite = true;
	}

	if ((!unkString.empty()) && (_verb != kVerbCodeExam) && (_verb != kVerbCodeTalk) && (_verb != kVerbCodeSave) && (_verb != kVerbCodeLoad) && (_verb != kVerbCodeDir)) {
		Common::String tmpStr = Common::String::format("Sorry, but I have no idea what \"%s\" means. Can you rephrase it?", unkString.c_str());
		_vm->_dialogs->displayText(tmpStr);
		_vm->_avalot->_weirdWord = true;
	} else
		_vm->_avalot->_weirdWord = false;

	if (_thats.empty())
		_thats = kNothing;

	if (_thing != kPardon)
		_vm->_avalot->_it = _thing;

	if (_person != kPardon) {
		if (_person < kPeopleArkata)
			_vm->_avalot->_him = _person;
		else
			_vm->_avalot->_her = _person;
	}
}

void Parser::examineObject() {
	if (_thing != _vm->_avalot->_thinks)
		_vm->_avalot->thinkAbout(_thing, Avalot::kThing);
	switch (_thing) {
	case kObjectWine :
		switch (_vm->_avalot->_wineState) {// 4 is perfect wine. 0 is not holding the wine.
		case 1:
			_vm->_dialogs->displayScrollChain('t', 1); // Normal examine wine scroll
			break;
		case 2:
			_vm->_dialogs->displayScrollChain('d', 6); // Bad wine
			break;
		case 3:
			_vm->_dialogs->displayScrollChain('d', 7); // Vinegar
			break;
		}
		break;
	case kObjectOnion:
		if (_vm->_avalot->_rottenOnion)
			_vm->_dialogs->displayScrollChain('q', 21); // Yucky onion
		else
			_vm->_dialogs->displayScrollChain('t', 18);  // Normal onion
		break;
	default:
		_vm->_dialogs->displayScrollChain('t', _thing); // Ordinarily
	}
}

bool Parser::isPersonHere() { // Person equivalent of "holding".
	if ((_person == kPeoplePardon) || (_person == kPeopleNone) || (_vm->_avalot->getRoom(_person) == _vm->_avalot->_room))
		return true;
	else {
		Common::String tmpStr;
		if (_person < kPeopleArkata)
			tmpStr = "He isn't around at the moment.";
		else
			tmpStr = "She isn't around at the moment.";
		_vm->_dialogs->displayText(tmpStr);
		return false;
	}
}

void Parser::exampers() {
	if (isPersonHere()) {
		if (_thing != _vm->_avalot->_thinks)
			_vm->_avalot->thinkAbout(_person, Avalot::kPerson);

		byte newPerson = _person - 149;

		if ((_person == kPeopleDogfood) && _vm->_avalot->_wonNim)
			_vm->_dialogs->displayScrollChain('Q', 8); // "I'm Not Playing!"
		else if ((_person == kPeopleDuLustie) && _vm->_avalot->_lustieIsAsleep)
			_vm->_dialogs->displayScrollChain('Q', 65); // He's asleep.
		else
			_vm->_dialogs->displayScrollChain('p', newPerson);

		if ((_person == kPeopleAyles) && !_vm->_avalot->_aylesIsAwake)
			_vm->_dialogs->displayScrollChain('Q', 13);

		// CHECKME: Present in the original, but it doesn't make sense.
		// _person = newPerson;
	}
}

/**
 * Return whether Avvy is holding an object or not
 * @remarks	Originally called 'holding'
 */
bool Parser::isHolding() {
	if ((51 <= _thing) && (_thing <= 99)) // Also.
		return true;

	bool holdingResult = false;

	if (_thing > 100)
		_vm->_dialogs->displayText("Be reasonable!");
	else if (!_vm->_avalot->_objects[_thing - 1])  // Verbs that need "_thing" to be in the inventory.
		_vm->_dialogs->displayText("You're not holding it, Avvy.");
	else
		holdingResult = true;

	return holdingResult;
}

void Parser::openBox(bool isOpening) {
	if ((_vm->_avalot->_room == kRoomYours) && (_thing == 54)) {
		_vm->_background->draw(-1, -1, 4);

		_vm->_background->update();
		_vm->_animation->animLink();
		_vm->_graphics->refreshScreen();

		_vm->_system->delayMillis(55);

		if (!isOpening) {
			_vm->_background->draw(-1, -1, 5);
			_vm->_background->update();
			_vm->_animation->animLink();
			_vm->_graphics->refreshScreen();
		}
	}
}

void Parser::examine() {
	// EITHER it's an object OR it's an Also OR it's a _person OR it's something else.
	if ((_person == kPeoplePardon) && (_thing != kPardon)) {
		if (isHolding()) {
			// Remember: it's been slipped! Ie subtract 49.
			if ((1 <= _thing) && (_thing <= 49)) // Standard object
				examineObject();
			else if ((50 <= _thing) && (_thing <= 100)) { // Also _thing
				openBox(true);
				_vm->_dialogs->displayText(*_vm->_avalot->_also[_thing - 50][1]);
				openBox(false);
			}
		}
	} else if (_person != kPardon)
		exampers();
	else
		_vm->_dialogs->displayText("It's just as it looks on the picture.");  // Don't know: guess.
}

void Parser::inventory() {
	byte itemNum = 0;
	Common::String tmpStr = Common::String("You're carrying ");

	for (int i = 0; i < kObjectNum; i++) {
		if (_vm->_avalot->_objects[i]) {
			itemNum++;
			if (itemNum == _vm->_avalot->_carryNum)
				tmpStr += "and ";

			tmpStr += _vm->_avalot->getItem(i + 1);

			if ((i + 1) == _wearing)
				tmpStr += ", which you're wearing";

			if (itemNum < _vm->_avalot->_carryNum)
				tmpStr += ", ";
		}
	}

	if (_wearing == kNothing)
		tmpStr += Common::String::format("...%c%c...and you're stark naked!", Dialogs::kControlNewLine, Dialogs::kControlNewLine);
	else
		tmpStr += '.';

	_vm->_dialogs->displayText(tmpStr);
}

void Parser::swallow() { // Eat something.
	switch (_thing) {
	case kObjectWine:
		switch (_vm->_avalot->_wineState) { // 4 is perfect
		case 1:
			if (_vm->_avalot->_teetotal)  {
				_vm->_dialogs->displayScrollChain('D', 6);
				return;
			}
			_vm->_dialogs->displayScrollChain('U', 1);
			_vm->_pingo->wobble();
			_vm->_dialogs->displayScrollChain('U', 2);
			_vm->_avalot->_objects[kObjectWine - 1] = false;
			_vm->_avalot->refreshObjectList();
			drink();
			break;
		case 2:
		case 3:
			_vm->_dialogs->displayScrollChain('d', 8);
			break; // You can't drink it!
		}
		break;
	case kObjectPotion:
		_vm->_avalot->setBackgroundColor(4);
		_vm->_dialogs->displayScrollChain('U', 3);
		_vm->_avalot->gameOver();
		_vm->_avalot->setBackgroundColor(0);
		break;
	case kObjectInk:
		_vm->_dialogs->displayScrollChain('U', 4);
		break;
	case kObjectChastity:
		_vm->_dialogs->displayScrollChain('U', 5);
		break;
	case kObjectMushroom:
		_vm->_dialogs->displayScrollChain('U', 6);
		_vm->_avalot->gameOver();
		break;
	case kObjectOnion:
		if (_vm->_avalot->_rottenOnion)
			_vm->_dialogs->displayScrollChain('U', 11);
		else {
			_vm->_dialogs->displayScrollChain('U', 8);
			_vm->_avalot->_objects[kObjectOnion - 1] = false;
			_vm->_avalot->refreshObjectList();
		}
		break;
	default:
		if ((_vm->_avalot->_room == kRoomArgentPub) || (_vm->_avalot->_room == kRoomNottsPub))
			_vm->_dialogs->displayText("Try BUYing things before you drink them!");
		else
			_vm->_dialogs->displayText("The taste of it makes you retch!");
	}
}

void Parser::peopleInRoom() {
	byte numPeople = 0; // Number of people in the room.

	for (int i = 151; i < 179; i++) { // Start at 1 so we don't list Avvy himself!
		if (_vm->_avalot->getRoom((People)i) == _vm->_avalot->_room)
			numPeople++;
	}

	if (numPeople == 0) // If nobody's here, we can cut out straight away.
		return;

	Common::String tmpStr;
	byte actPerson = 0; // Actually listed people.
	for (int i = 151; i < 179; i++) {
		if (_vm->_avalot->getRoom((People)i) == _vm->_avalot->_room) {
			actPerson++;
			if (actPerson == 1) // First on the list.
				tmpStr = _vm->_avalot->getName((People)i);
			else if (actPerson < numPeople) // The middle...
				tmpStr += ", " + _vm->_avalot->getName((People)i);
			else // The end.
				tmpStr += " and " + _vm->_avalot->getName((People)i);
		}
	}

	if (numPeople == 1)
		tmpStr += " is";
	else
		tmpStr += " are";

	_vm->_dialogs->displayText(tmpStr + " here."); // End and display it.
}

void Parser::lookAround() {
	_vm->_dialogs->displayText(*_vm->_avalot->_also[0][1]);
	switch (_vm->_avalot->_room) {
	case kRoomSpludwicks:
		if (_vm->_avalot->_avariciusTalk > 0)
			_vm->_dialogs->displayScrollChain('q', 23);
		else
			peopleInRoom();
		break;
	case kRoomRobins:
		if (_vm->_avalot->_tiedUp)
			_vm->_dialogs->displayScrollChain('q', 38);
		if (_vm->_avalot->_mushroomGrowing)
			_vm->_dialogs->displayScrollChain('q', 55);
		break;
	case kRoomInsideCardiffCastle:
		if (!_vm->_avalot->_takenPen)
			_vm->_dialogs->displayScrollChain('q', 49);
		break;
	case kRoomLustiesRoom:
		if (_vm->_avalot->_lustieIsAsleep)
			_vm->_dialogs->displayScrollChain('q', 65);
		break;
	case kRoomCatacombs:
		switch (_vm->_avalot->_catacombY * 256 + _vm->_avalot->_catacombX) {
		case 258 :
			_vm->_dialogs->displayScrollChain('q', 80); // Inside art gallery.
			break;
		case 514 :
			_vm->_dialogs->displayScrollChain('q', 81); // Outside ditto.
			break;
		case 260 :
			_vm->_dialogs->displayScrollChain('q', 82); // Outside Geida's room.
			break;
		}
		break;
	default:
		peopleInRoom();
	}
}

void Parser::openDoor() {
	// Special cases.
	switch (_vm->_avalot->_room) {
	case kRoomYours:
		if (_vm->_animation->inField(1)) {
			// Opening the box.
			_thing = 54; // The box.
			_person = kPeoplePardon;
			examine();
			return;
		}
		break;
	case kRoomSpludwicks:
		if (_thing == 61) {
			_vm->_dialogs->displayScrollChain('q', 85);
			return;
		}
		break;
	}

	if ((!_vm->_avalot->_userMovesAvvy) && (_vm->_avalot->_room != kRoomLusties))
		return; // No doors can open if you can't move Avvy.

	for (int i = 0; i < 7; i++) {
		if (_vm->_animation->inField(i + 8)) {
			MagicType *portal = &_vm->_avalot->_portals[i];
			switch (portal->_operation) {
			case Avalot::kMagicExclaim:
				_vm->_animation->_sprites[0].bounce();
				_vm->_dialogs->displayScrollChain('x', portal->_data);
				break;
			case Avalot::kMagicTransport:
				_vm->_avalot->flipRoom((Room)((portal->_data) >> 8), portal->_data & 0x0F);
				break;
			case Avalot::kMagicUnfinished:
				_vm->_animation->_sprites[0].bounce();
				_vm->_dialogs->displayText("Sorry. This place is not available yet!");
				break;
			case Avalot::kMagicSpecial:
				_vm->_animation->callSpecial(portal->_data);
				break;
			case Avalot::kMagicOpenDoor:
				_vm->_avalot->openDoor((Room)(portal->_data >> 8), portal->_data & 0x0F, i + 9);
				break;
			}

			return;
		}
	}

	if (_vm->_avalot->_room == kRoomMap)
		_vm->_dialogs->displayText("Avvy, you can complete the whole game without ever going " \
				"to anywhere other than Argent, Birmingham, Cardiff, Nottingham and Norwich.");
	else
		_vm->_dialogs->displayText("Door? What door?");
}

void Parser::silly() {
	_vm->_dialogs->displayText("Don't be silly!");
}

void Parser::putProc() {
	if (!isHolding())
		return;

	_thing2 -= 49; // Slip the second object.
	char temp = _thing;
	_thing = _thing2;
	if (!isHolding())
		return;
	_thing = temp;

	// Thing is the _thing which you're putting in. _thing2 is where you're putting it.
	switch (_thing2) {
	case kObjectWine:
		if (_thing == kObjectOnion) {
			if (_vm->_avalot->_rottenOnion)
				_vm->_dialogs->displayText("That's a bit like shutting the stable door after the horse has bolted!");
			else { // Put onion into wine?
				if (_vm->_avalot->_wineState != 3) {
					Common::String tmpStr = Common::String::format("%cOignon au vin%c is a bit too strong for your tastes!", Dialogs::kControlItalic, Dialogs::kControlRoman);
					_vm->_dialogs->displayText(tmpStr);
				} else { // Put onion into vinegar! Yes!
					_vm->_avalot->_onionInVinegar = true;
					_vm->_avalot->incScore(7);
					_vm->_dialogs->displayScrollChain('u', 9);
				}
			}
		} else
			silly();
		break;

	case 54:
		if (_vm->_avalot->_room == kRoomYours) { // Put something into the box.
			if (_vm->_avalot->_boxContent != kNothing)
				_vm->_dialogs->displayText("There's something in the box already, Avvy. Try taking that out first.");
			else {
				switch (_thing) {
				case kObjectMoney:
					_vm->_dialogs->displayText("You'd better keep some ready cash on you!");
					break;
				case kObjectBell:
					_vm->_dialogs->displayText("That's a silly place to keep a bell.");
					break;
				case kObjectBodkin:
					_vm->_dialogs->displayText("But you might need it!");
					break;
				case kObjectOnion:
					_vm->_dialogs->displayText("Just give it to Spludwick, Avvy!");
					break;
				default: // Put the object into the box...
					if (_wearing == _thing) {
						Common::String tmpStr = Common::String::format("You'd better take %s off first!", _vm->_avalot->getItem(_thing).c_str());
						_vm->_dialogs->displayText(tmpStr);
					} else {
						openBox(true); // Open box.

						_vm->_avalot->_boxContent = _thing;
						_vm->_avalot->_objects[_thing - 1] = false;
						_vm->_avalot->refreshObjectList();
						_vm->_dialogs->displayText("OK, it's in the box.");

						openBox(false); // Shut box.
					}
				}
			}
		} else
			silly();
		break;

	default:
		silly();
	}
}

/**
 * Display text when ingredients are not in the right order
 * @remarks	Originally called 'not_in_order'
 */
void Parser::notInOrder() {
	Common::String itemStr = _vm->_avalot->getItem(_vm->_avalot->kSpludwicksOrder[_vm->_avalot->_givenToSpludwick]);
	Common::String tmpStr = Common::String::format("Sorry, I need the ingredients in the right order for this potion. " \
		"What I need next is %s%c2%c", itemStr.c_str(), Dialogs::kControlRegister, Dialogs::kControlSpeechBubble);
	_vm->_dialogs->displayText(tmpStr);
}

/**
 * Move Spludwick to cauldron
 * @remarks	Originally called 'go_to_cauldron'
 */
void Parser::goToCauldron() {
	_vm->_animation->_sprites[1]._callEachStepFl = false; // Stops Geida_Procs.
	_vm->_timer->addTimer(1, Timer::kProcSpludwickGoesToCauldron, Timer::kReasonSpludwickWalk);
	_vm->_animation->_sprites[1].walkTo(1);
}

/**
 * Check is it's possible to give something to Spludwick
 * @remarks	Originally called 'give2spludwick'
 */
bool Parser::giveToSpludwick() {
	if (_vm->_avalot->kSpludwicksOrder[_vm->_avalot->_givenToSpludwick] != _thing) {
		notInOrder();
		return false;
	}

	switch (_thing) {
	case kObjectOnion:
		_vm->_avalot->_objects[kObjectOnion - 1] = false;
		if (_vm->_avalot->_rottenOnion)
			_vm->_dialogs->displayScrollChain('q', 22);
		else {
			_vm->_avalot->_givenToSpludwick++;
			_vm->_dialogs->displayScrollChain('q', 20);
			goToCauldron();
			_vm->_avalot->incScore(3);
		}
		_vm->_avalot->refreshObjectList();
		break;
	case kObjectInk:
		_vm->_avalot->_objects[kObjectInk - 1] = false;
		_vm->_avalot->refreshObjectList();
		_vm->_avalot->_givenToSpludwick++;
		_vm->_dialogs->displayScrollChain('q', 24);
		goToCauldron();
		_vm->_avalot->incScore(3);
		break;
	case kObjectMushroom:
		_vm->_avalot->_objects[kObjectMushroom - 1] = false;
		_vm->_dialogs->displayScrollChain('q', 25);
		_vm->_avalot->incScore(5);
		_vm->_avalot->_givenToSpludwick++;
		goToCauldron();
		_vm->_avalot->_objects[kObjectPotion - 1] = true;
		_vm->_avalot->refreshObjectList();
		break;
	default:
		return true;
	}

	return false;
}

void Parser::drink() {
	_alcoholLevel += 1;
	if (_alcoholLevel == 5) {
		_vm->_avalot->_objects[kObjectKey - 1] = true; // Get the key.
		_vm->_avalot->_teetotal = true;
		_vm->_avalot->_avvyIsAwake = false;
		_vm->_avalot->_avvyInBed = true;
		_vm->_avalot->refreshObjectList();
		_vm->_avalot->dusk();
		_vm->_avalot->hangAroundForAWhile();
		_vm->_avalot->flipRoom(kRoomYours, 1);
		_vm->_avalot->setBackgroundColor(14);
		_vm->_animation->_sprites[0]._visible = false;
	}
}

void Parser::cardiffClimbing() {
	if (_vm->_avalot->_standingOnDais) { // Clamber up.
		_vm->_dialogs->displayText("You climb down, back onto the floor.");
		_vm->_avalot->_standingOnDais = false;
		_vm->_animation->appearPed(0, 2);
	} else if (_vm->_animation->inField(0)) { // Clamber down
		_vm->_dialogs->displayText("You clamber up onto the dais.");
		_vm->_avalot->_standingOnDais = true;
		_vm->_animation->appearPed(0, 1);
	} else
			_vm->_dialogs->displayText("Get a bit closer, Avvy.");
}

void Parser::already() {
	_vm->_dialogs->displayText("You're already standing!");
}

void Parser::standUp() {
	switch (_vm->_avalot->_room) {
	case kRoomYours: // Avvy isn't asleep.
		if (_vm->_avalot->_avvyIsAwake && _vm->_avalot->_avvyInBed) {  // But he's in bed.
			if (_vm->_avalot->_teetotal) {
				_vm->_dialogs->displayScrollChain('d', 12);
				_vm->_avalot->setBackgroundColor(0);
				_vm->_dialogs->displayScrollChain('d', 14);
			}
			_vm->_animation->_sprites[0]._visible = true;
			_vm->_avalot->_userMovesAvvy = true;
			_vm->_animation->appearPed(0, 1);
			_vm->_animation->setDirection(kDirLeft);
			_vm->_background->draw(-1, -1, 3); // Picture of empty pillow.
			_vm->_avalot->incScore(1);
			_vm->_avalot->_avvyInBed = false;
			_vm->_timer->loseTimer(Timer::kReasonArkataShouts);
		} else
			already();
		break;

	case kRoomInsideCardiffCastle:
		cardiffClimbing();
		break;

	case kRoomNottsPub:
		if (_vm->_avalot->_sittingInPub)  {
			_vm->_background->draw(-1, -1, 3); // Not sitting down.
			_vm->_animation->_sprites[0]._visible = true; // But standing up.
			_vm->_animation->appearPed(0, 3); // And walking away.
			_vm->_avalot->_sittingInPub = false; // Really not sitting down.
			_vm->_avalot->_userMovesAvvy = true; // And ambulant.
		} else
			already();
		break;
	default:
		already();
	}
}

void Parser::getProc(char thing) {
	switch (_vm->_avalot->_room) {
	case kRoomYours:
		if (_vm->_animation->inField(1)) {
			if (_vm->_avalot->_boxContent == thing) {
				_vm->_background->draw(-1, -1, 4);
				_vm->_dialogs->displayText("OK, I've got it.");
				_vm->_avalot->_objects[thing - 1] = true;
				_vm->_avalot->refreshObjectList();
				_vm->_avalot->_boxContent = kNothing;
				_vm->_background->draw(-1, -1, 5);
			} else {
				Common::String tmpStr = Common::String::format("I can't see %s in the box.", _vm->_avalot->getItem(thing).c_str());
				_vm->_dialogs->displayText(tmpStr);
			}
		} else
			_vm->_dialogs->displayScrollChain('q', 57);
		break;
	case kRoomInsideCardiffCastle:
		switch (thing) {
		case kObjectPen:
			if (_vm->_animation->inField(1)) { // Standing on the dais.
				if (_vm->_avalot->_takenPen)
					_vm->_dialogs->displayText("It's not there, Avvy.");
				else {
					// OK: we're taking the pen, and it's there.
					_vm->_background->draw(-1, -1, 3); // No pen there now.
					_vm->_animation->callSpecial(3); // Zap!
					_vm->_avalot->_takenPen = true;
					_vm->_avalot->_objects[kObjectPen - 1] = true;
					_vm->_avalot->refreshObjectList();
					_vm->_dialogs->displayText("Taken.");
				}
			} else if (_vm->_avalot->_standingOnDais)
				_vm->_dialogs->displayScrollChain('q', 53);
			else
				_vm->_dialogs->displayScrollChain('q', 51);
			break;
		case kObjectBolt:
			_vm->_dialogs->displayScrollChain('q', 52);
			break;
		default:
			_vm->_dialogs->displayScrollChain('q', 57);
		}
		break;
	case kRoomRobins:
		if ((thing == kObjectMushroom) & (_vm->_animation->inField(0)) & (_vm->_avalot->_mushroomGrowing)) {
			_vm->_background->draw(-1, -1, 2);
			_vm->_dialogs->displayText("Got it!");
			_vm->_avalot->_mushroomGrowing = false;
			_vm->_avalot->_takenMushroom = true;
			_vm->_avalot->_objects[kObjectMushroom - 1] = true;
			_vm->_avalot->refreshObjectList();
			_vm->_avalot->incScore(3);
		} else
			_vm->_dialogs->displayScrollChain('q', 57);
		break;
	default:
		_vm->_dialogs->displayScrollChain('q', 57);
	}
}

/**
 * Give the lute to Geida
 * @remarks	Originally called 'give_Geida_the_lute'
 */
void Parser::giveGeidaTheLute() {
	if (_vm->_avalot->_room != kRoomLustiesRoom) {
		Common::String tmpStr = Common::String::format("Not yet. Try later!%c2%c", Dialogs::kControlRegister, Dialogs::kControlSpeechBubble);
		_vm->_dialogs->displayText(tmpStr);
		return;
	}
	_vm->_avalot->_objects[kObjectLute - 1] = false;
	_vm->_avalot->refreshObjectList();
	_vm->_dialogs->displayScrollChain('q', 64); // She plays it.

	_vm->_timer->addTimer(1, Timer::kProcGiveLuteToGeida, Timer::kReasonGeidaSings);
	//_vm->_enid->backToBootstrap(4); TODO: Replace it with proper ScummVM-friendly function(s)!  Do not remove until then!
}

void Parser::playHarp() {
	if (_vm->_animation->inField(6))
		_vm->_dialogs->displayMusicalScroll();
	else
		_vm->_dialogs->displayText("Get a bit closer to it, Avvy!");
}

void Parser::winSequence() {
	_vm->_dialogs->displayScrollChain('q', 78);
	_vm->_sequence->firstShow(7);
	_vm->_sequence->thenShow(8);
	_vm->_sequence->thenShow(9);
	_vm->_sequence->startToClose();
	_vm->_timer->addTimer(30, Timer::kProcWinning, Timer::kReasonWinning);
}

Common::String Parser::personSpeaks() {
	if ((_person == kPeoplePardon) || (_person == kPeopleNone)) {
		if ((_vm->_avalot->_him == kPeoplePardon) || (_vm->_avalot->getRoom(_vm->_avalot->_him) != _vm->_avalot->_room))
			_person = _vm->_avalot->_her;
		else
			_person = _vm->_avalot->_him;
	}

	if (_vm->_avalot->getRoom(_person) != _vm->_avalot->_room) {
		return Common::String::format("%c1", Dialogs::kControlRegister); // Avvy himself!
	}

	bool found = false; // The _person we're looking for's code is in _person.
	Common::String tmpStr;

	for (int i = 0; i < _vm->_animation->kSpriteNumbMax; i++) {
		if (_vm->_animation->_sprites[i]._quick && ((_vm->_animation->_sprites[i]._stat._acciNum + 149) == _person)) {
			tmpStr += Common::String::format("%c%c", Dialogs::kControlRegister, '1' + i);
			found = true;
		}
	}

	if (found)
		return tmpStr;

	for (int i = 0; i < 16; i++) {
		if ((_vm->_avalot->kQuasipeds[i]._who == _person) && (_vm->_avalot->kQuasipeds[i]._room == _vm->_avalot->_room))
			tmpStr += Common::String::format("%c%c", Dialogs::kControlRegister, 'A' + i);
	}

	return tmpStr;
}

void Parser::heyThanks() {
	Common::String tmpStr = personSpeaks();
	tmpStr += Common::String::format("Hey, thanks!%c(But now, you've lost it!)", Dialogs::kControlSpeechBubble);
	_vm->_dialogs->displayText(tmpStr);
	_vm->_avalot->_objects[_thing - 1] = false;
}

/**
 * @remarks	Originally called 'do_that'
 */
void Parser::doThat() {
	static const Common::String booze[] = {"Bitter", "GIED", "Whisky", "Cider", "", "", "", "Mead"};
	static const char kWhat[] = "That's not possible!";

	if (_thats == Common::String(kNothing))  {
		if (!_thats.empty())
			_thats.clear();
		return;
	}

	if (_vm->_avalot->_weirdWord)
		return;

	if (_thing < 200)
		_thing -= 49; // "Slip"


	if ((_verb != kVerbCodeLoad) && (_verb != kVerbCodeSave) && (_verb != kVerbCodeQuit) && (_verb != kVerbCodeInfo) && (_verb != kVerbCodeHelp)
	&& (_verb != kVerbCodeLarrypass) && (_verb != kVerbCodePhaon) && (_verb != kVerbCodeBoss) && (_verb != kVerbCodeCheat) && (_verb != kVerbCodeRestart)
	&& (_verb != kVerbCodeDir) && (_verb != kVerbCodeScore) && (_verb != kVerbCodeHiscores) && (_verb != kVerbCodeSmartAlec)) {
		if (!_vm->_avalot->_alive) {
			_vm->_dialogs->displayText("You're dead, so don't talk. What are you, a ghost or something? Try restarting, or restoring a saved game!");
			return;
		}
		if (!_vm->_avalot->_avvyIsAwake  && (_verb != kVerbCodeDie) && (_verb != kVerbCodeExpletive) && (_verb != kVerbCodeWake)) {
			_vm->_dialogs->displayText("Talking in your sleep? Try waking up!");
			return;
		}
	}

	switch (_verb) {
	case kVerbCodeExam:
		examine();
		break;
	case kVerbCodeOpen:
		openDoor();
		break;
	case kVerbCodePause: { // Note that the original game doesn't care about the "O.K." box neither, it accepts clicks from everywhere on the screen to continue. Just like my code.
		Common::String tmpStr = Common::String::format("Game paused.%c%c%cPress Enter, Esc, or click the mouse on the `O.K.\" box to continue.", Dialogs::kControlCenter, Dialogs::kControlNewLine, Dialogs::kControlNewLine);
		_vm->_dialogs->displayText(tmpStr);
		}
		break;
	case kVerbCodeGet:
		if (_thing != kPardon) { // Legitimate try to pick something up.
			if (_vm->_avalot->_carryNum >= kCarryLimit)
				_vm->_dialogs->displayText("You can't carry any more!");
			else
				getProc(_thing);
		} else { // Not... ditto.
			if (_person != kPeoplePardon)
				_vm->_dialogs->displayText("You can't sweep folk off their feet!");
			else
				_vm->_dialogs->displayText("I assure you, you don't need it.");
		}
		break;
	case kVerbCodeDrop:
		_vm->_dialogs->displayText("Two years ago you dropped a florin in the street. Three days " \
				"later it was gone! So now you never leave ANYTHING lying around. OK?");
		break;
	case kVerbCodeInv:
		inventory();
		break;
	case kVerbCodeTalk:
		if (_person == kPeoplePardon) {
			if (_vm->_avalot->_subjectNum == 99) { // They typed "say password".
				Common::String tmpStr = Common::String::format("Yes, but what %cis%c the password?", Dialogs::kControlItalic, Dialogs::kControlRoman);
				_vm->_dialogs->displayText(tmpStr);
			} else if (((1 <= _vm->_avalot->_subjectNum) && (_vm->_avalot->_subjectNum <= 49)) || (_vm->_avalot->_subjectNum == 253) || (_vm->_avalot->_subjectNum == 249)) {
				_thats.deleteChar(0);

				for (int i = 0; i < 10; i++)
					_realWords[i] = _realWords[i + 1];

				_verb = (VerbCode)_vm->_avalot->_subjectNum;
				doThat();
				return;
			} else {
				_person = (People)_vm->_avalot->_subjectNum;
				_vm->_avalot->_subjectNum = 0;
				if ((_person == kPeopleNone) || (_person == kPeoplePardon))
					_vm->_dialogs->displayText("Talk to whom?");
				else if (isPersonHere())
					_vm->_dialogs->talkTo(_person);
			}
		} else if (isPersonHere())
			_vm->_dialogs->talkTo(_person);
		break;
	case kVerbCodeGive:
		if (isHolding()) {
			if (_person == kPeoplePardon)
				_vm->_dialogs->displayText("Give to whom?");
			else if (isPersonHere()) {
				switch (_thing) {
				case kObjectMoney :
					_vm->_dialogs->displayText("You can't bring yourself to give away your moneybag.");
					break;
				case kObjectBodkin:
				case kObjectBell:
				case kObjectClothes:
				case kObjectHabit :
					_vm->_dialogs->displayText("Don't give it away, it might be useful!");
					break;
				default:
					switch (_person) {
					case kPeopleCrapulus:
						if (_thing == kObjectWine) {
							_vm->_dialogs->displayText("Crapulus grabs the wine and gulps it down.");
							_vm->_avalot->_objects[kObjectWine - 1] = false;
						} else
							heyThanks();
						break;
					case kPeopleCwytalot:
						if ((_thing == kObjectCrossbow) || (_thing == kObjectBolt))
							_vm->_dialogs->displayText("You might be able to influence Cwytalot more if you used it!");
						else
							heyThanks();
						break;
					case kPeopleSpludwick:
						if (giveToSpludwick())
							heyThanks();
						break;
					case kPeopleIbythneth:
						if (_thing == kObjectBadge) {
							_vm->_dialogs->displayScrollChain('q', 32); // Thanks! Wow!
							_vm->_avalot->incScore(3);
							_vm->_avalot->_objects[kObjectBadge - 1] = false;
							_vm->_avalot->_objects[kObjectHabit - 1] = true;
							_vm->_avalot->_givenBadgeToIby = true;
							_vm->_background->draw(-1, -1, 7);
							_vm->_background->draw(-1, -1, 8);
						} else
							heyThanks();
						break;
					case kPeopleAyles:
						if (_vm->_avalot->_aylesIsAwake) {
							if (_thing == kObjectPen) {
								_vm->_avalot->_objects[kObjectPen - 1] = false;
								_vm->_dialogs->displayScrollChain('q', 54);
								_vm->_avalot->_objects[kObjectInk - 1] = true;
								_vm->_avalot->_givenPenToAyles = true;
								_vm->_avalot->refreshObjectList();
								_vm->_avalot->incScore(2);
							} else
								heyThanks();
						} else
							_vm->_dialogs->displayText("But he's asleep!");
						break;
					case kPeopleGeida:
						switch (_thing) {
						case kObjectPotion:
							_vm->_avalot->_objects[kObjectPotion - 1] = false;
							_vm->_dialogs->displayScrollChain('u', 16); // She drinks it.
							_vm->_avalot->incScore(2);
							_vm->_avalot->_givenPotionToGeida = true;
							_vm->_avalot->refreshObjectList();
							break;
						case kObjectLute:
							giveGeidaTheLute();
							break;
						default:
							heyThanks();
						}
						break;
					case kPeopleArkata:
						switch (_thing) {
						case kObjectPotion:
							if (_vm->_avalot->_givenPotionToGeida)
								winSequence();
							else
								_vm->_dialogs->displayScrollChain('q', 77); // That Geida woman!
							break;
						default:
							heyThanks();
						}
						break;
					default:
						heyThanks();
					}
				}
			}
			_vm->_avalot->refreshObjectList(); // Just in case...
		}
		break;

	case kVerbCodeEat:
	case kVerbCodeDrink:
		if (isHolding())
			swallow();
		break;

	case kVerbCodeLoad:
		break;
	case kVerbCodeSave:
		break;
	// We don't handle these two because we use ScummVM's save/load system.

	case kVerbCodePay:
		_vm->_dialogs->displayText("No money need change hands.");
		break;
	case kVerbCodeLook:
		lookAround();
		break;
	case kVerbCodeBreak:
		_vm->_dialogs->displayText("Vandalism is prohibited within this game!");
		break;
	case kVerbCodeQuit: // quit
		if (!_polite)
			_vm->_dialogs->displayText("How about a `please\", Avvy?");
		else {
			Common::String tmpStr = Common::String::format("%cC%cDo you really want to quit?", Dialogs::kControlRegister, Dialogs::kControlIcon);
			if (_vm->_dialogs->displayQuestion(tmpStr))
				_vm->_avalot->_letMeOut = true;
		}
		break;
	case kVerbCodeGo:
		_vm->_dialogs->displayText("Just use the arrow keys to walk there.");
		break;
	case kVerbCodeInfo: {
		_vm->_dialogs->_aboutBox = true;

		Common::String toDisplay;
		for (int i = 0; i < 7; i++)
			toDisplay += Dialogs::kControlNewLine;
		toDisplay = toDisplay + "LORD AVALOT D'ARGENT" + Dialogs::kControlCenter + Dialogs::kControlNewLine
			+ "The medi\x91val descendant of" + Dialogs::kControlNewLine
			+ "Denarius Avaricius Sextus" + Dialogs::kControlNewLine + Dialogs::kControlNewLine
			+ "version " + _vm->_avalot->kVersionNum + Dialogs::kControlNewLine + Dialogs::kControlNewLine + "Copyright \xEF "
			+ _vm->_avalot->kCopyright + ", Mark, Mike and Thomas Thurman." + Dialogs::kControlRegister + 'Y' + Dialogs::kControlIcon;
		_vm->_dialogs->displayText(toDisplay);
		_vm->_dialogs->_aboutBox = false;
		}
		break;
	case kVerbCodeUndress:
		if (_wearing == kNothing)
			_vm->_dialogs->displayText("You're already stark naked!");
		else if (_vm->_avalot->_avvysInTheCupboard) {
			Common::String tmpStr = Common::String::format("You take off %s.", _vm->_avalot->getItem(_wearing).c_str());
			_vm->_dialogs->displayText(tmpStr);
			_wearing = kNothing;
			_vm->_avalot->refreshObjectList();
		} else
			_vm->_dialogs->displayText("Hadn't you better find somewhere more private, Avvy?");
		break;
	case kVerbCodeWear:
		if (isHolding()) { // Wear something.
			switch (_thing) {
			case kObjectChastity:
				// \? are used to avoid that ??! is parsed as a trigraph
				_vm->_dialogs->displayText("Hey, what kind of a weirdo are you\?\?!");
				break;
			case kObjectClothes:
			case kObjectHabit: { // Change this!
				if (_wearing != kNothing) {
					if (_wearing == _thing)
						_vm->_dialogs->displayText("You're already wearing that.");
					else
						_vm->_dialogs->displayText("You'll be rather warm wearing two sets of clothes!");
					return;
				} else
					_wearing = _thing;

				_vm->_avalot->refreshObjectList();

				byte i;
				if (_thing == kObjectHabit)
					i = 3;
				else
					i = 0;
				Avalanche::AnimationType *spr = &_vm->_animation->_sprites[0];
				if (spr->_id != i) {
					int16 x = spr->_x;
					int16 y = spr->_y;
					spr->remove();
					spr->init(i, true, _vm->_animation);
					spr->appear(x, y, kDirLeft);
					spr->_visible = false;
				}
				}
				break;
			default:
				_vm->_dialogs->displayText(kWhat);
			}
		}
		break;
	case kVerbCodePlay:
		if (_thing == kPardon) {
			switch (_vm->_avalot->_room) { // They just typed "play"...
			case kRoomArgentPub: // ...in the pub, => play Nim.
				warning("STUB: Parser::doThat() - case kVerbCodeplay - play_nim()");
				// play_nim();
				// The following parts are copied from play_nim().
				// The player automatically wins the game everytime he wins, until I implement the mini-game.

				if (_vm->_avalot->_wonNim) { // Already won the game.
					_vm->_dialogs->displayScrollChain('Q', 6);
					return;
				}

				if (!_vm->_avalot->_askedDogfoodAboutNim) {
					_vm->_dialogs->displayScrollChain('q', 84);
					return;
				}

				_vm->_dialogs->displayScrollChain('Q', 3);
				_playedNim++;

				// You won - strange!
				_vm->_dialogs->displayScrollChain('Q', 7); // You won! Give us a lute!
				_vm->_avalot->_objects[kObjectLute - 1] = true;
				_vm->_avalot->refreshObjectList();
				_vm->_avalot->_wonNim = true;
				_vm->_background->draw(-1, -1, 0); // Show the settle with no lute on it.
				_vm->_avalot->incScore(7); // 7 points for winning!

				if (_playedNim == 1)
					_vm->_avalot->incScore(3); // 3 points for playing your 1st game.

				// A warning to the player that there should have been a mini-game. TODO: Remove it later!!!
				_vm->_dialogs->displayText(Common::String("P.S.: There should have been the mini-game called \"Nim\", but I haven't implemented it yet: you win and get the lute automatically.")
					+ Dialogs::kControlNewLine + Dialogs::kControlNewLine + "Peter (uruk)");
				break;
			case kRoomMusicRoom:
				playHarp();
				break;
			}
		} else if (isHolding()) {
			switch (_thing) {
			case kObjectLute :
					_vm->_dialogs->displayScrollChain('U', 7);

					if (_vm->_avalot->getRoom(kPeopleCwytalot) == _vm->_avalot->_room)
						_vm->_dialogs->displayScrollChain('U', 10);

					if (_vm->_avalot->getRoom(kPeopleDuLustie) == _vm->_avalot->_room)
						_vm->_dialogs->displayScrollChain('U', 15);
				break;
			case 52:
				if (_vm->_avalot->_room == kRoomMusicRoom)
					playHarp();
				else
					_vm->_dialogs->displayText(kWhat);
				break;
			case 55:
				if (_vm->_avalot->_room == kRoomArgentPub)
					// play_nim();
					warning("STUB: Parser::doThat() - case kVerbCodeplay - play_nim()");
				else
					_vm->_dialogs->displayText(kWhat);
				break;
			default:
				_vm->_dialogs->displayText(kWhat);
			}
		}
		break;
	case kVerbCodeRing:
		if (isHolding()) {
			if (_thing == kObjectBell) {
				_vm->_dialogs->displayText("Ding, dong, ding, dong, ding, dong, ding, dong...");
				if ((_vm->_avalot->_bellsAreRinging) & (_vm->_avalot->setFlag('B')))
					// \? are used to avoid that ??! is parsed as a trigraph
					_vm->_dialogs->displayText("(Are you trying to join in, Avvy\?\?!)");
			} else
				_vm->_dialogs->displayText(kWhat);
		}
		break;
	case kVerbCodeHelp:
		// boot_help();
		warning("STUB: Parser::doThat() - case kVerbCodehelp");
		break;
	case kVerbCodeLarrypass:
		_vm->_dialogs->displayText("Wrong game!");
		break;
	case kVerbCodePhaon:
		_vm->_dialogs->displayText("Hello, Phaon!");
		break;
	case kVerbCodeBoss:
		// bosskey();
		warning("STUB: Parser::doThat() - case kVerbCodeboss");
		break;
	case kVerbCodePee:
		if (_vm->_avalot->setFlag('P')) {
			_vm->_dialogs->displayText("Hmm, I don't think anyone will notice...");
			_vm->_timer->addTimer(4, Timer::kProcUrinate, Timer::kReasonGoToToilet);
		} else {
			Common::String tmpStr = Common::String::format("It would be %cVERY%c unwise to do that here, Avvy!", Dialogs::kControlItalic, Dialogs::kControlRoman);
			_vm->_dialogs->displayText(tmpStr);
		}
		break;
	case kVerbCodeCheat: {
		Common::String tmpStr = Common::String::format("%cCheat mode now enabled.", Dialogs::kControlItalic);
		_vm->_dialogs->displayText(tmpStr);
		_vm->_avalot->_cheat = true;
		}
		break;
	case kVerbCodeMagic:
		if (_vm->_avalot->_avariciusTalk > 0)
			_vm->_dialogs->displayScrollChain('q', 19);
		else {
			if ((_vm->_avalot->_room == kRoomSpludwicks) & (_vm->_animation->inField(1))) { // Avaricius appears!
				_vm->_dialogs->displayScrollChain('q', 17);
				if (_vm->_avalot->getRoom(kPeopleSpludwick) == kRoomSpludwicks)
					_vm->_dialogs->displayScrollChain('q', 18);
				else {
					Avalanche::AnimationType *spr = &_vm->_animation->_sprites[1];
					spr->init(1, false, _vm->_animation); // Avaricius
					_vm->_animation->appearPed(1, 3);
					spr->walkTo(4);
					spr->_callEachStepFl = true;
					spr->_eachStepProc = Animation::kProcBackAndForth;
					_vm->_avalot->_avariciusTalk = 14;
					_vm->_timer->addTimer(177, Timer::kProcAvariciusTalks, Timer::kReasonAvariciusTalks);
				}
			} else
				_vm->_dialogs->displayText("Nothing appears to happen...");
		}
		break;
	case kVerbCodeSmartAlec:
		_vm->_dialogs->displayText("Listen, smart alec, that was just rhetoric.");
		break;
	case kVerbCodeExpletive:
		switch (_sworeNum) {
		case 0: {
			Common::String tmpStr = Common::String::format("Avvy! Do you mind? There might be kids playing!%c%c" \
				"(I shouldn't say it again, if I were you!)", Dialogs::kControlNewLine, Dialogs::kControlNewLine);
			_vm->_dialogs->displayText(tmpStr);
			}
			break;
		case 1: {
			Common::String tmpStr = Common::String::format("You hear a distant rumble of thunder. Must you always" \
				"do things I tell you not to?%c%cDon't do it again!", Dialogs::kControlNewLine, Dialogs::kControlNewLine);
			_vm->_dialogs->displayText(tmpStr);
			}
			break;
		default: {
			_vm->_pingo->zonk();
			Common::String tmpStr = Common::String::format("A crack of lightning shoots from the sky, and fries you.%c%c(`Such is the anger of the gods, Avvy!\")", Dialogs::kControlNewLine, Dialogs::kControlNewLine);
			_vm->_dialogs->displayText(tmpStr);
			_vm->_avalot->gameOver();
			}
		}
		_sworeNum++;
		break;
	case kVerbCodeListen:
		if ((_vm->_avalot->_bellsAreRinging) & (_vm->_avalot->setFlag('B')))
			_vm->_dialogs->displayText("All other noise is drowned out by the ringing of the bells.");
		else if (_vm->_avalot->_listen.empty())
			_vm->_dialogs->displayText("You can't hear anything much at the moment, Avvy.");
		else
			_vm->_dialogs->displayText(_vm->_avalot->_listen);
		break;
	case kVerbCodeBuy: // What are they trying to buy?
		switch (_vm->_avalot->_room) {
		case kRoomArgentPub:
			if (_vm->_animation->inField(5)) { // We're in a pub, and near the bar.
				switch (_thing) {
				case 51:
				case 53:
				case 54:
				case 58: // Beer, whisky, cider or mead.
					if (_vm->_avalot->_malagauche == 177) { // Already getting us one.
						_vm->_dialogs->displayScrollChain('D', 15);
						return;
					}

					if (_vm->_avalot->_teetotal)  {
						_vm->_dialogs->displayScrollChain('D', 6);
						return;
					}

					if (_alcoholLevel == 0)
						_vm->_avalot->incScore(3);

					_vm->_background->draw(-1, -1, 11);
					_vm->_dialogs->displayText(booze[_thing - 51] + ", please." + Dialogs::kControlRegister + '1' + Dialogs::kControlSpeechBubble);
					_vm->_avalot->_drinking = _thing;

					_vm->_background->draw(-1, -1, 9);
					_vm->_avalot->_malagauche = 177;
					_vm->_timer->addTimer(27, Timer::kProcBuyDrinks, Timer::kReasonDrinks);
					break;
				case 52:
					examine();
					break; // We have a right one here - buy Pepsi??!
				case kObjectWine:
					if (_vm->_avalot->_objects[kObjectWine - 1])  // We've already got the wine!
						_vm->_dialogs->displayScrollChain('D', 2); // 1 bottle's shufishent!
					else {
						if (_vm->_avalot->_malagauche == 177) { // Already getting us one.
							_vm->_dialogs->displayScrollChain('D', 15);
							return;
						}

						if (_vm->_avalot->_carryNum >= kCarryLimit) {
							_vm->_dialogs->displayText("Your hands are full.");
							return;
						}

						_vm->_background->draw(-1, -1, 11);
						Common::String tmpStr = Common::String::format("Wine, please.%c1%c", Dialogs::kControlRegister, Dialogs::kControlSpeechBubble);
						_vm->_dialogs->displayText(tmpStr);
						if (_alcoholLevel == 0)
							_vm->_avalot->incScore(3);
						_vm->_background->draw(-1, -1, 9);
						_vm->_avalot->_malagauche = 177;

						_vm->_timer->addTimer(27, Timer::kProcBuyWine, Timer::kReasonDrinks);
					}
					break;
				}
			} else
				_vm->_dialogs->displayScrollChain('D', 5); // Go to the bar!
			break;

		case kRoomOutsideDucks:
			if (_vm->_animation->inField(5)) {
				if (_thing == kObjectOnion) {
					if (_vm->_avalot->_objects[kObjectOnion - 1])
						_vm->_dialogs->displayScrollChain('D', 10); // Not planning to juggle with the things!
					else if (_vm->_avalot->_carryNum >= kCarryLimit)
						_vm->_dialogs->displayText("Before you ask, you remember that your hands are full.");
					else {
						if (_boughtOnion)
							_vm->_dialogs->displayScrollChain('D', 11);
						else {
							_vm->_dialogs->displayScrollChain('D', 9);
							_vm->_avalot->incScore(3);
						}
						_vm->_avalot->decreaseMoney(3); // It costs thruppence.
						_vm->_avalot->_objects[kObjectOnion - 1] = true;
						_vm->_avalot->refreshObjectList();
						_boughtOnion = true;
						_vm->_avalot->_rottenOnion = false; // It's OK when it leaves the stall!
						_vm->_avalot->_onionInVinegar = false;
					}
				} else
					_vm->_dialogs->displayScrollChain('D', 0);
			} else
				_vm->_dialogs->displayScrollChain('D', 0);
			break;

		case kRoomNottsPub:
			_vm->_dialogs->displayScrollChain('n', 15); // Can't sell to southerners.
			break;
		default:
			_vm->_dialogs->displayScrollChain('D', 0); // Can't buy that.
		}
		break;
	case kVerbCodeAttack:
		if ((_vm->_avalot->_room == kRoomBrummieRoad) &&
			((_person == kPeopleCwytalot) || (_thing == kObjectCrossbow) || (_thing == kObjectBolt)) &&
			(_vm->_avalot->getRoom(kPeopleCwytalot) == _vm->_avalot->_room)) {
			switch (_vm->_avalot->_objects[kObjectBolt - 1] + _vm->_avalot->_objects[kObjectCrossbow - 1] * 2) {
				// 0 = neither, 1 = only bolt, 2 = only crossbow, 3 = both.
			case 0:
				_vm->_dialogs->displayScrollChain('Q', 10);
				_vm->_dialogs->displayText("(At the very least, don't use your bare hands!)");
				break;
			case 1:
				_vm->_dialogs->displayText("Attack _vm->_avalot->him with only a crossbow bolt? Are you planning on playing darts?!");
				break;
			case 2:
				_vm->_dialogs->displayText("Come on, Avvy! You're not going to get very far with only a crossbow!");
				break;
			case 3:
				_vm->_dialogs->displayScrollChain('Q', 11);
				_vm->_avalot->_cwytalotGone = true;
				_vm->_avalot->_objects[kObjectBolt - 1] = false;
				_vm->_avalot->_objects[kObjectCrossbow - 1] = false;
				_vm->_avalot->refreshObjectList();
				_vm->_avalot->_magics[11]._operation = Avalot::kMagicNothing;
				_vm->_avalot->incScore(7);
				_vm->_animation->_sprites[1].walkTo(1);
				_vm->_animation->_sprites[1]._vanishIfStill = true;
				_vm->_animation->_sprites[1]._callEachStepFl = false;
				_vm->_avalot->setRoom(kPeopleCwytalot, kRoomDummy);
				break;
			default:
				_vm->_dialogs->displayScrollChain('Q', 10); // Please try not to be so violent!
			}
		} else
			_vm->_dialogs->displayScrollChain('Q', 10);
		break;
	case kVerbCodePasswd:
		if (_vm->_avalot->_room != kRoomBridge)
			_vm->_dialogs->displayScrollChain('Q', 12);
		else {
			bool ok = true;
			for (uint i = 0; i < _thats.size(); i++) {
				Common::String temp = _realWords[i];
				temp.toUppercase();
				int pwdId = _vm->_avalot->_passwordNum + kFirstPassword;
				for (uint j = 0; j < _vocabulary[pwdId]._word.size(); j++) {
					if (_vocabulary[pwdId]._word[j] != temp[j])
						ok = false;
				}
			}

			if (ok) {
				if (_vm->_avalot->_drawbridgeOpen != 0)
					_vm->_dialogs->displayText("Contrary to your expectations, the drawbridge fails to close again.");
				else {
					_vm->_avalot->incScore(4);
					_vm->_dialogs->displayText("The drawbridge opens!");
					_vm->_timer->addTimer(7, Timer::kProcOpenDrawbridge, Timer::kReasonDrawbridgeFalls);
					_vm->_avalot->_drawbridgeOpen = 1;
				}
			} else
				_vm->_dialogs->displayScrollChain('Q', 12);
		}
		break;
	case kVerbCodeDir:
		//_vm->_enid->dir(_realWords[1]); TODO: Replace it with proper ScummVM-friendly function(s)!
		break;
	case kVerbCodeDie:
		_vm->_avalot->gameOver();
		break;
	case kVerbCodeScore: {
		Common::String tmpStr = Common::String::format("Your score is %d,%c%cout of a possible 128.%c%cThis gives you a rank of %s.%c%c%s", _vm->_avalot->_dnascore, Dialogs::kControlCenter, Dialogs::kControlNewLine, Dialogs::kControlNewLine, Dialogs::kControlNewLine, rank().c_str(), Dialogs::kControlNewLine, Dialogs::kControlNewLine, totalTime().c_str());
		_vm->_dialogs->displayText(tmpStr);
		}
		break;
	case kVerbCodePut:
		putProc();
		break;
	case kVerbCodeStand:
		standUp();
		break;
	case kVerbCodeKiss:
		if (_person == kPeoplePardon)
			_vm->_dialogs->displayText("Kiss whom?");
		else if (isPersonHere()) {
			switch (_person) {
			case kPeopleArkata:
				_vm->_dialogs->displayScrollChain('U', 12);
				break;
			case kPeopleGeida:
				_vm->_dialogs->displayScrollChain('U', 13);
				break;
			case kPeopleWisewoman:
				_vm->_dialogs->displayScrollChain('U', 14);
				break;
			default:
				_vm->_dialogs->displayScrollChain('U', 5); // You WHAT?
			}
		} else if ((kPeopleAvalot <= _person) && (_person < kPeopleArkata))
			_vm->_dialogs->displayText("Hey, what kind of a weirdo are you??");

		break;
	case kVerbCodeClimb:
		if (_vm->_avalot->_room == kRoomInsideCardiffCastle)
			cardiffClimbing();
		else // In the wrong room!
			_vm->_dialogs->displayText("Not with your head for heights, Avvy!");
		break;
	case kVerbCodeJump:
		_vm->_timer->addTimer(1, Timer::kProcJump, Timer::kReasonJumping);
		_vm->_avalot->_userMovesAvvy = false;
		break;
	case kVerbCodeHiscores:
		//	show_highs();
		warning("STUB: Parser::doThat() - case kVerbCodehighscores");
		break;
	case kVerbCodeWake:
		if (isPersonHere())
			switch (_person) {
			case kPeoplePardon:
			case kPeopleAvalot:
			case 0:
				if (!_vm->_avalot->_avvyIsAwake) {
					_vm->_avalot->_avvyIsAwake = true;
					_vm->_avalot->incScore(1);
					_vm->_avalot->_avvyInBed = true;
					_vm->_background->draw(-1, -1, 2); // Picture of Avvy, awake in bed.
					if (_vm->_avalot->_teetotal)
						_vm->_dialogs->displayScrollChain('d', 13);
				} else
					_vm->_dialogs->displayText("You're already awake, Avvy!");
				break;
			case kPeopleAyles:
				if (!_vm->_avalot->_aylesIsAwake)
					_vm->_dialogs->displayText("You can't seem to wake him by yourself.");
				break;
			case kPeopleJacques: {
				Common::String tmpStr = Common::String::format("Brother Jacques, Brother Jacques, are you asleep?%c1%c" \
					"Hmmm... that doesn't seem to do any good...", Dialogs::kControlRegister, Dialogs::kControlSpeechBubble);
				_vm->_dialogs->displayText(tmpStr);
				}
				break;
			default:
				_vm->_dialogs->displayText("It's difficult to awaken people who aren't asleep...!");
		}
		break;
	case kVerbCodeSit:
		if (_vm->_avalot->_room == kRoomNottsPub) {
			if (_vm->_avalot->_sittingInPub)
				_vm->_dialogs->displayText("You're already sitting!");
			else {
				_vm->_animation->_sprites[0].walkTo(3); // Move Avvy to the place, and sit him down.
				_vm->_timer->addTimer(1, Timer::kProcAvvySitDown, Timer::kReasonSittingDown);
			}
		} else { // Default doodah.
			_vm->_avalot->dusk();
			_vm->_avalot->hangAroundForAWhile();
			_vm->_avalot->dawn();
			Common::String tmpStr = Common::String::format("A few hours later...%cnothing much has happened...", Dialogs::kControlParagraph);
			_vm->_dialogs->displayText(tmpStr);
		}
		break;
	case kVerbCodeRestart:
		if (_vm->_dialogs->displayQuestion("Restart game and lose changes?"))  {
			_vm->_avalot->dusk();
			_vm->_avalot->newGame();
			_vm->_avalot->dawn();
		}
		break;
	case kVerbCodePardon:
		_vm->_dialogs->displayText("Hey, a verb would be helpful!");
		break;
	case kVerbCodeHello: {
		Common::String tmpStr = personSpeaks();
		tmpStr += Common::String::format("Hello.%c", Dialogs::kControlSpeechBubble);
		_vm->_dialogs->displayText(tmpStr);
		}
		break;
	case kVerbCodeThanks: {
		Common::String tmpStr = personSpeaks();
		tmpStr += Common::String::format("That's OK.%c", Dialogs::kControlSpeechBubble);
		_vm->_dialogs->displayText(tmpStr);
		}
		break;
	default:
		Common::String tmpStr = Common::String::format("%cParser bug!", Dialogs::kControlBell);
		_vm->_dialogs->displayText(tmpStr);
	}
}

void Parser::verbOpt(byte verb, Common::String &answer, char &ansKey) {
	switch (verb) {
	case kVerbCodeExam:
		answer = "Examine";
		ansKey = 'x';
		break; // The ubiquitous one.
	// kVerbCodegive isn't dealt with by this procedure, but by ddm__with.
	case kVerbCodeDrink:
		answer = "Drink";
		ansKey = 'D';
		break;
	case kVerbCodeWear:
		answer = "Wear";
		ansKey = 'W';
		break;
	case kVerbCodeRing:
		answer = "Ring";
		ansKey = 'R';
		break; // Only the bell!
	case kVerbCodePlay:
		answer = "Play";
		ansKey = 'P';
		break;
	case kVerbCodeEat:
		answer = "Eat";
		ansKey = 'E';
		break;
	default:
		answer = "? Unknown!"; // Bug!
		ansKey = '?';
	}
}

void Parser::resetVariables() {
	_wearing = 0;
	_sworeNum = 0;
	_alcoholLevel = 0;
	_playedNim = 0;
	_boughtOnion = false;
}

void Parser::synchronize(Common::Serializer &sz) {
	sz.syncAsByte(_wearing);
	sz.syncAsByte(_sworeNum);
	sz.syncAsByte(_alcoholLevel);
	sz.syncAsByte(_playedNim);
	sz.syncAsByte(_boughtOnion);
}

} // End of namespace Avalanche
