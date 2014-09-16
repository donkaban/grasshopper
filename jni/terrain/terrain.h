#ifndef __GRASSHOPPER_TERRAIN__
#define __GRASSHOPPER_TERRAIN__

#include "micro.h"

struct tile
{
	math::vec3 pos  = math::vec3::zero;
	object::ptr              ground;
	std::vector<object::ptr> grass;
};

class terrain : public Iref<terrain,scene::cref,float, uint16_t, float, strref, strref>
{
public:	
	const float   GRASS_DIV       = 0.1;
	const uint8_t GRASS_THRASHOLD = 30;

	terrain(scene::cref, float, uint16_t, float, strref, strref);

private:
	mesh::ptr make_ground();
	mesh::ptr make_leaf(float, float);

	std::vector<object::ptr> make_grass(math::vec3::cref);
	
	image::ptr  	_hmap;
	image::ptr  	_tex0;
	scene::cref 	_scene;
	material::ptr 	_tile_mat;
	mesh::ptr 	   _tile_mesh;
	material::ptr 	_leaf_mat;
	mesh::ptr       _leaf_mesh;

	float 		_tile_size; 
	uint16_t 	_tile_slice; 
	float 		_tile_h;

	std::vector<tile> _tiles;

};



#endif

