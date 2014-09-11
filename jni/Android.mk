LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := grasshopper
LOCAL_SRC_FILES := jni_bridge.cpp 
LOCAL_LDLIBS    := -llog -lGLESv2
LOCAL_CFLAGS := -DPLATFORM_ANDROID
include $(BUILD_SHARED_LIBRARY)