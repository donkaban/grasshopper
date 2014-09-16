#include "micro.h"
using namespace math;

_MODULE("OBJECT");

object::object(mesh::cref _mesh, material::cref _mat):
    _check(false),
    _mesh(_mesh),
    _material(_mat)
  
{
    INFO("create object");
}

object::~object()
{}

void object::set_texture(int n, image::cref img) {_texture[n] = img;} //fix: unsafe! 

void object::translate(vec3::cref v) {_transform *= mat4::translate(v);}
void object::rotate(vec3::cref v)    {_transform.rotate(v);}

void object::render()
{
    glUniformMatrix4fv(_material->uni().model, 1,GL_FALSE,_transform.data);
    for(auto i=0; i< 4; i++)
    {   
        if(_material->uni().t[i] !=-1 && _texture[i])
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, _texture[0]->getID()); 
            glUniform1i(_material->uni().t[i],i);
        } 
    }
    _mesh->render(_material); 
 }

math::mat4 & object::T()   {return _transform;}
void object::check(bool b) {_check = b;}
