#include "microGL/common.h"

#include <jni.h>
#include <android/asset_manager_jni.h>
#include <mutex>


std::shared_ptr<scene> test(float w,float h)
{
	auto s = std::make_shared<scene>(45,w/h,0.1,100);
	s->translate(vec3(0,0,-5));

	mesh::ref m (new mesh({
		{{-1, 1, 0},{0,1,0},{0,0,0},{0,0,0},{0,0,0}},
		{{-1,-1, 0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		{{ 1, 1, 0},{1,1,0},{0,0,0},{0,0,0},{0,0,0}},
		{{ 1,-1, 0},{1,0,0},{0,0,0},{0,0,0},{0,0,0}}
	}));
	
	auto mat = std::make_shared<material>("shaders/test.shader");
	auto t1 = std::make_shared<image>("textures/green.tga");
	auto t2 = std::make_shared<image>("textures/red.tga");

	auto obj = std::make_shared<object>(m,mat);
	obj->set_texture(0,t2);
	obj->set_texture(1,t1);
	
	s->add(obj);
	return s;
}

static std::shared_ptr<scene> SCENE;
static std::mutex  locker;

#define LOCK_GUARD  std::lock_guard<std::mutex> lock(locker);
#define DECLARE(tag,...) JNIEXPORT void JNICALL Java_com_kaban_grasshopper_Native_##tag

extern "C" {
DECLARE(init)(JNIEnv *env, jobject obj, jobject assetMgr)
{
	LOCK_GUARD
	stream::init(AAssetManager_fromJava(env, assetMgr));
	
}

DECLARE(draw)(JNIEnv *env, jobject obj)
{
	LOCK_GUARD
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SCENE->render();
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
    SCENE = test(w,h);
}

}
