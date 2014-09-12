#include "common.h"

mesh::mesh(const std::vector<vertex> &v) :
	vertexes(v)
{
	INFO("create mesh from vector");
	glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(vertex) , &vertexes[0], GL_STATIC_DRAW);

}	
mesh::mesh(strref filename)
{}	

mesh::~mesh()
{
 	if(!glIsBuffer(_id)) return;
    glDeleteBuffers(1, &_id);
}

#define SET_ATTR(id, offset) if(mat->attributes.id !=-1){\
	glVertexAttribPointer(mat->attributes.id,vec3::size,GL_FLOAT,GL_FALSE,sizeof(vertex),reinterpret_cast<const void *>(offset));\
    glEnableVertexAttribArray(mat->attributes.id);}

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
