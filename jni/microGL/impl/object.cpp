#include "micro.h"
using namespace math;

object::object(mesh::cref _mesh, material::cref _mat):
    _mesh(_mesh),
    _material(_mat)
{
    INFO("create object");
}

object::~object()
{}

void object::set_texture(int n, image::cref img) {_texture[n] = img;} //fix: unsafe! 
void object::translate(vec3::cref v) {_transform *= mat4::translate(v);}
void object::rotate(vec3::cref v)    {_transform *= mat4::rot_x(v.x) * mat4::rot_y(v.y) * mat4::rot_z(v.z) ;}

void object::render(material::cref mat)
{
    glUniformMatrix4fv(mat->uni().model, 1,GL_FALSE,_transform.data);
    for(auto i=0; i< 4; i++)
    {   
        if(mat->uni().t[i] !=-1 && _texture[i])
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, _texture[0]->getID()); 
            glUniform1i(mat->uni().t[i],i);
        } 
    }
    _mesh->render(mat); 
 }
