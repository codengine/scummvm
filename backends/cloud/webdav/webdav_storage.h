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

#ifndef WEBDAV_STORAGE_H
#define WEBDAV_STORAGE_H

#include "backends/cloud/cloudmanager.h"

namespace Cloud {
namespace WebDAV {

class WebDAVStorage : Storage {
	Common::String _username;
	Common::String _password;

public:
	Common::String _url;
	static Storage *loadFromConfig(const Common::String &key_prefix);
	WebDAVStorage(const Common::String &username, const Common::String &password, const Common::String &url);
	void saveConfig(const Common::String &keyPrefix) override;
	Common::String name() const override;
	Networking::Request *listDirectory(const Common::String &path, ListDirectoryCallback callback, Networking::ErrorCallback errorCallback, bool recursive) override;
	Networking::Request *upload(const Common::String &path, Common::SeekableReadStream *contents, UploadCallback callback, Networking::ErrorCallback errorCallback) override;
	Networking::Request *streamFileById(const Common::String &id, Networking::NetworkReadStreamCallback callback, Networking::ErrorCallback errorCallback) override;
	Networking::Request *createDirectory(const Common::String &path, BoolCallback callback, Networking::ErrorCallback errorCallback) override;
	Networking::Request *info(StorageInfoCallback callback, Networking::ErrorCallback errorCallback) override;
	Common::String savesDirectoryPath() override;
	Common::String accessToken();
};

}
}
#endif // WEBDAV_STORAGE_H
