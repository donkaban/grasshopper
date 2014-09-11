#include "elementary.h"
#include "auxgl.h"

material::material(strref vsh, strref fsh)
{
	auto v_src = stream(vsh).str().c_str();
    auto f_src = stream(fsh).str().c_str();
    auto v_shader = glCreateShader(GL_VERTEX_SHADER);    
    auto f_shader = glCreateShader(GL_FRAGMENT_SHADER);  
    _id = glCreateProgram(); 
    if(v_shader == 0 || f_shader == 0 || _id == 0) 
       FATAL("can't create shader");
    glShaderSource(v_shader, 1, &v_src, NULL); 
    glShaderSource(f_shader, 1, &f_src, NULL); 
    glCompileShader(v_shader);  GL::COMPILE_CHECK(v_shader);
    glCompileShader(f_shader);  GL::COMPILE_CHECK(f_shader);
    glAttachShader(_id, v_shader);
    glAttachShader(_id, f_shader);
    glLinkProgram(_id);         GL::LINK_CHECK(_id);
}	

material::~material()
{
	if(!glIsProgram(_id)) return;
    glDeleteProgram(_id);
}


mesh::mesh()
{}	

mesh::~mesh()
{}

