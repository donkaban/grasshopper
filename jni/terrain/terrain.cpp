#include "terrain.h"

mesh::ptr terrain::make_tile(float size, uint16_t slice, float mul, image::cref hmap) // fix: unsafe!
{
    auto sz = size * .5f;
    float xy_step  = size / slice;
    float st_step = 1.f  / slice;    
	int bpp = hmap->_bpp / 8;

    std::vector<gl::vertex>  _v;
    std::vector<uint16_t>    _i;
    for (auto y = -sz, t = 0.f; y <= sz; y += xy_step, t+=st_step)
        for (auto x = -sz, s = 0.f; x <= sz; x += xy_step, s+=st_step)
        {	
        	int tx  = s * hmap->_width;
        	int ty  = t * hmap->_height;
            int ndx = (tx * bpp) + (ty * hmap->_width * bpp);
            float z = (hmap->_data[ndx+3]) / 255.f * mul ;
            math::vec3 n
            (
				(hmap->_data[ndx+0]) / 255.f,
				(hmap->_data[ndx+1]) / 255.f,
				(hmap->_data[ndx+2]) / 255.f
            );
            _v.push_back({x, y, z, s, t, 0, n.x, n.y, n.z});
    	}
    for(uint sq = 0; sq < slice * slice; sq++)
    {
         uint16_t o = sq / slice + sq;
         uint16_t r = o + 1;
         uint16_t u = r + slice ;
         uint16_t d = u + 1;
        _i.insert(_i.end(),{o,r,d,d,u,o}); 
    }
    return mesh::make(_v,_i,GL_LINE_STRIP);
}
