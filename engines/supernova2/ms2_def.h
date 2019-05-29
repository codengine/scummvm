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

#ifndef SUPERNOVA2_MS2_DEF_H
#define SUPERNOVA2_MS2_DEF_H

#include "common/scummsys.h"

namespace Supernova2 {

const int kTextSpeed[] = {19, 14, 10, 7, 4};
const int kMsecPerTick = 55;

const int kMaxSection = 40;
const int kMaxDialog = 2;
const int kMaxObject = 30;
const int kMaxCarry = 30;

const int kSleepAutosaveSlot = 999;

const byte kShownFalse = 0;
const byte kShownTrue = 1;

enum MessagePosition {
	kMessageNormal,
	kMessageLeft,
	kMessageRight,
	kMessageCenter,
	kMessageTop
};

enum ObjectType {
	NULLTYPE    =      0,
	TAKE        =      1,
	OPENABLE    =      2,
	OPENED      =      4,
	CLOSED      =      8,
	EXIT        =     16,
	PRESS       =     32,
	COMBINABLE  =     64,
	CARRIED     =    128,
	UNNECESSARY =    256,
	WORN        =    512,
	TALK        =   1024,
	OCCUPIED    =   2048,
	CAUGHT      =   4096
};
typedef uint16 ObjectTypes;

enum Action {
	ACTION_WALK,
	ACTION_LOOK,
	ACTION_TAKE,
	ACTION_OPEN,
	ACTION_CLOSE,
	ACTION_PRESS,
	ACTION_PULL,
	ACTION_USE,
	ACTION_TALK,
	ACTION_GIVE
};

enum RoomId {
	INTRO,AIRPORT,TAXISTAND,STREET,GAMES,CABIN,KIOSK,
	KPALAST,CASHBOX,CITY1,CITY2,ELEVATOR,APARTMENT,SHIP,

	PYRAMID,PYRGANG,UPSTAIRS1,DOWNSTAIRS1,
	BOTTOM_RIGHT_DOOR,BOTTOM_LEFT_DOOR,UPSTAIRS2,DOWNSTAIRS2,
	UPPER_DOOR,PUZZLE_FRONT,PUZZLE_BEHIND,
	FORMULA1_F,FORMULA1_N,FORMULA2_F,FORMULA2_N,TOMATO_F,TOMATO_N,
	MONSTER_F,MONSTER1_N,MONSTER2_N,UPSTAIRS3,DOWNSTAIRS3,
	LGANG1,LGANG2,HOLE_ROOM,IN_HOLE,BODENTUER,BODENTUER_U,
	BST_DOOR,HALL,COFFIN_ROOM,MASK,

	MUSEUM,MUS_EING,MUS1,MUS2,MUS3,MUS4,MUS5,MUS6,MUS7,MUS8,
	MUS9,MUS10,MUS11,MUS_RUND,
	MUS12,MUS13,MUS14,MUS15,MUS16,MUS17,MUS18,MUS19,MUS20,MUS21,MUS22,
	NUMROOMS,NULLROOM
};

enum ObjectId {
	INVALIDOBJECT = -1,
	NULLOBJECT = 0,
	TAXI=1,WALLET,TRANSMITTER,KNIFE,POLE,BES_CABIN,MONEY,
	SLOT1,CHAIR,GANG,G_RIGHT,G_LEFT,PYRA_ENTRANCE,DOOR,BUTTON,
	PART0,PART1,PART2,PART3,PART4,PART5,PART6,PART7,
	PART8,PART9,PART10,PART11,PART12,PART13,PART14,PART15,
	TKNIFE,ROPE,NOTE,MOUTH,
	HOLE1,HOLE2,HOLE3,HOLE4,HOLE5,HOLE6,HOLE7,HOLE8,HOLE9,HOLE10,
	HOLE11,HOLE12,HOLE13,HOLE14,HOLE15,HOLE16,HOLE17,HOLE18,HOLE19,HOLE20,
	HOLE21,HOLE22,HOLE23,HOLE24,HOLE25,SHIELD,
	SLOT,HOLE,STONES,
	BST1,BST2,BST3,BST4,BST5,BST6,BST7,BST8,
	BST9,BST10,BST11,BST12,BST13,BST14,BST15,BST16,
	COFFIN,SUN,MONSTER,EYE,EYE1,EYE2,L_BALL,R_BALL,
	PRIZE,REAR_STREET,
	BMASK,BOTTLE,PLAYER,TOOTHBRUSH,BOOKS,LEXIcON,PLANT,SNAKE,
	CUP,JOYSTICK,BOTTLE1,BOTTLE2,BOTTLE3,BOTTLE4,BOX,FACES,
	SELLER,POSTER,AXACUSSER,KP_ENTRANCE,CHIP,CARD,
	DOODLE,DOODLE2,BELL,GROPE,DOOR_L,DOOR_R,ID_CARD,
	MAGNET,UNDER_BED,KEY,VALVE,WARDROBE,DISCMAN,
	SMALL_DOOR,BACK_MONEY,WALL,MAMMAL,IMITATION,SP_KEYCARD,ALARM_CRACKER,
	ENCRYPTED_DOOR,ALARM_ANLAGE,MUS_STREET,BIG_DOOR,INVESTMENT,
	HANDLE,COUNTER,DOOR_SWITCH,SUIT,MANAGEMENT,RMANAGEMENT,
	MUSCARD,SKOPF
};

enum StringId {
	kNoString = -1,
kString0, kString1, kString2, kString3, kString4,
kString5, kString6, kString7, kString8, kString9,
kString10, kString11, kString12, kString13, kString14,
kString15, kString16, kString17, kString18, kString19,
kString20, kString21, kString22, kString23, kString24,
kString25, kString26, kString27, kStringTextSpeed, kString29,
kString30, kString31, kString32, kString33, kString34,
kString35, kString36, kString37, kString38, kString39,
kString40, kString41, kString42, kString43, kString44,
kStringIntro1, kStringIntro2, kStringIntro3, kStringIntro4, kStringIntro5,
kString50, kString51, kString52, kString53, kString54,
kString55, kString56, kString57, kString58, kString59,
kString60, kString61, kString62, kString63, kString64,
kString65, kString66, kString67, kString68, kString69,
kString70, kString71, kString72, kString73, kString74,
kString75, kString76, kString77, kString78, kString79,
kString80, kString81, kString82, kString83, kString84,
kString85, kString86, kString87, kString88, kString89,
kString90, kString91, kString92, kString93, kString94,
kString95, kString96, kString97, kString98, kString99,
kString100, kString101, kString102, kString103, kString104,
kString105, kString106, kString107, kString108, kString109,
kString110, kString111, kString112, kString113, kString114,
kString115, kString116, kString117, kString118, kString119,
kString120, kString121, kString122, kString123, kString124,
kString125, kString126, kString127, kString128, kString129,
kString130, kString131, kString132, kString133, kString134,
kString135, kString136, kString137, kString138, kString139,
kString140, kString141, kString142, kString143, kString144,
kString145, kString146, kString147, kString148, kString149,
kString150, kString151, kString152, kString153, kString154,
kString155, kString156, kString157, kString158, kString159,
kString160, kString161, kString162, kString163, kString164,
kString165, kString166, kString167, kString168, kString169,
kString170, kString171, kString172, kString173, kString174,
kString175, kString176, kString177, kStringDefaultDescription, kString179,
kString180, kString181, kString182, kString183, kString184,
kString185, kString186, kString187, kString188, kString189,
kString190, kString191, kString192, kString193, kString194,
kString195, kString196, kString197, kString198, kString199,
kString200, kString201, kString202, kString203, kString204,
kString205, kString206, kString207, kString208, kString209,
kString210, kString211, kString212, kString213, kString214,
kString215, kString216, kString217, kString218, kString219,
kString220, kString221, kString222, kString223, kString224,
kString225, kString226, kString227, kString228, kString229,
kString230, kString231, kString232, kString233, kString234,
kString235, kString236, kString237, kString238, kString239,
kString240, kString241, kString242, kString243, kString244,
kString245, kString246, kString247, kString248, kString249,
kString250, kString251, kString252, kString253, kString254,
kString255, kString256, kString257, kString258, kString259,
kString260, kString261, kString262, kString263, kString264,
kString265, kString266, kString267, kString268, kString269,
kString270, kString271, kString272, kString273, kString274,
kString275, kString276, kString277, kString278, kString279,
kString280, kString281, kString282, kString283, kString284,
kString285, kString286, kString287, kString288, kString289,
kString290, kString291, kString292, kString293, kString294,
kString295, kString296, kString297, kString298, kString299,
kString300, kString301, kString302, kString303, kString304,
kString305, kString306, kString307, kString308, kString309,
kString310, kString311, kString312, kString313, kString314,
kString315, kString316, kString317, kString318, kString319,
kString320, kString321, kString322, kString323, kString324,
kString325, kString326, kString327, kString328, kString329,
kString330, kString331, kString332, kString333, kString334,
kString335, kString336, kString337, kString338, kString339,
kString340, kString341, kString342, kString343, kString344,
kString345, kString346, kString347, kString348, kString349,
kString350, kString351, kString352, kString353, kString354,
kString355, kString356, kString357, kString358, kString359,
kString360, kString361, kString362, kString363, kString364,
kString365, kString366, kString367, kString368, kString369,
kString370, kString371, kString372, kString373, kString374,
kString375, kString376, kString377, kString378, kString379,
kString380, kString381, kString382, kString383, kString384,
kString385, kString386, kString387, kString388, kString389,
kString390, kString391, kString392, kString393, kString394,
kString395, kString396, kString397, kString398, kString399,
kString400, kString401, kString402, kString403, kString404,
kString405, kString406, kString407, kString408, kString409,
kString410, kString411, kString412, kString413, kString414,
kString415, kString416, kString417, kString418, kString419,
kString420, kString421, kString422, kString423, kString424,
kString425, kString426, kString427, kString428, kString429,
kString430, kString431, kString432, kString433, kString434,
kString435, kString436, kString437, kString438, kString439,
kString440, kString441, kString442, kString443, kString444,
kString445, kString446, kString447, kString448, kString449,
kString450, kString451, kString452, kString453, kString454,
kString455, kString456, kString457, kString458, kString459,
kString460, kString461, kString462, kString463, kString464,
kString465, kString466, kString467, kString468, kString469,
kString470, kString471, kString472, kString473, kString474,
kString475, kString476, kString477, kString478, kString479,
kString480, kString481, kString482, kString483, kString484,
kString485, kString486, kString487, kString488, kString489,
kString490, kString491, kString492, kString493, kString494,
kString495, kString496, kString497, kString498, kString499,
kString500, kString501, kString502, kString503, kString504,
kString505, kString506, kString507, kString508, kString509,
kString510, kString511, kString512, kString513, kString514,
kString515, kString516, kString517, kString518, kString519,
kString520, kString521, kString522, kString523, kString524,
kString525, kString526, kString527, kString528, kString529,
kString530, kString531, kString532, kString533, kString534,
kString535, kString536, kString537, kString538, kString539,
kString540, kString541, kString542, kString543, kString544,
kString545, kString546, kString547, kString548, kString549,
kString550, kString551, kString552, kString553, kString554,
kString555, kString556, kString557, kString558, kString559,
kString560, kString561, kString562, kString563, kString564,
kString565, kString566, kString567, kString568, kString569,
kString570, kString571, kString572, kString573, kString574,
kString575, kString576, kString577, kString578, kString579,
kString580, kString581, kString582, kString583, kString584,
kString585, kString586, kString587, kString588, kString589,
kString590, kString591, kString592, kString593, kString594,
kString595, kString596, kString597, kString598, kString599,
kString600, kString601, kString602, kString603, kString604,
kString605, kString606, kString607, kString608, kString609,
kString610, kString611, kString612, kString613 
};

ObjectType operator|(ObjectType a, ObjectType b);
ObjectType operator&(ObjectType a, ObjectType b);
ObjectType operator^(ObjectType a, ObjectType b);
ObjectType &operator|=(ObjectType &a, ObjectType b);
ObjectType &operator&=(ObjectType &a, ObjectType b);
ObjectType &operator^=(ObjectType &a, ObjectType b);

struct Object {
	Object()
		: _name(kNoString)
		, _description(kStringDefaultDescription)
		, _id(INVALIDOBJECT)
		, _roomId(NULLROOM)
		, _type(NULLTYPE)
		, _click(0)
		, _click2(0)
		, _section(0)
		, _exitRoom(NULLROOM)
		, _direction(0)
	{}
	Object(byte roomId, StringId name, StringId description, ObjectId id, ObjectType type,
		   byte click, byte click2, byte section = 0, RoomId exitRoom = NULLROOM, byte direction = 0)
		: _name(name)
		, _description(description)
		, _id(id)
		, _roomId(roomId)
		, _type(type)
		, _click(click)
		, _click2(click2)
		, _section(section)
		, _exitRoom(exitRoom)
		, _direction(direction)
	{}

	void resetProperty(ObjectType type = NULLTYPE) {
		_type = type;
	}

	void setProperty(ObjectType type) {
		_type |= type;
	}

	void disableProperty(ObjectType type) {
		_type &= ~type;
	}

	bool hasProperty(ObjectType type) const {
		return _type & type;
	}

	static bool combine(Object &obj1, Object &obj2, ObjectId id1, ObjectId id2) {
		if (obj1.hasProperty(COMBINABLE))
			return (((obj1._id == id1) && (obj2._id == id2)) ||
					((obj1._id == id2) && (obj2._id == id1)));
		else
			return false;
	}

	byte _roomId;
	StringId _name;
	StringId _description;
	ObjectId _id;
	ObjectTypes _type;
	byte _click;
	byte _click2;
	byte _section;
	RoomId _exitRoom;
	byte _direction;
};

#define ticksToMsec(x) (x * kMsecPerTick)

}

#endif // SUPERNOVA2_MS2_DEF_H
