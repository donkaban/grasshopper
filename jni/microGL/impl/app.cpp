#include <jni.h>
#include <android/asset_manager_jni.h>
#include <mutex>
#include "micro.h"

_MODULE("JNI");

static std::mutex  locker;
static app::ptr    application; 
static JavaVM *    javaVM;

#define MAIN_CLASS_NAME "com/kaban/grasshopper/Main"
#define DECLARE(tag,...) JNIEXPORT void JNICALL Java_com_kaban_grasshopper_engine_##tag
#define LOCK_GUARD  std::lock_guard<std::mutex> lock(locker);

template<typename ... T>
void jCall(JNIEnv *  env,const char *methodName, const char *methoodSignature,T && ... args)
{
    auto klass = env->FindClass(MAIN_CLASS_NAME);
    if(!klass)  FATAL("can't find engine class");
    auto method = env->GetStaticMethodID(klass, methodName,methoodSignature); 
    if(!method) FATAL("can't find method %s.%s(%s)", MAIN_CLASS_NAME,methodName, methoodSignature);
     env->CallVoidMethod(klass,method,args...);
}  

void logger::gui(strref msg)
{
    JNIEnv * env;
    javaVM->AttachCurrentThread(&env, NULL);
    jstring m = env->NewStringUTF(msg.c_str());
    jCall(env,"print","(Ljava/lang/String;)V",m);
}

extern "C" {

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *)
{
    INFO("native module loaded");
    javaVM = vm;
    return JNI_VERSION_1_6;
}    

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
    application->onUpdate(1); // fix: dt!
    application->get_scene()->render();
}

DECLARE(resize)(JNIEnv *env, jobject obj, jint w, jint h)
{
    LOCK_GUARD
    INFO("viewport resize to ",w,"x",h);
    glViewport(0,0,w,h);
    glClearColor(.2, .2, .3, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    application->set_scene(scene::make(45,static_cast<float>(w)/static_cast<float>(h),0.1,60));
    application->onInit();
}
}
