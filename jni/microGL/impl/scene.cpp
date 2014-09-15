#include "micro.h"
using namespace math;

_MODULE("SCENE");

std::chrono::time_point<std::chrono::system_clock> scene::start_time = std::chrono::system_clock::now();

scene::scene(int w, int h) 
{
    _cam = camera::make(35,static_cast<float>(w)/static_cast<float>(h),0.1,300);
} 

void scene::add(object::cref obj)   
{
    INFO("add object to scene");
    render_list.push_back(obj);
}

void scene::render()
{   
    auto cur_time = time();
    auto eye = _cam->pos();
    for(const auto & obj : render_list)
    {
        if(!obj->_enabled) return;
        auto mat = obj->_material;
        glUseProgram(mat->getID());
        glUniformMatrix4fv(mat->uni().prj,   1,GL_FALSE, _cam->prj().data);
        glUniformMatrix4fv(mat->uni().iview, 1,GL_FALSE, _cam->view().data);
        glUniform3f(mat->uni().eye,eye.x,eye.y,eye.z);
        
        glUniform1f(mat->uni().time, cur_time);
        obj->render();
    }   
}

float scene::time() 
{
    auto cur = std::chrono::system_clock::now();
    std::chrono::duration<float> dt(cur - start_time);
    return dt.count();
}