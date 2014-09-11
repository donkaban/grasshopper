#include "common.h"
#include <jni.h>

#define CLASS_NAME "com/kaban/grasshopper"
#define DECL_METHOD(tag,...) JNIEXPORT void JNICALL Java_com_kaban_grasshopper_Native_##tag

extern "C" {

DECL_METHOD(init)(JNIEnv *env, jobject obj)
{
	D_LOG("call init()\n");


}

DECL_METHOD(draw)(JNIEnv *env, jobject obj)
{
	
}

DECL_METHOD(resize)(JNIEnv *env, jobject obj, jint w, jint h)
{
	D_LOG("call resize(%d,%d)\n",w,h);

}




}
