#include <jni.h>
#include <android/asset_manager_jni.h>
#include <mutex>
#include "micro.h"

#define LOCK_GUARD  std::lock_guard<std::mutex> lock(locker);
#define DECLARE(tag,...) JNIEXPORT void JNICALL Java_com_kaban_grasshopper_Native_##tag

static std::mutex  locker;
static app::ptr    application; 

extern "C" {
DECLARE(init)(JNIEnv *env, jobject obj, jobject assetMgr)
{
    LOCK_GUARD
    stream::init(AAssetManager_fromJava(env, assetMgr));
    application = __APP_INSTANCE();
}

DECLARE(draw)(JNIEnv *env, jobject obj)
{
    LOCK_GUARD
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    application->onUpdate(1);
    application->_scene->render();
}

DECLARE(resize)(JNIEnv *env, jobject obj, jint w, jint h)
{
    LOCK_GUARD
    INFO("viewport resize to %dx%d\n",w,h);
    glLineWidth(10);
    glViewport(0, 0, w, h);
    glClearColor(.1, .1, .2, 0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL); 
    application->onInit(w,h);
}




}