#include <jni.h>
#include <android/asset_manager_jni.h>
#include <mutex>
#include "micro.h"

_MODULE("JNI");

static struct
{
    uint mx = 0;
    uint my = 0;
    int  dx = 0;
    int  dy = 0;

    bool moved    = false;
    bool pressed  = false;
    bool released = false;

    void clear() {moved=pressed=released=false;}
    bool dirty() {return moved || pressed || released;}
       
} input;

static std::mutex  locker;
static app::ptr    application; 
static JavaVM *    javaVM;

#define MAIN_CLASS_NAME "com/kaban/grasshopper/Main"
#define DECL_VOID(tag,...) JNIEXPORT void JNICALL Java_com_kaban_grasshopper_engine_##tag
#define DECL_BOOL(tag,...) JNIEXPORT jint JNICALL Java_com_kaban_grasshopper_engine_##tag

#define LOCK_GUARD std::lock_guard<std::mutex> lock(locker);

template<typename ... T>
void jCall(JNIEnv *  env,const char *methodName, const char *methoodSignature,T && ... args)
{
    auto klass = env->FindClass(MAIN_CLASS_NAME);
    if(!klass)  ABORT("can't find engine class");
    auto method = env->GetStaticMethodID(klass, methodName,methoodSignature); 
    if(!method) ABORT("can't find method %s.%s(%s)", MAIN_CLASS_NAME,methodName, methoodSignature);
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

DECL_VOID(init)(JNIEnv *env, jobject obj, jobject assetMgr)
{
    LOCK_GUARD
    stream::init(AAssetManager_fromJava(env, assetMgr));
    application = __APP_INSTANCE();
}

DECL_VOID(draw)(JNIEnv *env, jobject obj)
{
    LOCK_GUARD
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(input.dirty())
    {    
        if(input.pressed)  {application->onTouch(input.mx, input.my);   input.pressed  = false;}
        if(input.moved)    {application->onMove(input.dx, input.dy);    input.moved    = false;}
        if(input.released) {application->onRelease(input.mx, input.my); input.released = false;}
       
    }
    application->onUpdate(1); // fixit: dt!
    application->get_scene()->render();
}

DECL_VOID(resize)(JNIEnv *env, jobject obj, jint w, jint h)
{
    LOCK_GUARD
    INFO("viewport resize to ",w,"x",h);
    glViewport(0,0,w,h);
    glClearColor(.2, .2, .3, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    application->set_scene(scene::make(w*1,h*1));
    application->onInit();
}

DECL_BOOL(onTouch) (JNIEnv *env, jobject obj, jint x, jint y)
{
    LOCK_GUARD
    input.mx = x;
    input.my = y;
    input.pressed = true;
    return true;
}

DECL_BOOL(onRelease) (JNIEnv *env, jobject obj, jint x, jint y)
{
    LOCK_GUARD
    input.mx = x;
    input.my = y;
    input.released = true;
    return true;
}
DECL_BOOL(onMove) (JNIEnv *env, jobject obj, jint x, jint y)
{
    LOCK_GUARD
    input.dx = input.mx - x;
    input.dy = input.my - y;
    input.mx = x;
    input.my = y;
    input.moved = true;
    return true;

}



}
