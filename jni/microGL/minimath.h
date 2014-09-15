#ifndef __GRASSHOPPER_MATH__
#define __GRASSHOPPER_MATH__

// todo: strip it!

#include <cmath>
#include <cstring>
#include <initializer_list>

#define PI 3.141592654
#define DEG2RAD (PI/180.0)
#define RAD2DEG (180.0/PI)

namespace math {
  
struct vec3 
{
    using cref = const vec3 &;
public:
    static const int  size = 3;
    static const vec3 zero;
    union
    {
        struct {float x, y, z;};
        float data[3];
    };
       
    vec3(float _x = 0, float _y = 0 ,float _z = 0);

    vec3   operator+  (cref)  const ;
    vec3   operator-  (cref)  const ;
    vec3 & operator+= (cref)        ;
    vec3 & operator-= (cref)        ;
    vec3   operator*  (float) const ;
    vec3 & operator*= (float)       ;
    vec3   operator-  ()      const ;
    bool   operator== (cref)  const ;
    bool   operator!= (cref)  const ;

    bool  cmp(cref)   const ;
    float len()       const ;
    float dot(cref)   const ;
    vec3  cross(cref) const ;
    vec3  norm();
};

struct mat4
{
    using cref =  const mat4 &;
    static const mat4 identity;
     
    union
    {
        float   m[4][4];
        float   data[16];
    };
    mat4();
    mat4(const std::initializer_list<float> &);

    mat4   operator*  (cref) const;
    mat4 & operator*= (cref);
    mat4 inverse() const;
    void inv();
    void pos(vec3::cref);
    void rot(vec3::cref);
    vec3 pos() const ;
    vec3 rot() const;

    static mat4 rot_x(float);
    static mat4 rot_y(float);
    static mat4 rot_z(float);
    static mat4 scale(vec3::cref);    
    static mat4 translate(vec3::cref);
    static mat4 perspective(float ,float,float,float);
    static mat4 frustum(float, float, float, float, float, float);
   
};
}



#endif
