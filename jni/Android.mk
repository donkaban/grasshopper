LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := grasshopper

MINIGL_SRC := 	microGL/impl/minimath.cpp    \
				microGL/impl/stream.cpp      \
				microGL/impl/image.cpp       \
				microGL/impl/material.cpp    \
				microGL/impl/mesh.cpp        \
				microGL/impl/object.cpp      \
				microGL/impl/scene.cpp       \

LOCAL_SRC_FILES :=  main.cpp $(MINIGL_SRC)


LOCAL_LDLIBS := -llog -landroid -lGLESv2
LOCAL_CFLAGS := -Ijni/microGL
include $(BUILD_SHARED_LIBRARY)