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

#include "cryo/cryolib.h"

namespace Cryo {

soundgroup_t *CLSoundGroup_New(int16 numSounds, int16 arg4, int16 sampleSize, float rate, int16 mode) {
	soundgroup_t *sg;
	int16 i;

	sg = (soundgroup_t *)CLMemory_Alloc(sizeof(*sg));
	if (numSounds < kCryoMaxClSounds)
		sg->_numSounds = numSounds;
	else {
		__libError = -3;
		__osError = 0;
		CLCheckError();
		sg->_numSounds = kCryoMaxClSounds;
	}
	for (i = 0; i < sg->_numSounds; i++) {
		sound_t *sound = CLSoundRaw_New(arg4, rate, sampleSize, mode);
		sg->_sound[i] = sound;
		sound->ff_1A = arg4;
	}
	sg->_soundIndex = 0;
	sg->_playIndex = 0;
	sg->ff_106 = 1;

	return sg;
}

void CLSoundGroup_Free(soundgroup_t *sg) {
	int16 i;
	for (i = 0; i < sg->_numSounds; i++)
		CLSoundRaw_Free(sg->_sound[i]);
	CLMemory_Free(sg);
}

void CLSoundGroup_Reverse16All(soundgroup_t *sg) {
	int16 i;
	for (i = 0; i < sg->_numSounds; i++)
		sg->_sound[i]->_reversed = true;
}

void *CLSoundGroup_GetNextBuffer(soundgroup_t *sg) {
	sound_t *sound = sg->_sound[sg->_soundIndex];
	if (sg->ff_106)
		while (sound->_locked) ;
	return sound->sndHandle + sound->_headerLen;
}

int16 CLSoundGroup_AssignDatas(soundgroup_t *sg, void *buffer, int length, int16 isSigned) {
	sound_t *sound = sg->_sound[sg->_soundIndex];
	if (sg->ff_106)
		while (sound->_locked) ;
	else if (sound->_locked)
		return 0;
	sound->_buffer = (char *)buffer;
	CLSound_SetLength(sound, length);
	sound->_length = length;
//	if(sound->reversed && sound->sampleSize == 16)
//		ReverseBlock16(buffer, length);
//	if(isSigned)
//		CLSound_Signed2NonSigned(buffer, length);
	if (sg->_soundIndex == sg->_numSounds - 1)
		sg->_soundIndex = 0;
	else
		sg->_soundIndex++;

	return 1;
}

int16 CLSoundGroup_SetDatas(soundgroup_t *sg, void *data, int length, int16 isSigned) {
	void *buffer;
	sound_t *sound = sg->_sound[sg->_soundIndex];
	if (length >= sound->ff_1A) {
		__libError = -10;
		__osError = 0;
		CLCheckError();
	}
	if (sg->ff_106)
		while (sound->_locked) ;
	else if (sound->_locked)
		return 0;
	buffer = sound->sndHandle + sound->_headerLen;
	sound->_buffer = (char *)buffer;
	memcpy(buffer, data, length);
	CLSound_SetLength(sound, length);
	sound->_length = length;
//	if(sound->reversed && sound->sampleSize == 16)
//		ReverseBlock16(buffer, length);
//	if(isSigned)
//		CLSound_Signed2NonSigned(buffer, length);
	if (sg->_soundIndex == sg->_numSounds - 1)
		sg->_soundIndex = 0;
	else
		sg->_soundIndex++;

	return 1;
}

void CLSoundGroup_PlayNextSample(soundgroup_t *sg, soundchannel_t *ch) {
	CLSoundChannel_Play(ch, sg->_sound[sg->_playIndex]);
	if (sg->_playIndex == sg->_numSounds - 1)
		sg->_playIndex = 0;
	else
		sg->_playIndex++;

}

} // End of namespace Cryo
