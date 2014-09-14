#include "microGL/micro.h"
#include "terrain/terrain.h"

_MODULE("MAIN");


class my_app : public app
{
    void onInit() final
    {
        auto cube_mat  = material::make("shaders/test.shader");
        auto cube_mesh = mesh::make_cube(.8,.8,.8);
        auto tex1 = image::make("textures/green.tga");
        auto tex2 = image::make("textures/red.tga");
        auto hmap = image::make("textures/tile.tga");
        
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
            terrain::make_tile(10,60,2,hmap),
            material::make("shaders/terrain.shader")
        );
        back->set_texture(0, tex2);    
        back->translate(math::vec3(0,-5,-25));
        back->rotate(math::vec3( -60* RAD2DEG,0,0));
     
        get_scene()->add(back);
 
    }
    void onUpdate(float dt) final
    {
      static size_t i = 0;
       for(auto &cube : cubes)
        cube->rotate(math::vec3(0.01,0.01,.01)) ;

      back->rotate(math::vec3(0.00,0.00,.01)) ;
      PRINT("counter: ", ++i);     

    }   
private:
    std::vector<object::ptr> cubes;
    object::ptr back;
};

RUN_APP(my_app)
