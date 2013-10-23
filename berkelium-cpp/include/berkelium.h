// Copyright (c) 2013 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_API_H_
#define BERKELIUM_API_H_
#pragma once

// =========================================
// WARNING:
//   THIS FILE IS AUTOMATICALLY GENERATED!
//   !! ANY CHANGES WILL BE OVERWRITTEN !!
//
// See berkelium/berkelium-api/update.sh
// =========================================

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	HostVersion,
	BerkeliumFactory,
	Runtime,
	HostExecutable,
	Profile,
	Logger,
	LogDelegate,
	HostDelegate,
	Instance,
	Window,
	WindowDelegate,
	Tab,
	TabDelegate,
	Update
} BK_Env_Enum;

const char* BK_Env_Enum_To_String_Or_Null(BK_Env_Enum type);
const char* BK_Env_Enum_To_String_Or_Err(BK_Env_Enum type);

#define BK_Env_Enum_MAX 14

typedef int32_t bk_int32;
typedef int32_t bk_bool;
typedef char* bk_string;
typedef void* BK_Rect;

typedef void* BK_HostVersion;
typedef void* BK_BerkeliumFactory;
typedef void* BK_Runtime;
typedef void* BK_HostExecutable;
typedef void* BK_Profile;
typedef void* BK_Logger;
typedef void* BK_Instance;
typedef void* BK_Window;
typedef void* BK_Tab;

typedef enum {
	Host,
	Lib
} BK_LogSource;

typedef enum {
	StdOut,
	StdErr,
	Debug,
	Info,
	Warn,
	Error
} BK_LogType;

typedef void* bk_bk_obj;
typedef void* bk_ext_obj;

typedef bk_bk_obj BK_Env_mapIn(BK_Env_Enum type, bk_ext_obj id, void* data);

typedef bk_ext_obj BK_Env_mapOut(BK_Env_Enum type, bk_bk_obj id, void* data);

typedef bk_ext_obj BK_Env_mapNew(BK_Env_Enum type, bk_bk_obj id, bk_ext_obj extId, void* data);

typedef void BK_Env_free(bk_ext_obj extId, void* data);

typedef void BK_Env_NPE(bk_string clazz, bk_string arg);

typedef struct {
	BK_Env_mapIn* mapIn;
	BK_Env_mapOut* mapOut;
	BK_Env_mapNew* mapNew;
	BK_Env_free* free;
	BK_Env_NPE* NPE;
	void* data;
} BK_Env;

typedef struct {
	bk_int32 size;
	BK_Window* entrys;
} BK_WindowList;

typedef struct {
	bk_int32 size;
	BK_Tab* entrys;
} BK_TabList;


// =========================================
// delegate LogDelegate
// =========================================

typedef struct _BK_LogDelegate* BK_LogDelegate;

typedef void BK_LogDelegate_log(BK_Env* env, BK_LogDelegate self, BK_Runtime runtime, BK_LogSource source, BK_LogType type, bk_string clazz, bk_string name, bk_string message);

struct _BK_LogDelegate {
	bk_ext_obj self;
	BK_LogDelegate_log* log;
};

// =========================================
// delegate HostDelegate
//
// Handler for events concerning the berkelium host process.
// =========================================

typedef struct _BK_HostDelegate* BK_HostDelegate;

typedef void BK_HostDelegate_onCrashed(BK_Env* env, BK_HostDelegate self, BK_Instance instance);
typedef void BK_HostDelegate_onClosed(BK_Env* env, BK_HostDelegate self, BK_Instance instance);
typedef void BK_HostDelegate_onPing(BK_Env* env, BK_HostDelegate self, BK_Instance instance);

struct _BK_HostDelegate {
	bk_ext_obj self;
	BK_HostDelegate_onCrashed* onCrashed;
	BK_HostDelegate_onClosed* onClosed;
	BK_HostDelegate_onPing* onPing;
};

// =========================================
// delegate WindowDelegate
// =========================================

typedef struct _BK_WindowDelegate* BK_WindowDelegate;


struct _BK_WindowDelegate {
	bk_ext_obj self;
};

// =========================================
// delegate TabDelegate
//
// Handler for events concerning tab content.
// =========================================

typedef struct _BK_TabDelegate* BK_TabDelegate;

typedef void BK_TabDelegate_onClosed(BK_Env* env, BK_TabDelegate self, BK_Tab tab);
typedef void BK_TabDelegate_onTitleChanged(BK_Env* env, BK_TabDelegate self, BK_Tab tab, bk_string title);
typedef void BK_TabDelegate_onPaint(BK_Env* env, BK_TabDelegate self, BK_Tab tab);
typedef void BK_TabDelegate_onPaintDone(BK_Env* env, BK_TabDelegate self, BK_Tab tab, BK_Rect rect);
typedef void BK_TabDelegate_onReady(BK_Env* env, BK_TabDelegate self, BK_Tab tab);

struct _BK_TabDelegate {
	bk_ext_obj self;
	BK_TabDelegate_onClosed* onClosed;
	BK_TabDelegate_onTitleChanged* onTitleChanged;
	BK_TabDelegate_onPaint* onPaint;
	BK_TabDelegate_onPaintDone* onPaintDone;
	BK_TabDelegate_onReady* onReady;
};

// =========================================
// delegate Update
// =========================================

typedef struct _BK_Update* BK_Update;

typedef void BK_Update_update(BK_Env* env, BK_Update self);

struct _BK_Update {
	bk_ext_obj self;
	BK_Update_update* update;
};

// =========================================
// interface HostVersion
// =========================================

// Returns the associated Runtime.
BK_Runtime BK_HostVersion_getRuntime(BK_Env* env, BK_HostVersion self);

// Returns the berkelium host version e.g. “22.0.1229.94”
bk_string BK_HostVersion_getVersionString(BK_Env* env, BK_HostVersion self);

// Returns the Major Version, e.g. “22”
bk_int32 BK_HostVersion_getMajor(BK_Env* env, BK_HostVersion self);

// Returns the Minor Version, always zero?
bk_int32 BK_HostVersion_getMinor(BK_Env* env, BK_HostVersion self);

// Returns the Build Version, e.g. “1229”
bk_int32 BK_HostVersion_getBuild(BK_Env* env, BK_HostVersion self);

// Returns the Patch Version, e.g. “94”
bk_int32 BK_HostVersion_getPatch(BK_Env* env, BK_HostVersion self);

// Returns true if the given Version is less or equal to the version of the executable represented by this executable object.
bk_bool BK_HostVersion_isMinVersion(BK_Env* env, BK_HostVersion self, bk_string version);
void BK_HostVersion_free(BK_Env*, BK_HostVersion self);

// =========================================
// class BerkeliumFactory
// =========================================

// Returns the default Berkelium Runtime Instance.
BK_Runtime BK_BerkeliumFactory_getDefaultRuntime(BK_Env* env);

// Creates an add additional Berkelium Runtime Instance with default LogDelegate.
BK_Runtime BK_BerkeliumFactory_createRuntime(BK_Env* env);

// Creates an add additional Berkelium Runtime Instance with given LogDelegate.
BK_Runtime BK_BerkeliumFactory_createRuntimeWithLog(BK_Env* env, BK_LogDelegate log);

// =========================================
// interface Runtime
// =========================================

// String with object count debug informations.
bk_string BK_Runtime_getDebugObjectStats(BK_Env* env, BK_Runtime self);

// Processes all Pending Events. Waits up to timeout ms for new events.
void BK_Runtime_update(BK_Env* env, BK_Runtime self, bk_int32 timeout);

// Calls given update method after given timeout (in ms).
void BK_Runtime_addUpdateEvent(BK_Env* env, BK_Runtime self, BK_Update update, bk_int32 timeout);

// Sets the Path to the HostExecutable Object used by forSystemInstalled.
void BK_Runtime_setDefaultExecutable(BK_Env* env, BK_Runtime self, bk_string pathTo);

// Creates an HostExecutable Object representing the given executable.
BK_HostExecutable BK_Runtime_forExecutable(BK_Env* env, BK_Runtime self, bk_string pathTo);

// Creates an HostExecutable, the exectuable is searched through system path or system configuration (e.g. registry on windows)
BK_HostExecutable BK_Runtime_forSystemInstalled(BK_Env* env, BK_Runtime self);

// Returns the profile for the given application name.
BK_Profile BK_Runtime_forProfile(BK_Env* env, BK_Runtime self, bk_string application);

// Returns a Profile object representing the Google Chrome profile.
BK_Profile BK_Runtime_getChromeProfile(BK_Env* env, BK_Runtime self);

// Returns a Profile object representing the Chromium profile.
BK_Profile BK_Runtime_getChromiumProfile(BK_Env* env, BK_Runtime self);

// Returns the profile located inside the given path.
BK_Profile BK_Runtime_forProfilePath(BK_Env* env, BK_Runtime self, bk_string path);

// Creates a temporary profile that gets automatically removed after use.
BK_Profile BK_Runtime_createTemporaryProfile(BK_Env* env, BK_Runtime self);

// Creates a HostVersion object representing the given version string.
BK_HostVersion BK_Runtime_forVersionS(BK_Env* env, BK_Runtime self, bk_string version);

// Creates a HostVersion object representing the given version number.
BK_HostVersion BK_Runtime_forVersion4I(BK_Env* env, BK_Runtime self, bk_int32 vMajor, bk_int32 vMinor, bk_int32 vBuild, bk_int32 vPatch);

// Launches a the given berkelium host process using the given profile.
BK_Instance BK_Runtime_open(BK_Env* env, BK_Runtime self, BK_HostExecutable executable, BK_Profile profile);
BK_Logger BK_Runtime_getLogger(BK_Env* env, BK_Runtime self, bk_string clazz, bk_string name);

// Add the given LogDelegate to this Instance.
void BK_Runtime_addLogDelegate(BK_Env* env, BK_Runtime self, BK_LogDelegate delegate);

// Remove the given LogDelegate from this Instance.
void BK_Runtime_removeLogDelegate(BK_Env* env, BK_Runtime self, BK_LogDelegate delegate);

// Forwards the given type/message to all log handlers attached to this instance.
void BK_Runtime_log(BK_Env* env, BK_Runtime self, BK_LogSource source, BK_LogType type, bk_string clazz, bk_string name, bk_string message);
void BK_Runtime_free(BK_Env*, BK_Runtime self);

// =========================================
// interface HostExecutable
//
// Represents a reference to the executable file of the berkelium host process.
// =========================================

// Returns the associated Runtime.
BK_Runtime BK_HostExecutable_getRuntime(BK_Env* env, BK_HostExecutable self);

// Returns the full (native) path to the berkelium host executable represented by this object.
bk_string BK_HostExecutable_getPath(BK_Env* env, BK_HostExecutable self);

// Returns the version of this berkelium host executable.
BK_HostVersion BK_HostExecutable_getVersion(BK_Env* env, BK_HostExecutable self);
void BK_HostExecutable_free(BK_Env*, BK_HostExecutable self);

// =========================================
// interface Profile
//
// Represents a berkelium profile on disk.
// =========================================

// Returns the associated Runtime.
BK_Runtime BK_Profile_getRuntime(BK_Env* env, BK_Profile self);

// Returns true if this profile is already in use.
bk_bool BK_Profile_isInUse(BK_Env* env, BK_Profile self);

// Returns true if this profile was found on disk.
bk_bool BK_Profile_isFound(BK_Env* env, BK_Profile self);

// Returns true if this profile can be used without updating this profile to a newer version.
bk_bool BK_Profile_isSameVersion(BK_Env* env, BK_Profile self);

// Returns true if this profile is from a newer berkelium host version.
bk_bool BK_Profile_isTooNew(BK_Env* env, BK_Profile self);

// Returns the name of the application or “berkelium” if not specified.
bk_string BK_Profile_getApplicationName(BK_Env* env, BK_Profile self);

// Returns the full path to the used Profile.
bk_string BK_Profile_getProfilePath(BK_Env* env, BK_Profile self);

// Lock or Unlock the Profile so another instance can't open it for writing.
void BK_Profile_setLocked(BK_Env* env, BK_Profile self, bk_bool locked);

// Returns true if this Profile instance holds the Profile lock.
bk_bool BK_Profile_isLocked(BK_Env* env, BK_Profile self);
void BK_Profile_free(BK_Env*, BK_Profile self);

// =========================================
// interface Logger
// =========================================
void BK_Logger_debug(BK_Env* env, BK_Logger self, bk_string message);
void BK_Logger_info(BK_Env* env, BK_Logger self, bk_string message);
void BK_Logger_warn(BK_Env* env, BK_Logger self, bk_string message);
void BK_Logger_error(BK_Env* env, BK_Logger self, bk_string message);
void BK_Logger_free(BK_Env*, BK_Logger self);

// =========================================
// interface Instance
//
// Represents a running berkelium host instance.
// =========================================

// Returns the associated Runtime.
BK_Runtime BK_Instance_getRuntime(BK_Env* env, BK_Instance self);

// Closes all open Windows/Tabs and the profile, terminates the host.
void BK_Instance_close(BK_Env* env, BK_Instance self);

// Returns the profile used to launch this instance.
BK_Profile BK_Instance_getProfile(BK_Env* env, BK_Instance self);

// Returns the executable used to launch this instance.
BK_HostExecutable BK_Instance_getExecutable(BK_Env* env, BK_Instance self);

// Add the given HostDelegate to this Instance.
void BK_Instance_addHostDelegate(BK_Env* env, BK_Instance self, BK_HostDelegate delegate);

// Remove the given HostDelegate from this Instance.
void BK_Instance_removeHostDelegate(BK_Env* env, BK_Instance self, BK_HostDelegate delegate);

// Returns the number of active Windows.
bk_int32 BK_Instance_getWindowCount(BK_Env* env, BK_Instance self);

// Returns a list of all active windows.
BK_WindowList* BK_Instance_getWindowList(BK_Env* env, BK_Instance self);

// Open a new window.
BK_Window BK_Instance_createWindow(BK_Env* env, BK_Instance self, bk_bool incognito);
void BK_Instance_free(BK_Env*, BK_Instance self);

// =========================================
// interface Window
// =========================================

// Returns the associated Runtime.
BK_Runtime BK_Window_getRuntime(BK_Env* env, BK_Window self);

// Returns the current tab count.
bk_int32 BK_Window_getTabCount(BK_Env* env, BK_Window self);

// Returns an ordered list of all tabs in this window.
BK_TabList* BK_Window_getTabList(BK_Env* env, BK_Window self);

// Creates a new (about:blank) Tab.
BK_Tab BK_Window_createTab(BK_Env* env, BK_Window self);

// Returns the Instance used to create this Window.
BK_Instance BK_Window_getInstance(BK_Env* env, BK_Window self);

// Move this Tab to the given index.
void BK_Window_moveTo(BK_Env* env, BK_Window self, BK_Tab tab, bk_int32 index);

// Returns true if this is a incognito window.
bk_bool BK_Window_isIncognito(BK_Env* env, BK_Window self);
void BK_Window_free(BK_Env*, BK_Window self);

// =========================================
// interface Tab
// =========================================

// Returns the associated Runtime.
BK_Runtime BK_Tab_getRuntime(BK_Env* env, BK_Tab self);

// Closes this tab and removes it from the window.
void BK_Tab_close(BK_Env* env, BK_Tab self);

// Wait until all pending Java Script Events are handled.
void BK_Tab_sync(BK_Env* env, BK_Tab self);

// Add a TabDelegate to this tab.
void BK_Tab_addTabDelegate(BK_Env* env, BK_Tab self, BK_TabDelegate delegate);

// Remove a TabDelegate from this tab.
void BK_Tab_removeTabDelegate(BK_Env* env, BK_Tab self, BK_TabDelegate delegate);

// Returns the Window of this Tab.
BK_Window BK_Tab_getWindow(BK_Env* env, BK_Tab self);

// Set the size of this tab.
void BK_Tab_resize(BK_Env* env, BK_Tab self, bk_int32 width, bk_int32 height);

// Set the URL of this tab. A new tab has the url “about:blank”.
void BK_Tab_navigateTo(BK_Env* env, BK_Tab self, bk_string url);
void BK_Tab_free(BK_Env*, BK_Tab self);

#ifdef __cplusplus
}
#endif

#endif // BERKELIUM_API_H_
