#include "common.h"

static void SHADER_CHECK(GLuint id)  
{
    int compiled = 0;
    glGetShaderiv (static_cast<GLuint>(id), GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLint       lenght;
        std::string message;
        glGetShaderiv (static_cast<GLuint>(id), GL_INFO_LOG_LENGTH, &lenght);
        if (lenght > 1)
        {
            message.resize(static_cast<size_t>(lenght));
            glGetShaderInfoLog(id, lenght, NULL, &message[0]);
            glDeleteShader (id);
            FATAL("can't compile shader: %s",message.c_str());
        }
    }
}

material::material(strref sh)
{
    auto vstr  = "precision highp float;\n#define VERT_SHADER\n" + stream(sh).str();
    auto fstr  = "precision highp float;\n#define FRAG_SHADER\n" + stream(sh).str();
    auto v_src = vstr.c_str();
    auto f_src = fstr.c_str();
    auto v_shader = glCreateShader(GL_VERTEX_SHADER);    
    auto f_shader = glCreateShader(GL_FRAGMENT_SHADER);  
    _id = glCreateProgram(); 
    if(v_shader == 0 || f_shader == 0 || _id == 0) 
       FATAL("can't create shader");
    glShaderSource(v_shader, 1, &v_src, NULL); 
    glShaderSource(f_shader, 1, &f_src, NULL); 
    glCompileShader(v_shader);  SHADER_CHECK(v_shader);
    glCompileShader(f_shader);  SHADER_CHECK(f_shader);
    glAttachShader(_id, v_shader);
    glAttachShader(_id, f_shader);
    glLinkProgram(_id);       
}	

material::~material()
{
	if(!glIsProgram(_id)) return;
    glDeleteProgram(_id);
}
