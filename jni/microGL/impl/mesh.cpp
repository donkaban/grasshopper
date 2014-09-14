#include "micro.h"

using namespace math;

mesh::mesh(const std::vector<gl::vertex>  &v, const std::vector<uint16_t> &i, GLenum draw) :
    vertexes(std::move(v)),
    indicies(std::move(i)),
    draw_by(draw)
       
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
    SET_ATTR(n, 2 * sizeof(vec3))
    glDrawElements(draw_by,indicies.size(),GL_UNSIGNED_SHORT,&indicies[0]);
}

mesh::ptr mesh::make_plane(float width, float height)
{
    auto w = width * .5f;
    auto h = height * .5f;
    return make({
        { w, h,0,1,1,0,0,0,1},{-w, h,0,0,1,0,0,0,1},{-w,-h,0,0,0,0,0,0,1},{ w,-h,0,1,0,0,0,0,1}},
        {0,1,2,2,3,0}, 
        GL_TRIANGLES);
}

mesh::ptr mesh::make_cube(float x, float y, float t)
{
    auto w = x * .5f;
    auto h = y * .5f;
    auto z = t * .5f;
    return make({    
    {-w,-h,-z, 0, 0, 0, 0,-1, 0},{-w,-h, z, 0, 1, 0, 0,-1, 0},{ w,-h, z, 1, 1, 0, 0,-1, 0},{ w,-h,-z, 1, 0, 0, 0,-1, 0}, 
    {-w, h,-z, 1, 0, 0, 0, 1, 0},{-w, h, z, 1, 1, 0, 0, 1, 0},{ w, h, z, 0, 1, 0, 0, 1, 0},{ w, h,-z, 0, 0, 0, 0, 1, 0}, 
    {-w,-h,-z, 0, 0, 0, 0, 0,-1},{-w, h,-z, 0, 1, 0, 0, 0,-1},{ w, h,-z, 1, 1, 0, 0, 0,-1},{ w,-h,-z, 1, 0, 0, 0, 0,-1}, 
    {-w,-h, z, 0, 0, 0, 0, 0, 1},{-w, h, z, 0, 1, 0, 0, 0, 1},{ w, h, z, 1, 1, 0, 0, 0, 1},{ w,-h, z, 1, 0, 0, 0, 0, 1}, 
    {-w,-h,-z, 0, 0, 0,-1, 0, 0},{-w,-h, z, 0, 1, 0,-1, 0, 0},{-w, h, z, 1, 1, 0,-1, 0, 0},{-w, h,-z, 1, 0, 0,-1, 0, 0}, 
    { w,-h,-z, 0, 0, 0, 1, 0, 0},{ w,-h, z, 0, 1, 0, 1, 0, 0},{ w, h, z, 1, 1, 0, 1, 0, 0},{ w, h,-z, 1, 0, 0, 1, 0, 0}},
    {0,2,1,0,3,2,4,5,6,4,6,7,8,9,10,8,10,11,12,15,14,12,14,13,16,17,18,16,18,19,20,23,22,20,22,21},
    GL_TRIANGLES);         
}


