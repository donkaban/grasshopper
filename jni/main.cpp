#include "microGL/micro.h"
#include "terrain/terrain.h"

_MODULE("MAIN");

class my_app : public app
{
    void onInit() final
    {
        terrain::make(get_scene(),60,20,10,"textures/tile_hmap.tga","textures/tile_tex.tga");
        get_scene()->set_culling(60);
    }


    void onUpdate(float dt) final
    {}   

    void onTouch(uint x,uint y)    {}
    void onRelease(uint x,uint y)  {}
    void onMove(int dx, int dy)    
    {
        get_scene()->cam()->move(math::vec3(dx * 0.03,dy * 0.05,0));
        auto p = get_scene()->cam()->pos();

        PRINT(p.x,":",p.y,":",p.z);
    };

private:

};

RUN_APP(my_app)
