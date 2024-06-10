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

#ifndef WEBDAV_INFO_REQUEST_H
#define WEBDAV_INFO_REQUEST_H

#include "backends/cloud/storage.h"
#include "backends/networking/curl/request.h"

namespace Cloud {
namespace WebDAV {

class WebDAVStorage;

class WebDAVInfoRequest: public Networking::Request {
	WebDAVStorage *_storage;
	Storage::StorageInfoCallback _infoCallback;
	Request *_workingRequest;
	bool _ignoreCallback;

	void start();
	void responseCallback(const Networking::Response<void *> & response);
	void errorCallback(const Networking::ErrorResponse &error);
	void finishInfo(const StorageInfo &info);
public:
	WebDAVInfoRequest(WebDAVStorage *storage, Storage::StorageInfoCallback cb, Networking::ErrorCallback ecb);
	~WebDAVInfoRequest() override;

	void handle() override;
	void restart() override;
};
}
}
#endif // WEBDAV_INFO_REQUEST_H
