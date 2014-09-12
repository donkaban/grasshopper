LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := grasshopper

MINIGL_SRC := 	minigl/impl/minimath.cpp    \
				minigl/impl/stream.cpp      \
				minigl/impl/auxgl.cpp       \
				minigl/impl/image.cpp       \
				minigl/impl/material.cpp    \
				minigl/impl/mesh.cpp        \
				minigl/impl/object.cpp      \
				minigl/impl/scene.cpp       \

LOCAL_SRC_FILES :=  main.cpp $(MINIGL_SRC)


LOCAL_LDLIBS := -llog -landroid -lGLESv2
LOCAL_CFLAGS := -Ijni/minigl
include $(BUILD_SHARED_LIBRARY)