#include "microGL/micro.h"

class my_app : public app
{
    void onInit() final
    {
        for(int x = -5; x <= 5; x ++)
            for(int y = -10; y <= 10; y ++)
        {        
            auto cube = object::make
            (
                mesh::make_cube(.8,.8,.8),
                material::make("shaders/test.shader")
            );
            cube->set_texture(0,image::make("textures/green.tga"));
            cube->set_texture(1,image::make("textures/red.tga"));
            cube->translate(math::vec3(x,y,-25));
            cubes.push_back(cube);
            get_scene()->add(cube);
        }
    }    

    void onUpdate(float dt) final
    {
       for(auto &cube : cubes)
        cube->rotate(math::vec3(0.1,0.1, .1)) ;
    }   
private:
    std::vector<object::ptr> cubes;
};

RUN_APP(my_app)
