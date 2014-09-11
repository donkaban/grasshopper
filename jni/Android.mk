LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := grasshopper

LOCAL_SRC_FILES :=        \
	main.cpp              \
	minigl/common.cpp     \
	minigl/auxgl.cpp     \
	minigl/elementary.cpp \



LOCAL_LDLIBS := -llog -landroid -lGLESv2
LOCAL_CFLAGS := -DPLATFORM_ANDROID -Ijni/minigl
include $(BUILD_SHARED_LIBRARY)