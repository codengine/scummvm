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

// MIDI music class

#include "made/music.h"
#include "made/redreader.h"
#include "made/resource.h"

#include "audio/adlib_ms.h"
#include "audio/midiparser.h"
#include "audio/miles.h"

#include "common/config-manager.h"
#include "common/file.h"
#include "common/stream.h"

namespace Made {

MusicPlayer::MusicPlayer(bool milesAudio) : _parser(0) {
	MidiDriver::DeviceHandle dev = MidiDriver::detectDevice(MDT_MIDI | MDT_ADLIB | MDT_PREFER_MT32);
	_driverType = MidiDriver::getMusicType(dev);
	if (_driverType == MT_GM && ConfMan.getBool("native_mt32"))
		_driverType = MT_MT32;

	Common::SeekableReadStream *adLibInstrumentStream = nullptr;
	switch (_driverType) {
	case MT_ADLIB:
		if (milesAudio) {
			if (Common::File::exists("rtzcd.red")) {
				// Installing Return to Zork produces both a SAMPLE.AD and
				// a SAMPLE.OPL file, but they are identical. The resource
				// file appears to only contain SAMPLE.AD.
				adLibInstrumentStream = RedReader::loadFromRed("rtzcd.red", "SAMPLE.AD");
			}
			_driver = Audio::MidiDriver_Miles_AdLib_create("SAMPLE.AD", "SAMPLE.OPL", adLibInstrumentStream);
			delete adLibInstrumentStream;
		} else {
			_driver = new MidiDriver_ADLIB_MADE(OPL::Config::kOpl2);
		}
		break;
	case MT_GM:
	case MT_MT32:
		if (milesAudio) {
			_driver = Audio::MidiDriver_Miles_MIDI_create(MT_MT32, "");
		} else {
			_driver = new MidiDriver_MT32GM(MT_MT32);
		}
		break;
	default:
		_driver = new MidiDriver_NULL_Multisource();
		break;
	}

	if (_driver) {
		_driver->property(MidiDriver::PROP_USER_VOLUME_SCALING, true);
		if (_driver->open() != 0)
			error("Failed to open MIDI driver.");

		_driver->setTimerCallback(this, &timerCallback);
	}

	syncSoundSettings();
}

MusicPlayer::~MusicPlayer() {
	if (_parser) {
		_parser->stopPlaying();
		delete _parser;
	}
	if (_driver) {
		_driver->setTimerCallback(0, 0);
		_driver->close();
		delete _driver;
	}
}

void MusicPlayer::playXMIDI(GenericResource *midiResource) {
	if (_parser) {
		_parser->unloadMusic();
	} else {
		_parser = MidiParser::createParser_XMIDI(0, 0, 0);

		_parser->setMidiDriver(_driver);
		_parser->setTimerRate(_driver->getBaseTempo());
		_parser->property(MidiParser::mpSendSustainOffOnNotesOff, 1);
	}

	// Load XMID resource data

	_parser->loadMusic(midiResource->getData(), midiResource->getSize());
}

void MusicPlayer::playSMF(GenericResource *midiResource) {
	if (_parser) {
		_parser->unloadMusic();
	} else {
		_parser = MidiParser::createParser_SMF(0);

		_parser->setMidiDriver(_driver);
		_parser->setTimerRate(_driver->getBaseTempo());
		_parser->property(MidiParser::mpCenterPitchWheelOnUnload, 1);
	}

	// Load MIDI resource data

	_parser->loadMusic(midiResource->getData(), midiResource->getSize());
}

void MusicPlayer::pause() {
	if (_parser)
		_parser->pausePlaying();
}

void MusicPlayer::resume() {
	if (_parser)
		_parser->resumePlaying();
}

void MusicPlayer::stop() {
	if (_parser)
		_parser->stopPlaying();
}

bool MusicPlayer::isPlaying() {
	return _parser ? _parser->isPlaying() : false;
}

void MusicPlayer::syncSoundSettings() {
	if (_driver)
		_driver->syncSoundSettings();
}

void MusicPlayer::onTimer() {
	if (_parser)
		_parser->onTimer();
}

void MusicPlayer::timerCallback(void *data) {
	((MusicPlayer *)data)->onTimer();
}

MidiDriver_ADLIB_MADE::MidiDriver_ADLIB_MADE(OPL::Config::OplType oplType) : MidiDriver_ADLIB_Multisource(oplType) {
	_modulationDepth = MODULATION_DEPTH_LOW;
	_vibratoDepth = VIBRATO_DEPTH_LOW;
	_defaultChannelVolume = 0x7F;
}

} // End of namespace Made
