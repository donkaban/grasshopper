#ifndef __GRASSHOPPER_TERRAIN__
#define __GRASSHOPPER_TERRAIN__

#include "micro.h"


class terrain : public Iref<terrain,scene::cref,float, uint16_t, float, strref, strref>
{
public:	

	terrain(scene::cref, float, uint16_t, float, strref, strref);

private:
	mesh::ptr make_tile(float, uint16_t, float, image::cref);
	mesh::ptr make_leaf(float, float); 
	std::vector<object::ptr> _leafs;

	image::ptr  	_hmap;
	image::ptr  	_tex0;
	scene::cref 	_scene;
	material::ptr 	_tile_mat;
	material::ptr 	_leaf_mat;
	mesh::ptr       _leaf_mesh;

	float 		_tile_size; 
	uint16_t 	_tile_slice; 
	float 		_tile_h;
};



#endif

