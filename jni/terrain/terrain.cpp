#include "terrain.h"

_MODULE("TERRAIN");

mesh::ptr terrain::make_ground()
{
    PRINT("create tile ....");
    auto sz = _tile_size * .5f;
    float xy_step  = _tile_size / _tile_slice  ;
    float st_step = 1.f   / _tile_slice  ;    

    std::vector<gl::vertex>  _v;
    std::vector<uint16_t>    _i;
    for (auto y = -sz, t = 0.f; y <= sz; y += xy_step, t+=st_step)
        for (auto x = -sz, s = 0.f; x <= sz; x += xy_step, s+=st_step)
        {   
            auto h = _hmap->get_pixel(s,t);
            auto z = -h.a / 255.f * _tile_h;
            _v.push_back({x, y, z, s, t, 0, h.r/255.f, h.g/255.f, h.b/255.f});
        }
    for(uint sq = 0; sq < _tile_slice * _tile_slice; sq++)
    {
         uint16_t o = sq / _tile_slice + sq;
         uint16_t r = o + 1;
         uint16_t u = r + _tile_slice ;
         uint16_t d = u + 1;
        _i.insert(_i.end(),{o,r,d,d,u,o}); 
    }
    return mesh::make(_v,_i,GL_TRIANGLES);
}

mesh::ptr terrain::make_leaf(float w, float h)
{
    return mesh::make({
        {w* -.25f,  0, 0,         0,0,  0,  0,-1,0},
        {w*  .25f,  0, 0,         1,0,  0,  0,-1,0},
        {w*  .0f,   0,-18.f *h,  .5,1,-.2,  0,-1,0},
        {w*  0.f,   2, 0,         0,0,  0,  0,-1,0},
        {w*  .5f,   2, 0,         1,0,  0,  0,-1,0},
        {w*  .25f,  2,-15.f *h,  .5,1, .15,  0,-1,0},
        {w*  2.f,  -2, 0,         0,0,  0,  0,-1,0},
        {w*  2.5f, -2, 0,         1,0,  0,  0,-1,0},
        {w*  2.25f,-2,-8.f  *h,  .5,1,-.1,  0,-1,0},
        {w* -3.f,  -1, 0,         0,0,  0,  0,-1,0},
        {w* -2.5f, -1, 0,         1,0,  0,  0,-1,0},
        {w* -2.75f,-1,-12.f *h,  .5,1, .5,  0,-1,0},
        },
        {0,1,2,3,4,5,6,7,8,9,10,11}, 
     
        GL_TRIANGLES);   
} 

std::vector<object::ptr> terrain::make_grass(math::vec3::cref tr)
{
    PRINT("create grass ....");
    auto sz = _tile_size * .5f;
    float xy_step  = _tile_size / _tile_slice  ;
    float st_step = 1.f   / _tile_slice  ;    

    std::vector<object::ptr> grass;
    for (auto y = -sz, t = 0.f; y <= sz; y += xy_step * GRASS_DIV, t+=st_step * GRASS_DIV)
        for (auto x = -sz, s = 0.f; x <= sz; x += xy_step * GRASS_DIV, s+=st_step * GRASS_DIV)
        {   
            auto g = _tex0->get_pixel(s,t).a;

            if(g > GRASS_THRASHOLD)
            {   
                auto h = _hmap->get_pixel(s,t);
                auto z = -h.a / 255.f * _tile_h;
                auto  o = object::make(_leaf_mesh, _leaf_mat);
                o->translate(tr);
                o->translate(math::vec3(x,y,z));
                o->check(true);
                grass.push_back(o);
            }
        }
    return grass;   
}

#define TILES 6  // ONLY TEST!

terrain::terrain(scene::cref sc, float tile_size, uint16_t slice, float h, strref hmap_file, strref texture):
      _hmap(image::make(hmap_file)),
      _tex0(image::make(texture)),
      _scene(sc),
      _tile_mat(material::make("shaders/terrain.shader")),
      _leaf_mat(material::make("shaders/leaf.shader")),
      _leaf_mesh(make_leaf(.25,.1)),
      _tile_size(tile_size),
      _tile_slice(slice),
      _tile_h(h)
{
    _tile_mesh = terrain::make_ground();
    
    for(int x = -tile_size * TILES; x <=tile_size * TILES; x += tile_size)
        for(int y = -tile_size * TILES; y <= tile_size * TILES; y += tile_size)
    {
        tile t;
        t.pos   = math::vec3(x,y,0);
        t.ground = object::make(_tile_mesh, _tile_mat);
        t.grass  = make_grass(t.pos);
        t.ground->translate(t.pos);
        t.ground->check(false);
        t.ground->set_texture(0, _tex0);
        t.ground->set_texture(1, _hmap);
        _tiles.push_back(t);
    }
    for(auto &t: _tiles)
    {
        _scene->add(t.ground);
        for(auto &l : t.grass)
            _scene->add(l);
    }    

}
