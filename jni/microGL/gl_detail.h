#ifndef __GRASSHOPPER_GL_DETAIL_
#define __GRASSHOPPER_GL_DETAIL_

#include "minimath.h"

namespace gl {
struct vertex
{
    union
    {   
        struct
        {
            math::vec3 position;  
            math::vec3 uv;           // :)  
            math::vec3 tangent;  
            math::vec3 binormal;
            math::vec3 normal;
        };
        float data[15];
    };
    vertex(const std::initializer_list<float> &l) {std::memcpy(data,l.begin(),sizeof(data));} 
};

struct attr_t 
{   
    int p,u,t,b,n;                         
    void lookup(int);
}; 
struct unif_t 
{
    int model,iview,prj,time;
    int t[4];  
    void lookup(int);
}; 

}


#endif