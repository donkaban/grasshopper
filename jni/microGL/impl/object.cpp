#include "common.h"

object::object(mesh::cref _mesh, material::cref _mat):
    _mesh(_mesh),
    _material(_mat)
{
	INFO("create object");
}

object::~object()
{
 	INFO("destroy object");
}

void object::set_texture(int n, image::cref img) {_texture[n] = img;} //fix: unsafe! 
void object::render(material::cref mat)
{
 	glUniformMatrix4fv(mat->uniforms.model, 1,GL_FALSE,_transform.data);
 	for(auto i=0; i< 4; i++)
 	{	
 		if(mat->uniforms.t[i] !=-1 && _texture[i])
 		{
 			glActiveTexture(GL_TEXTURE0 + i);
        	glBindTexture(GL_TEXTURE_2D, _texture[0]->getID()); 
        	glUniform1i(mat->uniforms.t[i],i);
 		} 
	}
 	_mesh->render(mat);	
 }
