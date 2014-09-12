#include "common.h"

scene::scene(float f,float a, float zn, float zf) :
    prj_m(mat4::perspective(f, a, zn, zf))
{
 
}

void scene::translate(vec3::cref v) {iview_m *= mat4::translate(v);}
void scene::add(object::cref obj)   {render_list.push_back(obj);}
void scene::render()
{
	for(auto & obj : render_list)
	{
		glUseProgram(obj->_material->getID());

		obj->render();
	}	
}

