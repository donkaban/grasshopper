#include "micro.h"

_MODULE("MATERIAL");

void _check(GLuint id)  
{
    int ok = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if(!ok)
    {
        GLint len;
        std::string message;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        if (len > 1)
        {
            message.resize(len);
            glGetShaderInfoLog(id, len, NULL, &message[0]);
            ABORT("error compile shader: ",message.c_str());
        }
    }
}

material::material(strref sh)
{
    INFO("create from ", sh);
    std::string vstr = "precision highp float;\n#define VERTEX\n"   + stream(sh).str(); // ?perf fix: loaded twice
    std::string fstr = "precision highp float;\n#define FRAGMENT\n" + stream(sh).str(); // ?perf fix: loaded twice
    auto v_src = vstr.c_str();
    auto f_src = fstr.c_str();
    auto v_shader = glCreateShader(GL_VERTEX_SHADER);    
    auto f_shader = glCreateShader(GL_FRAGMENT_SHADER);  
    _id = glCreateProgram(); 
    if(v_shader == 0 || f_shader == 0 || _id == 0) 
       ABORT("can't create shader");
    glShaderSource(v_shader, 1, &v_src, NULL); 
    glShaderSource(f_shader, 1, &f_src, NULL); 
    glCompileShader(v_shader); _check(v_shader);
    glCompileShader(f_shader); _check(f_shader); 
    glAttachShader(_id, v_shader);
    glAttachShader(_id, f_shader);
    glLinkProgram(_id);   
    attributes.lookup(_id);
    uniforms.lookup(_id);
}   

material::~material()
{
    if(!glIsProgram(_id)) return;
    glDeleteProgram(_id);
}

void gl::attr_t::lookup(int id)
{
    p = glGetAttribLocation(id,"position");
    u = glGetAttribLocation(id,"uv");
    n = glGetAttribLocation(id,"normal");
}
void gl::unif_t::lookup(int id)
{
    model = glGetUniformLocation(id,"u_model");
    iview = glGetUniformLocation(id,"u_view");
    prj   = glGetUniformLocation(id,"u_prj");
    time  = glGetUniformLocation(id,"u_time");
    eye  = glGetUniformLocation(id,"u_eye");
    t[0]  = glGetUniformLocation(id,"texture0");
    t[1]  = glGetUniformLocation(id,"texture1");
    t[2]  = glGetUniformLocation(id,"texture2");
    t[3]  = glGetUniformLocation(id,"texture3");
} 
