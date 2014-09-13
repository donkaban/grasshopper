LOCAL_PATH 	  := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE  := grasshopper

MICRO_SRC:= microGL/impl/minimath.cpp    \
			microGL/impl/stream.cpp      \
			microGL/impl/image.cpp       \
			microGL/impl/material.cpp    \
			microGL/impl/mesh.cpp        \
			microGL/impl/object.cpp      \
			microGL/impl/scene.cpp       \
			microGL/impl/app.cpp         \

TERRAIN_SRC:= terrain/terrain.cpp


LOCAL_SRC_FILES  :=  main.cpp $(MICRO_SRC) $(TERRAIN_SRC)
LOCAL_CPPFLAGS   := -std=c++11 -pthread 	-fexceptions
LOCAL_LDLIBS     := -llog -landroid -lGLESv2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/microGL

include $(BUILD_SHARED_LIBRARY)