LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE     := RemoveEffects
LOCAL_SRC_FILES  := main.cpp mod/config.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_CFLAGS     := -Os -fvisibility=hidden -ffunction-sections -fdata-sections -DNDEBUG -DDONT_USE_STB
LOCAL_CPPFLAGS   := -std=c++17 -fno-exceptions -fno-rtti -fno-threadsafe-statics
LOCAL_LDFLAGS    := -Wl,--gc-sections -Wl,--strip-all -Wl,--build-id=none
LOCAL_LDLIBS     := -ldl
include $(BUILD_SHARED_LIBRARY)
