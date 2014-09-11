#include "auxgl.h"

template<> void uniform<int  >::set(const int &v)   const  {glUniform1i(_id, v);}
template<> void uniform<float>::set(const float &v) const  {glUniform1f(_id, v);}
template<> void uniform<vec3 >::set(vec3::cref v)   const  {glUniform3f(_id,v.x,v.y,v.z);}
template<> void uniform<mat4 >::set(mat4::cref m)   const  {glUniformMatrix4fv(_id, 1,GL_FALSE, m.data);}

void _check(int getter, GLuint id, GLenum type)
{
    struct  
    {
         std::function<void(GLuint, GLenum, GLint *)> get ;             
         std::function<void(GLuint, GLsizei, GLsizei *, GLchar *)> logg ;
    }
    nfo[] = {{glGetShaderiv,glGetShaderInfoLog},{glGetProgramiv,glGetProgramInfoLog}}; 
    int result = 0;
    nfo[getter].get(id, type, &result);
    if(!result)
    {
        GLint len;
        std::string msg;
        nfo[getter].get(id, GL_INFO_LOG_LENGTH, &len);
        if (len > 1)
        {
            msg.resize(static_cast<uint>(len));
            nfo[getter].logg(id, len, NULL, &msg[0]);
            FATAL("shader error : %s ", msg.c_str());
        }
    }   
}
void   GL::COMPILE_CHECK(GLuint id)  {_check(0, id, GL_COMPILE_STATUS);}
void   GL::LINK_CHECK(GLuint id)     {_check(1, id, GL_LINK_STATUS);}
