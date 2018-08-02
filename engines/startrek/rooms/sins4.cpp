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

#include "startrek/room.h"

#define OBJECT_NORTH_DOOR 8

#define HOTSPOT_NORTH_DOOR 0x20
#define HOTSPOT_PANEL 0x21
#define HOTSPOT_BEAM 0x22
#define HOTSPOT_LIGHT 0x23
#define HOTSPOT_WEST_DOOR 0x24
#define HOTSPOT_EAST_DOOR 0x25

namespace StarTrek {

extern const RoomAction sins4ActionList[] = {
	{ {ACTION_TICK, 1, 0, 0}, &Room::sins4Tick1 },

	{ {ACTION_USE, OBJECT_ISTRICOR, HOTSPOT_PANEL,      0}, &Room::sins4UseSTricorderOnPanel },
	{ {ACTION_USE, OBJECT_SPOCK,    HOTSPOT_PANEL,      0}, &Room::sins4UseSpockOnPanel },
	{ {ACTION_USE, OBJECT_IPHASERK, HOTSPOT_NORTH_DOOR, 0}, &Room::sins4UsePhaserOnNorthDoor },
	{ {ACTION_USE, OBJECT_IPHASERS, HOTSPOT_NORTH_DOOR, 0}, &Room::sins4UsePhaserOnNorthDoor },
	{ {ACTION_USE, OBJECT_IPHASERK, HOTSPOT_PANEL,      0}, &Room::sins4UsePhaserOnPanel },
	{ {ACTION_USE, OBJECT_IPHASERS, HOTSPOT_PANEL,      0}, &Room::sins4UsePhaserOnPanel },

	{ {ACTION_USE, OBJECT_IIDCARD,  HOTSPOT_PANEL,      0}, &Room::sins4UseIDCardOnPanel },
	{ {ACTION_DONE_WALK, 2,                          0, 0}, &Room::sins4KirkReachedPanel },
	{ {ACTION_DONE_ANIM, 5,                          0, 0}, &Room::sins4KirkPutCardInPanel },
	{ {ACTION_USE, OBJECT_IS8ROCKS, HOTSPOT_PANEL,      0}, &Room::sins4UseRockOnPanel },
	{ {ACTION_DONE_WALK, 3,                          0, 0}, &Room::sins4KirkReachedPanelWithRock },
	{ {ACTION_DONE_ANIM, 4,                          0, 0}, &Room::sins4KirkUsedRockOnPanel },

	{ {ACTION_LOOK, HOTSPOT_WEST_DOOR,  0, 0}, &Room::sins4LookAtWestDoor },
	{ {ACTION_LOOK, HOTSPOT_EAST_DOOR,  0, 0}, &Room::sins4LookAtEastDoor },
	{ {ACTION_LOOK, 0xff,               0, 0}, &Room::sins4LookAnywhere },
	{ {ACTION_LOOK, HOTSPOT_PANEL,      0, 0}, &Room::sins4LookAtPanel },
	{ {ACTION_TICK, 40,                 0, 0}, &Room::sins4Tick40 },
	{ {ACTION_LOOK, OBJECT_KIRK,        0, 0}, &Room::sins4LookAtKirk },
	{ {ACTION_LOOK, OBJECT_SPOCK,       0, 0}, &Room::sins4LookAtSpock },
	{ {ACTION_LOOK, OBJECT_MCCOY,       0, 0}, &Room::sins4LookAtMccoy },
	{ {ACTION_LOOK, OBJECT_REDSHIRT,    0, 0}, &Room::sins4LookAtRedshirt },
	{ {ACTION_LOOK, HOTSPOT_LIGHT,      0, 0}, &Room::sins4LookAtLight },
	{ {ACTION_LOOK, HOTSPOT_BEAM,       0, 0}, &Room::sins4LookAtBeam },
	{ {ACTION_LOOK, OBJECT_NORTH_DOOR,  0, 0}, &Room::sins4LookAtOpenNorthDoor },
	{ {ACTION_LOOK, HOTSPOT_NORTH_DOOR, 0, 0}, &Room::sins4LookAtClosedNorthDoor },
	{ {ACTION_TALK, OBJECT_KIRK,        0, 0}, &Room::sins4TalkToKirk },
	{ {ACTION_TALK, OBJECT_SPOCK,       0, 0}, &Room::sins4TalkToSpock },
	{ {ACTION_TALK, OBJECT_MCCOY,       0, 0}, &Room::sins4TalkToMccoy },
	{ {ACTION_TALK, OBJECT_REDSHIRT,    0, 0}, &Room::sins4TalkToRedshirt },

	{ {ACTION_USE, OBJECT_ISTRICOR, HOTSPOT_NORTH_DOOR, 0}, &Room::sins4UseSTricorderOnNorthDoor },
	{ {ACTION_USE, OBJECT_ISTRICOR, 0xff,               0}, &Room::sins4UseSTricorderAnywhere },
	{ {ACTION_USE, OBJECT_ICOMM,    0xff,               0}, &Room::sins4UseCommunicator },
	{ {ACTION_USE, OBJECT_MCCOY,    HOTSPOT_NORTH_DOOR, 0}, &Room::sins4UseMccoyOnNorthDoor },
	{ {ACTION_USE, OBJECT_REDSHIRT, HOTSPOT_NORTH_DOOR, 0}, &Room::sins4UseRedshirtOnNorthDoor },
	{ {ACTION_USE, OBJECT_SPOCK,    HOTSPOT_NORTH_DOOR, 0}, &Room::sins4UseSpockOnNorthDoor },
	{ {ACTION_USE, OBJECT_MCCOY,    HOTSPOT_PANEL,      0}, &Room::sins4UseMccoyOnPanel },
	{ {ACTION_USE, OBJECT_REDSHIRT, HOTSPOT_PANEL,      0}, &Room::sins4UseRedshirtOnPanel },

	{ {ACTION_WALK, HOTSPOT_NORTH_DOOR, 0, 0}, &Room::sins4WalkToNorthDoor },
	{ {ACTION_WALK, OBJECT_NORTH_DOOR,  0, 0}, &Room::sins4WalkToNorthDoor },
	{ {ACTION_WALK, HOTSPOT_WEST_DOOR, 0, 0}, &Room::sins4WalkToWestDoor },
	{ {ACTION_WALK, HOTSPOT_EAST_DOOR, 0, 0}, &Room::sins4WalkToEastDoor },

	{ {ACTION_USE, OBJECT_IMEDKIT,  OBJECT_KIRK,     0}, &Room::sins4UseMedkitOnCrewman },
	{ {ACTION_USE, OBJECT_IMEDKIT,  OBJECT_SPOCK,    0}, &Room::sins4UseMedkitOnCrewman },
	{ {ACTION_USE, OBJECT_IMEDKIT,  OBJECT_MCCOY,    0}, &Room::sins4UseMedkitOnCrewman },
	{ {ACTION_USE, OBJECT_IMEDKIT,  OBJECT_REDSHIRT, 0}, &Room::sins4UseMedkitOnCrewman },
	{ {ACTION_USE, OBJECT_IMTRICOR, OBJECT_KIRK,     0}, &Room::sins4UseMTricorderOnCrewman },
	{ {ACTION_USE, OBJECT_IMTRICOR, OBJECT_SPOCK,    0}, &Room::sins4UseMTricorderOnCrewman },
	{ {ACTION_USE, OBJECT_IMTRICOR, OBJECT_MCCOY,    0}, &Room::sins4UseMTricorderOnCrewman },
	{ {ACTION_USE, OBJECT_IMTRICOR, OBJECT_REDSHIRT, 0}, &Room::sins4UseMTricorderOnCrewman },
};

extern const int sins4NumActions = ARRAYSIZE(sins4ActionList);


void Room::sins4Tick1() {
	playVoc("SIN4LOOP");

	if (!_awayMission->sins.enteredRoom4FirstTime)
		_awayMission->disableInput = 2;

	if (_awayMission->sins.unlockedIDCardDoor)
		loadActorAnim2(OBJECT_NORTH_DOOR, "s4dro", 0, 0);

	playMidiMusicTracks(MIDITRACK_27, -3);
}

void Room::sins4UseSTricorderOnPanel() {
	spockScan(DIR_N, TX_SIN4_020);
	_awayMission->sins.scannedKeycardLock = true;
	_awayMission->sins.gatheredClues |= 4;

	if (_awayMission->sins.gatheredClues == 7) {
		showText(TX_SPEAKER_SPOCK, TX_SIN4_010);
		_awayMission->sins.gatheredClues |= 8;
	}
}

void Room::sins4UseSpockOnPanel() {
	// NOTE: two implementations of this function, one unused
	if (true)
		showText(TX_SPEAKER_SPOCK, TX_SIN4_018);
	else {
		showText(TX_SPEAKER_SPOCK, TX_SIN4_021);

		if (_awayMission->sins.gatheredClues == 7) {
			showText(TX_SPEAKER_SPOCK, TX_SIN4_010);
			_awayMission->sins.gatheredClues |= 8;
		}
	}
}

void Room::sins4UsePhaserOnNorthDoor() {
	showText(TX_SPEAKER_SPOCK, TX_SIN4_009);
}

void Room::sins4UsePhaserOnPanel() {
	showText(TX_SPEAKER_SPOCK, TX_SIN4_008);
}

void Room::sins4UseIDCardOnPanel() {
	if (_awayMission->sins.unlockedIDCardDoor)
		showText(TX_SIN4N006);
	else
		walkCrewmanC(OBJECT_KIRK, 0xb8, 0x86, &Room::sins4KirkReachedPanel);
}

void Room::sins4KirkReachedPanel() {
	_awayMission->sins.unlockedIDCardDoor = true;
	loseItem(OBJECT_IIDCARD);
	loadActorAnimC(OBJECT_KIRK, "kusemn", -1, -1, &Room::sins4KirkPutCardInPanel);

	_awayMission->disableInput = true; // ENHANCEMENT: disable input
}

void Room::sins4KirkPutCardInPanel() {
	loadActorAnim2(OBJECT_NORTH_DOOR, "s4door", 0, 0, 1); // Callback "1" doesn't exist
	playVoc("MUR4E1");
	_awayMission->disableInput = false;
}

void Room::sins4UseRockOnPanel() {
	walkCrewmanC(OBJECT_KIRK, 0xb8, 0x86, &Room::sins4KirkReachedPanelWithRock);
}

void Room::sins4KirkReachedPanelWithRock() {
	loadActorAnimC(OBJECT_KIRK, "kusemn", -1, -1, &Room::sins4KirkUsedRockOnPanel);
}

void Room::sins4KirkUsedRockOnPanel() {
	showText(TX_SIN4N012);
	showText(TX_SPEAKER_SPOCK, TX_SIN4_022);

	if (_awayMission->sins.gatheredClues == 7) {
		showText(TX_SPEAKER_SPOCK, TX_SIN4_010);
		_awayMission->sins.gatheredClues |= 8;
	}
}

void Room::sins4LookAtWestDoor() {
	showText(TX_SIN4N009);
}

void Room::sins4LookAtEastDoor() {
	showText(TX_SIN4N010);
}

void Room::sins4LookAnywhere() {
	showText(TX_SIN4N013);
}

void Room::sins4LookAtPanel() {
	showText(TX_SIN4N011);
}

void Room::sins4Tick40() {
	if (!_awayMission->sins.enteredRoom4FirstTime) {
		_awayMission->disableInput = false;
		showText(TX_SPEAKER_UHURA, TX_SIN4U088);
		showText(TX_SPEAKER_KIRK,  TX_SIN4_007);
		showText(TX_SPEAKER_UHURA, TX_SIN4U103);
		showText(TX_SPEAKER_SPOCK, TX_SIN4_025);
		showText(TX_SPEAKER_KIRK,  TX_SIN4_003);
		showText(TX_SPEAKER_UHURA, TX_SIN4U107);
		showText(TX_SPEAKER_UHURA, TX_SIN4U105);
		showText(TX_SPEAKER_KIRK,  TX_SIN4_005);
		_awayMission->sins.enteredRoom4FirstTime = true;
	}
}

void Room::sins4LookAtKirk() {
	showText(TX_SIN4N002);
}

void Room::sins4LookAtSpock() {
	showText(TX_SIN4N004);
}

void Room::sins4LookAtMccoy() {
	showText(TX_SIN4N003);
}

void Room::sins4LookAtRedshirt() {
	showText(TX_SIN4N001);
}

void Room::sins4LookAtLight() {
	showText(TX_SIN4N000);
}

void Room::sins4LookAtBeam() {
	showText(TX_SIN4N005);
}

void Room::sins4LookAtOpenNorthDoor() {
	showText(TX_SIN4N008);
}

void Room::sins4LookAtClosedNorthDoor() {
	showText(TX_SIN4N007);
}

void Room::sins4TalkToKirk() {
	showText(TX_SPEAKER_KIRK,  TX_SIN4_001);
	showText(TX_SPEAKER_SPOCK, TX_SIN4_028);
	showText(TX_SPEAKER_KIRK,  TX_SIN4_004);
}

void Room::sins4TalkToSpock() {
	showText(TX_SPEAKER_SPOCK, TX_SIN4_019);
}

void Room::sins4TalkToMccoy() {
	showText(TX_SPEAKER_MCCOY, TX_SIN4_015);
	showText(TX_SPEAKER_SPOCK, TX_SIN4_024);
	showText(TX_SPEAKER_MCCOY, TX_SIN4_017);
}

void Room::sins4TalkToRedshirt() {
	showText(TX_SPEAKER_MOSHER, TX_SIN4_031);
}

void Room::sins4UseSTricorderOnNorthDoor() {
	spockScan(DIR_N, TX_SIN4_027);
	showText(TX_SPEAKER_MOSHER, TX_SIN4_032);
	showText(TX_SPEAKER_SPOCK,  TX_SIN4_026);
}

void Room::sins4UseSTricorderAnywhere() {
	spockScan(DIR_S, TX_SIN4_011);

	if (!_awayMission->sins.gotPointsForScanningRoom4) {
		_awayMission->sins.missionScore += 1;
		_awayMission->sins.gotPointsForScanningRoom4 = true;
	}
}

void Room::sins4UseCommunicator() {
	if (!_awayMission->sins.enteredRoom3FirstTime) {
		showText(TX_SPEAKER_UHURA, TX_SIN4U100);
		showText(TX_SPEAKER_KIRK,  TX_SIN4_006);
		showText(TX_SPEAKER_UHURA, TX_SIN4U83B);
		showText(TX_SPEAKER_KIRK,  TX_SIN4_002);
	} else
		showText(TX_SPEAKER_UHURA, TX_SIN4U073);
}

void Room::sins4UseMccoyOnNorthDoor() {
	showText(TX_SPEAKER_MCCOY, TX_SIN4_016);
}

void Room::sins4UseRedshirtOnNorthDoor() {
	showText(TX_SPEAKER_MOSHER, TX_SIN4_029);
}

void Room::sins4UseSpockOnNorthDoor() {
	showText(TX_SPEAKER_SPOCK, TX_SIN4_023);
}

void Room::sins4UseMccoyOnPanel() {
	showText(TX_SPEAKER_MCCOY, TX_SIN4_013);
}

void Room::sins4UseRedshirtOnPanel() {
	showText(TX_SPEAKER_MOSHER, TX_SIN4_030);
}

void Room::sins4WalkToNorthDoor() {
	if (_awayMission->sins.unlockedIDCardDoor)
		walkCrewman(OBJECT_KIRK, 0x96, 0x7d);
}

void Room::sins4WalkToWestDoor() {
	walkCrewman(OBJECT_KIRK, 0x1b, 0x95);
}

void Room::sins4WalkToEastDoor() {
	walkCrewman(OBJECT_KIRK, 0x13c, 0x9b);
}

void Room::sins4UseMedkitOnCrewman() {
	showText(TX_SPEAKER_MCCOY, TX_SIN4_014);
}

void Room::sins4UseMTricorderOnCrewman() {
	mccoyScan(DIR_S, TX_SIN4_012);
}

}
