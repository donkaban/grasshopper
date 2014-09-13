LOCAL_PATH 	  := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE  := grasshopper

MICRO_GL:= 	microGL/impl/minimath.cpp    \
			microGL/impl/stream.cpp      \
			microGL/impl/image.cpp       \
			microGL/impl/material.cpp    \
			microGL/impl/mesh.cpp        \
			microGL/impl/object.cpp      \
			microGL/impl/scene.cpp       \
			microGL/impl/app.cpp         \

LOCAL_SRC_FILES  :=  main.cpp $(MICRO_GL)
LOCAL_CPPFLAGS   := -std=c++11 -pthread 	-fexceptions
LOCAL_LDLIBS     := -llog -landroid -lGLESv2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/microGL

include $(BUILD_SHARED_LIBRARY)