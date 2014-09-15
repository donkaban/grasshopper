#include "microGL/micro.h"
#include "terrain/terrain.h"

_MODULE("MAIN");

class my_app : public app
{
    void onInit() final
    {
        auto cube_mat  = material::make("shaders/test.shader");
        auto cube_mesh = mesh::make_cube(1,1,1);
        auto tex1 = image::make("textures/green.tga");
        auto tex2 = image::make("textures/red.tga");
        auto hmap = image::make("textures/tile.tga");
        
        for(int x = -20; x <= 20; x += 5)
            for(int z = -20; z <= 20; z +=5)
        {        
            auto cube = object::make (cube_mesh, cube_mat);
            cube->set_texture(0,tex1);
            cube->set_texture(1,tex2);
            cube->translate(math::vec3(x,-5,z));
            cubes.push_back(cube);
            get_scene()->add(cube);
        }
   
        tile_1 = object::make
        (
            terrain::make_tile(60,60,10,hmap),
            material::make("shaders/terrain.shader")
        );
        tile_1->set_texture(0, tex2);    
        tile_1->translate(math::vec3(0,-8,0));
        tile_1->rotate(math::vec3(-90* RAD2DEG,0,0));
     
        get_scene()->add(tile_1);
 
    }
    void onUpdate(float dt) final
    {
       for(auto &cube : cubes)
        cube->rotate(math::vec3(0.01,0.01,.01)) ;
     
    }   

    void onTouch(uint x,uint y)    {}
    void onRelease(uint x,uint y)  {}
    void onMove(int dx, int dy)    
    {
        get_scene()->cam()->translate(math::vec3(0,0,-dy * 0.02));
        get_scene()->cam()->rot_y(dx * 0.0005);
        auto p = get_scene()->cam()->pos();

        PRINT("CAM: ",p.x,"   ",p.y,"   ",p.z);
    };
  


private:
    std::vector<object::ptr> cubes;
    object::ptr tile_1;
};

RUN_APP(my_app)
