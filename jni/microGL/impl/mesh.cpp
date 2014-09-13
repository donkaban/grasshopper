#include "common.h"

using namespace math;

mesh::mesh(const std::initializer_list<gl::vertex>  &v) :
    vertexes(std::move(v))
{
    INFO("create mesh from vector");
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(gl::vertex) , &vertexes[0], GL_STATIC_DRAW);
}   

mesh::~mesh()
{
    if(!glIsBuffer(_id)) return;
    glDeleteBuffers(1, &_id);
}

#define SET_ATTR(id, offset) if(mat->atr().id !=-1){\
    glVertexAttribPointer(mat->atr().id,vec3::size,GL_FLOAT,GL_FALSE,sizeof(gl::vertex),reinterpret_cast<const void *>(offset));\
    glEnableVertexAttribArray(mat->atr().id);}

void mesh::render(material::cref mat)
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    SET_ATTR(p, 0 * sizeof(vec3))
    SET_ATTR(u, 1 * sizeof(vec3))
    SET_ATTR(t, 2 * sizeof(vec3))
    SET_ATTR(b, 3 * sizeof(vec3))
    SET_ATTR(n, 4 * sizeof(vec3))
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexes.size());
}
