#include "terrain.h"

_MODULE("TERRAIN");

mesh::ptr terrain::make_tile(float size, uint16_t slice, float mul, image::cref hmap) // fix: unsafe!
{
    auto sz = size * .5f;
    float xy_step  = size / slice;
    float st_step = 1.f  / slice;    
    
    std::vector<gl::vertex>  _v;
    std::vector<uint16_t>    _i;
    for (auto y = -sz, t = 0.f; y <= sz; y += xy_step, t+=st_step)
        for (auto x = -sz, s = 0.f; x <= sz; x += xy_step, s+=st_step)
        {   
            math::vec3 n({0,0,1});
            float z = 0;
            if(hmap!=nullptr)
            {    
                int bpp = hmap->_bpp / 8;
                int tx  = s * hmap->_width;
                int ty  = t * hmap->_height;
                int ndx = (tx * bpp) + (ty * hmap->_width * bpp);
                z = -(hmap->_data[ndx+3]) / 255.f * mul ;
                n = math::vec3
                (
                    (hmap->_data[ndx+0]) ,
                    (hmap->_data[ndx+1]) ,
                    (hmap->_data[ndx+2]) 
                );
            }
            _v.push_back({x, y, z, s, t, 0, n.x, n.y, n.z});
            
            auto  o = object::make(_leaf_mesh, _leaf_mat);
            o->translate(math::vec3(x,y,z));
            _leafs.push_back(o);
        }
    for(uint sq = 0; sq < slice * slice; sq++)
    {
         uint16_t o = sq / slice + sq;
         uint16_t r = o + 1;
         uint16_t u = r + slice ;
         uint16_t d = u + 1;
        _i.insert(_i.end(),{o,r,d,d,u,o}); 
    }
    return mesh::make(_v,_i,GL_TRIANGLES);
}

mesh::ptr terrain::make_leaf(float w, float h)
{
    return mesh::make({
        {w*  0, 0, 0,        0,0,  0,  0,1,0},
        {w*  1, 0, 0,        1,0,  0,  0,1,0},
        {w* .3f,0,-8.f *h,  .5,1,-.1,  0,1,0},
        {w* .2f,0,-6.f *h,  .5,1, .1,  0,1,0},
        {w* .3f,0,-4.f *h,  .5,1, .15, 0,1,0},
        {w* .2f,0,-3.f *h,  .5,1,-.15,  0,1,0},
        {w* .2f,0,-1.f *h,  .5,1, .2,  0,1,0}},
        {0,1,2,0,1,3, 0,1,4,0,1,5, 0,1,6}, 
        GL_TRIANGLES);   
} 

terrain::terrain(scene::cref sc, float tile_size, uint16_t slice, float h, strref hmap_file, strref texture):
      _tex0(image::make(texture)),
      _scene(sc),
      _tile_mat(material::make("shaders/terrain.shader")),
      _leaf_mat(material::make("shaders/leaf.shader")),
      _leaf_mesh(make_leaf(.3,.3)),
      _tile_size(tile_size),
      _tile_slice(slice),
      _tile_h(h)
{
    if(!hmap_file.empty())
        _hmap = image::make(hmap_file);
    
    auto tile = object::make
    (
        terrain::make_tile(tile_size,slice,h,_hmap),
        _tile_mat
    );
    tile->set_texture(0, _tex0);    
    _scene->add(tile);
    for(auto & o:_leafs)
        _scene->add(o);
}
