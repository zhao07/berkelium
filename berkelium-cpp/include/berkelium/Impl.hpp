// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_IMPL_HPP_
#define BERKELIUM_IMPL_HPP_
#pragma once

#ifndef BERKELIUM_CPP_IMPL
# error "This file is intended for internal use only!"
#endif

#include "berkelium/Berkelium.hpp"

namespace Berkelium {

namespace impl {

HostExecutableRef newHostExecutable(const std::string&);
ProfileRef newProfile(const std::string& application, const std::string& profile, const bool temp);
std::string getEnv(const std::string&, const std::string& defaultValue);
#ifdef WIN32
std::string ws2s(const std::wstring&);
std::wstring s2ws(const std::string&);
#endif

} // namespace impl

} // namespace Berkelium

#endif // BERKELIUM_IMPL_HPP_
