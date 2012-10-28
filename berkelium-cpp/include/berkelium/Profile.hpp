// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_PROFILE_HPP_
#define BERKELIUM_PROFILE_HPP_
#pragma once

// =========================================
// WARNING:
//   THIS FILE IS AUTOMATICALLY GENERATED!
//   !! ANY CHANGES WILL BE OVERWRITTEN !!
//
// See berkelium/berkelium-api/update.sh
// =========================================

#include "berkelium/Berkelium.hpp"

namespace Berkelium {

// Represents a berkelium profile on disk.
class Profile {
protected:
	Profile();

public:
	virtual ~Profile() = 0;

	// Returns true if this profile is already in use.
	virtual bool isInUse() = 0;

	// Returns true if this profile was found on disk.
	virtual bool isFound() = 0;

	// Returns true if this profile can be used without updating this profile to a newer version.
	virtual bool isSameVersion() = 0;

	// Returns true if this profile is from a newer berkelium host version.
	virtual bool isTooNew() = 0;

	// Returns the name of the application or “berkelium” if not specified.
	virtual const std::string& getApplicationName() = 0;

	// Returns the name of the profile or “default” if not specified.
	virtual const std::string& getProfileName() = 0;

	// Returns the full path to the used Profile.
	virtual const std::string& getProfilePath() = 0;
};

} // namespace Berkelium

#endif // BERKELIUM_PROFILE_HPP_
