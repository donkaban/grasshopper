#include "terrain.h"

_MODULE("TERRAIN");


mesh::ptr terrain::make_tile()
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
    // fix : perf waste - twice loop
    for (auto y = -sz, t = 0.f; y <= sz; y += xy_step * GRASS_DIV, t+=st_step * GRASS_DIV)
        for (auto x = -sz, s = 0.f; x <= sz; x += xy_step * GRASS_DIV, s+=st_step * GRASS_DIV)
        {   
            auto g = _tex0->get_pixel(s,t).a;

            if(g > GRASS_THRASHOLD)
            {   
                auto h = _hmap->get_pixel(s,t);
                auto z = -h.a / 255.f * _tile_h;
                auto  o = object::make(_leaf_mesh, _leaf_mat);
                o->translate(math::vec3(x,y,z));
                _leafs.push_back(o);
            }
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

terrain::terrain(scene::cref sc, float tile_size, uint16_t slice, float h, strref hmap_file, strref texture):
      _tex0(image::make(texture)),
      _scene(sc),
      _tile_mat(material::make("shaders/terrain.shader")),
      _leaf_mat(material::make("shaders/leaf.shader")),
      _leaf_mesh(make_leaf(.25,.1)),
      _tile_size(tile_size),
      _tile_slice(slice),
      _tile_h(h)
{
    if(!hmap_file.empty())
        _hmap = image::make(hmap_file);

    auto tile = object::make(terrain::make_tile(),_tile_mat);
    tile->set_texture(0, _tex0);
    tile->set_texture(1, _hmap);
   
    _scene->add(tile);
    for(auto & o:_leafs)
        _scene->add(o);
}
