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

#include "backends/cloud/webdav/webdav_info_request.h"
#include "backends/cloud/webdav/webdav_storage.h"
#include "backends/networking/curl/connectionmanager.h"

namespace Cloud {
namespace WebDAV {

WebDAVInfoRequest::WebDAVInfoRequest(WebDAVStorage *storage, Storage::StorageInfoCallback cb, Networking::ErrorCallback ecb):
	Request(nullptr, ecb), _storage(storage), _infoCallback(cb),
	_workingRequest(nullptr), _ignoreCallback(false) {
	start();
}

WebDAVInfoRequest::~WebDAVInfoRequest() {
	_ignoreCallback = true;
	if (_workingRequest)
		_workingRequest->finish();
	delete _infoCallback;
}

void WebDAVInfoRequest::handle() {
}

void WebDAVInfoRequest::restart() {
}

void WebDAVInfoRequest::start() {
	_ignoreCallback = true;
	if (_workingRequest)
		_workingRequest->finish();
	_ignoreCallback = false;

	const Networking::DataCallback callback = new Common::Callback<WebDAVInfoRequest, const Networking::DataResponse &>(this, &WebDAVInfoRequest::responseCallback);
	const Networking::ErrorCallback failureCallback = new Common::Callback<WebDAVInfoRequest, const Networking::ErrorResponse &>(this, &WebDAVInfoRequest::errorCallback);

	const auto request = new Networking::CurlRequest(callback, failureCallback, _storage->_url);
	request->addHeader("Authorization: Bearer " + _storage->accessToken());

	_workingRequest = ConnMan.addRequest(request);
}

void WebDAVInfoRequest::responseCallback(const Networking::Response<void *> &response) {
}

void WebDAVInfoRequest::errorCallback(const Networking::ErrorResponse &error) {
}

void WebDAVInfoRequest::finishInfo(const StorageInfo &info) {
}

}
}
