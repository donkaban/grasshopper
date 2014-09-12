#include "minigl/common.h"

#include <jni.h>
#include <android/asset_manager_jni.h>



void test()
{
	scene s(45,1,0.1,100); 
	mesh::ref m (new mesh({
		{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}}
	}));
	auto mat = std::make_shared<material>("shaders/test.shader");
	auto t1 = std::make_shared<image>("textures/green.tga");
	auto t2 = std::make_shared<image>("textures/red.tga");

	auto obj = std::make_shared<object>(m,mat);
	s.add(obj);


}





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

    test();


}

}
