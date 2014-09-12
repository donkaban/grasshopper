#ifndef __GRASSHOPPER_MATH__
#define __GRASSHOPPER_MATH__

#include <cmath>
#include <cstring>
#include <initializer_list>

#define PI 3.141592654
#define DEG2RAD (PI/180.0)
#define RAD2DEG (180.0/PI)
  
struct vec3 
{
    using cref = const vec3 &;
public:
    static const int size = 3;
    union
    {
        struct {float x, y, z;};
        float data[3];
    };
       
    vec3(float _x = 0, float _y = 0 ,float _z = 0);

    vec3   operator+  (cref a)  const ;
    vec3   operator-  (cref a)  const ;
    vec3 & operator+= (cref a)        ;
    vec3 & operator-= (cref a)        ;
    vec3   operator*  (float a) const ;
    vec3 & operator*= (float a)       ;
    vec3   operator-  ()        const ;
    bool   operator== (cref a)  const ;
    bool   operator!= (cref a)  const ;

    bool  cmp(cref a)   const ;
    float len()  	    const ;
    float dot(cref a)   const ;
    vec3  cross(cref a) const ;
	vec3  norm();
    friend vec3 operator* (float a, cref b) {return vec3(b.x * a, b.y * a, b.z * a);}
};

struct mat4
{
    using cref =  const mat4 &;
    union
    {
        float   m[4][4];
        float   data[16];
    };
    mat4();
    mat4(const std::initializer_list<float> &);

    mat4   operator*  (cref) const;
    mat4 & operator*= (cref);
   
    void pos(vec3::cref);
    void rot(vec3::cref);
    vec3 pos() const ;
    vec3 rot() const;

    static mat4 rot_x(float);
    static mat4 rot_y(float);
    static mat4 rot_z(float);
    static mat4 scale(vec3::cref);    
    static mat4 translate(vec3::cref);
 	static mat4 perspective(float fov,float aspect,float n,float f);
	static mat4 frustum(float l, float r, float b, float t, float n, float f);
   
};



#endif
