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

#include "backends/cloud/webdav/webdav_storage.h"
#include "common/config-manager.h"

namespace Cloud {
namespace WebDAV {

Storage *WebDAVStorage::loadFromConfig(const Common::String &key_prefix) {
	if (!ConfMan.hasKey(key_prefix + "username", ConfMan.kCloudDomain)) {
		warning("WebDAVStorage: no username found");
		return nullptr;
	}

	if (!ConfMan.hasKey(key_prefix + "password", ConfMan.kCloudDomain)) {
		warning("WebDAVStorage: no password found");
		return nullptr;
	}

	if (!ConfMan.hasKey(key_prefix + "url", ConfMan.kCloudDomain)) {
		warning("WebDAVStorage: no url found");
		return nullptr;
	}

	const auto username = ConfMan.get(key_prefix + "username", ConfMan.kCloudDomain);
	const auto password = ConfMan.get(key_prefix + "password", ConfMan.kCloudDomain);
	const auto url = ConfMan.get(key_prefix + "url", ConfMan.kCloudDomain);
	return new WebDAVStorage(username, password, url);
}

WebDAVStorage::WebDAVStorage(const Common::String &username, const Common::String &password, const Common::String &url):
	_username(username), _password(password), _url(url) {
}

void WebDAVStorage::saveConfig(const Common::String &keyPrefix) {
}

Common::String WebDAVStorage::name() const {
	return "WebDAV";
}

Networking::Request *WebDAVStorage::listDirectory(const Common::String &path, ListDirectoryCallback callback, Networking::ErrorCallback errorCallback, bool recursive) {
	return nullptr;
}

Networking::Request *WebDAVStorage::upload(const Common::String &path, Common::SeekableReadStream *contents, UploadCallback callback, Networking::ErrorCallback errorCallback) {
	return nullptr;
}

Networking::Request *WebDAVStorage::streamFileById(const Common::String &id, Networking::NetworkReadStreamCallback callback, Networking::ErrorCallback errorCallback) {
	return nullptr;
}

Networking::Request *WebDAVStorage::createDirectory(const Common::String &path, BoolCallback callback, Networking::ErrorCallback errorCallback) {
	return nullptr;
}

Networking::Request *WebDAVStorage::info(StorageInfoCallback callback, Networking::ErrorCallback errorCallback) {
	return nullptr;
}

Common::String WebDAVStorage::savesDirectoryPath() {
	return "/saves/";
}

Common::String WebDAVStorage::accessToken() {
	return nullptr;
}
}
}
