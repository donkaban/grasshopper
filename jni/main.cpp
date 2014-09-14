#include "microGL/micro.h"

class my_app : public app
{
    void onInit() final
    {
        auto cube_mat  = material::make("shaders/test.shader");
        auto cube_mesh = mesh::make_cube(.8,.8,.8);
        auto tex1 = image::make("textures/green.tga");
        auto tex2 = image::make("textures/red.tga");
        for(int x = -2; x <= 2; x ++)
            for(int y = -2; y <= 2; y ++)
        {        
            auto cube = object::make (cube_mesh, cube_mat);
            cube->set_texture(0,tex1);
            cube->set_texture(1,tex2);
            cube->translate(math::vec3(x,y,-15));
            cubes.push_back(cube);
            get_scene()->add(cube);
        }
   
        back = object::make
        (
            mesh::make_tile(100,20),
            material::make("shaders/back.shader")
        );
        back->set_texture(0, tex2);    
        back->translate(math::vec3(0,-7,-20));
        back->rotate(math::vec3(90 * RAD2DEG,0,0));
     
        get_scene()->add(back);
    }
    void onUpdate(float dt) final
    {
      
       for(auto &cube : cubes)
        cube->rotate(math::vec3(0.01,0.01,.01)) ;
    }   
private:
    std::vector<object::ptr> cubes;
    object::ptr back;
};

RUN_APP(my_app)
