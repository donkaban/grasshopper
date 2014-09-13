#include "micro.h"
using namespace math;

std::chrono::time_point<std::chrono::system_clock> scene::start_time = std::chrono::system_clock::now();

scene::scene(float f,float a, float zn, float zf) :
    prj_m(mat4::perspective(f, a, zn, zf))
{
    INFO("create scene : %f, %f, %f, %f",f,a,zn,zf);
} 

void scene::translate(vec3::cref v) {iview_m *= mat4::translate(v);}
void scene::rotate(vec3::cref v)    {iview_m *= mat4::rot_x(v.x) * mat4::rot_y(v.y) * mat4::rot_z(v.z) ;}

void scene::add(object::cref obj)   
{
    INFO("add object to scene");
    render_list.push_back(obj);
}

void scene::render()
{   
    auto cur_time = time();
    for(auto & obj : render_list)
    {
        if(!obj->_enabled) return;
        auto mat = obj->_material;
        glUseProgram(mat->getID());
        glUniformMatrix4fv(mat->uni().prj,   1,GL_FALSE,prj_m.data);
        glUniformMatrix4fv(mat->uni().iview, 1,GL_FALSE,iview_m.data);
        glUniform1f(mat->uni().time, cur_time);
        obj->render(mat);
    }   
}

float scene::time() 
{
    auto cur = std::chrono::system_clock::now();
    std::chrono::duration<float> dt(cur - start_time);
    return dt.count();
}