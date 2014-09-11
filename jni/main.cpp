#include "common.h"
#include <jni.h>
#include <android/asset_manager_jni.h>

#define DECLARE(tag,...) JNIEXPORT void JNICALL Java_com_kaban_grasshopper_Native_##tag

extern "C" {

DECLARE(init)(JNIEnv *env, jobject obj, jobject assetMgr)
{
	stream::init(AAssetManager_fromJava(env, assetMgr));
}

DECLARE(draw)(JNIEnv *env, jobject obj)
{

}

DECLARE(resize)(JNIEnv *env, jobject obj, jint w, jint h)
{
	D_LOG("viewport resize to %dx%d\n",w,h);
	glViewport(0, 0, w, h);
	glClearColor(.1, .1, .2, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL); 
    glCullFace(GL_BACK);    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}
