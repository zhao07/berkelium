// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include <Berkelium/API/BerkeliumFactory.hpp>
#include <Berkelium/API/HostExecutable.hpp>
#include <Berkelium/Impl/Impl.hpp>

#include <boost/filesystem.hpp>

namespace Berkelium {

namespace {

bool checkPath(const char* p, std::string& path) {
	boost::system::error_code ec;
	boost::filesystem::path p2(p);
	if(!boost::filesystem::exists(p2, ec)) return false;
	if(ec) return false;
	path = boost::filesystem::absolute(p2).string();
	return true;
}

} // namespace

HostExecutableRef BerkeliumFactory::forExecutable(const std::string& pathTo) {
	return HostExecutableRef(impl::newHostExecutable(pathTo));
}

HostExecutableRef BerkeliumFactory::forSystemInstalled() {
	std::string path;

#ifdef WIN32
	path = Berkelium::impl::getEnv("PROGRAMFILES(X86)", "C:\\Program Files") + "\\Google\\Chrome\\Application\\chrome.exe";
#elif defined(LINUX)
	if(checkPath("berkelium", path)) {
	} else if(checkPath("../berkelium", path)) {
	} else if(checkPath("../berkelium-host/berkelium", path)) {
	} else if(checkPath("../../berkelium-host/berkelium", path)) {
	} else if(checkPath("../../berkelium", path)) {
	} else {
		return HostExecutableRef();
	}
#else
#error "please add path to chrome here"
#endif

	std::cerr << "using berkelium host executable " << path << std::endl;

	return HostExecutableRef(impl::newHostExecutable(path));
}

} // namespace Berkelium
