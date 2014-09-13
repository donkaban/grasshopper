#include "microGL/micro.h"

class my_app : public app
{
    void onInit(float w,float h) override
    {

        _scene = scene::make(45,w/h,0.1,100);
        _scene->translate(math::vec3(0,0,-5));

        auto my_mesh = mesh::make_cube(1,1,1);
               
        
        auto my_mat = material::make("shaders/test.shader");
        auto t1  = image::make("textures/green.tga");
        auto t2  = image::make("textures/red.tga");
        my_obj   = object::make(my_mesh,my_mat);
        my_obj->set_texture(0,t2);
        my_obj->set_texture(1,t1);
        _scene->add(my_obj);
    }

    void onUpdate(float dt) override
    {
       my_obj->rotate(math::vec3(0.01,0.01, .01)) ;
    }   
private:
    object::ptr     my_obj;
};

RUN_APP(my_app)
