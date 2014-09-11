#ifndef __GRASSHOPPER_MATH__
#define __GRASSHOPPER_MATH__

#include "common.h"

#define PI 3.141592654
#define DEG2RAD (PI/180.0)
#define RAD2DEG (180.0/PI)
  
struct vec3 
{
    using cref = const vec3 &;
public:
    union
    {
        struct {float x, y, z;};
        float data[3];
    };
       
    vec3(float _x = 0, float _y = 0 ,float _z = 0) : x(_x), y(_y),z(_z) {}
    
    vec3   operator+  (cref a)  const {return vec3(x + a.x, y + a.y, z+ a.z);}
    vec3   operator-  (cref a)  const {return vec3(x - a.x, y - a.y, z- a.z);}
    vec3 & operator+= (cref a)        {x += a.x; y += a.y; z += a.z; return *this;}
    vec3 & operator-= (cref a)        {x -= a.x; y -= a.y; z -= a.z; return *this;}
    vec3   operator*  (float a) const {return vec3( x * a, y * a, z * a);}
    vec3 & operator*= (float a)       {x *= a; y *= a; z *= a; return *this; }
    vec3   operator-  ()        const {return vec3(-x,-y,-z);}
    bool   operator== (cref a)  const {return cmp(a);}
    bool   operator!= (cref a)  const {return !cmp(a);}
    
    bool  cmp(cref a)   const {return ((x == a.x) && (y == a.y) && (z == a.z));}
    float len()  	    const {return std::sqrt(x * x + y * y + z * z);}
    float dot(cref a)   const {return x * a.x + y * a.y + z * a.z;}
    vec3  cross(cref a) const {return vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);}
	vec3  norm()
    {
    	auto ilen = 1.0/len();
        x *= ilen; y *= ilen; z *= ilen;
        return *this;
    }
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

    mat4() : mat4({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}) {}
    mat4(std::initializer_list<float> l) {std::memcpy(data,l.begin(),sizeof(data));}   
    
    mat4 operator* (cref a) const
    {
        mat4  dst;
        const float *m1  = reinterpret_cast<const float *>(this);
        const float *m2  = reinterpret_cast<const float *>(&a);
        float *ptr = reinterpret_cast<float *>(&dst);
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                *ptr = m1[0]*m2[j]+m1[1]*m2[j+4]+m1[2]*m2[j+8]+m1[3]*m2[j+12];
                ptr++;
            }
            m1 += 4;
        }
        return dst;
    }
    mat4 & operator*= (cref a)
    {
        *this = (*this) * a;
        return *this;
    }
   
    void pos(vec3::cref v) {m[0][3] = v.x; m[1][3] = v.y; m[2][3] = v.z;}
    void rot(vec3::cref v) {*this = (*this) * rot_x(v.x) * rot_y(v.y) * rot_z(v.z);}
    
    vec3 pos() const {return {m[0][3],m[1][3],m[2][3]};}
	vec3 rot() const {return {m[0][3],m[1][3],m[2][3]};}

    static mat4 rot_x(float a) {auto s=std::sin(a); auto c=std::cos(a); return mat4({1,0,0,0,0,c,-s,0,0,s,c,0,0,0,0,1});}
    static mat4 rot_y(float a) {auto s=std::sin(a); auto c=std::cos(a); return mat4({c,0,s,0,0,1,0,0,-s,0,c,0,0,0,0,1});}
    static mat4 rot_z(float a) {auto s=std::sin(a); auto c=std::cos(a); return mat4({c,-s,0,0,s,c,0,0,0,0,1,0,0,0,0,1});}
    static mat4 scale(vec3::cref v)     {return {v.x,0,0,0,0,v.y,0,0,0,0,v.z,0,0,0,0,1};}
    static mat4 translate(vec3::cref v) {return {1,0,0,v.x,0,1,0,v.y,0,0,1,v.z,0,0,0,1};}
 	static mat4 perspective(float fov,float aspect,float n,float f)
    {
        float h = std::tan(fov * DEG2RAD * .5);
        float w = h * aspect;
        float dz = f-n;
        if((n <= 0.0f) || (f <= 0.0f) || (dz <= 0.0f))
            FATAL("perspective creation with bad parameters");
        return mat4({1/w,0,0,0,0,1/h,0,0,0,0,-(f+n)/dz,-2*f*n/dz,0,0,-1,0});
    }
	static mat4 frustum(float l, float r, float b, float t, float n, float f)
    {
        float dx = r - l;
        float dy = t - b;
        float dz = f - n;
        if((n <= 0.0f) || (f <= 0.0f) || (dx <= 0.0f) || (dx <= 0.0f) || (dx <= 0.0f))
            FATAL("frustum creation with bad parameters");
        return mat4({2.0f*n/dx,0,(r+l)/dx,0,0,2.0f*n/dy,(t+b)/dy,0,0,0,-(f+n)/dz,-2.0f*f*n/dz,0,0,-1,0});
    }
};



#endif
