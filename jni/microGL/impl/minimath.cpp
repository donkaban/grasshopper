#include "minimath.h"

namespace math {

vec3::vec3(float _x, float _y ,float _z) : x(_x), y(_y),z(_z) {}

vec3   vec3::operator+  (cref a)  const {return vec3(x + a.x, y + a.y, z+ a.z);}
vec3   vec3::operator-  (cref a)  const {return vec3(x - a.x, y - a.y, z- a.z);}
vec3 & vec3::operator+= (cref a)        {x += a.x; y += a.y; z += a.z; return *this;}
vec3 & vec3::operator-= (cref a)        {x -= a.x; y -= a.y; z -= a.z; return *this;}
vec3   vec3::operator*  (float a) const {return vec3( x * a, y * a, z * a);}
vec3 & vec3::operator*= (float a)       {x *= a; y *= a; z *= a; return *this; }
vec3   vec3::operator-  ()        const {return vec3(-x,-y,-z);}
bool   vec3::operator== (cref a)  const {return cmp(a);}
bool   vec3::operator!= (cref a)  const {return !cmp(a);}

bool  vec3::cmp(cref a)   const {return ((x == a.x) && (y == a.y) && (z == a.z));}
float vec3::len()         const {return std::sqrt(x * x + y * y + z * z);}
float vec3::dot(cref a)   const {return x * a.x + y * a.y + z * a.z;}
vec3  vec3::cross(cref a) const {return vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);}
vec3  vec3::norm()
{
    auto ilen = 1.0/len();
    x *= ilen; y *= ilen; z *= ilen;
    return *this;
}

mat4::mat4() : mat4({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}) {}
mat4::mat4(const std::initializer_list<float> &l) {std::memcpy(data,l.begin(),sizeof(data));}   
    
mat4 mat4::operator* (cref a) const
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
mat4 & mat4::operator*= (cref a)
{
    *this = (*this) * a;
    return *this;
}

void mat4::pos(vec3::cref v) {m[0][3] = v.x; m[1][3] = v.y; m[2][3] = v.z;}
void mat4::rotate(vec3::cref v) {*this = (*this) * rot_x(v.x) * rot_y(v.y) * rot_z(v.z);}

vec3 mat4::pos()     const {return {m[0][3],m[1][3],m[2][3]};}
vec3 mat4::up()      const {return {m[0][1],m[1][1],m[2][1]};}
vec3 mat4::forward() const {return {-m[0][2],-m[1][2],-m[2][2]};}
vec3 mat4::right()   const {return {m[0][0],m[1][0],m[2][0]};}

mat4 mat4::rot_x(float a) {auto s=std::sin(a); auto c=std::cos(a); return mat4({1,0,0,0,0,c,-s,0,0,s,c,0,0,0,0,1});}
mat4 mat4::rot_y(float a) {auto s=std::sin(a); auto c=std::cos(a); return mat4({c,0,s,0,0,1,0,0,-s,0,c,0,0,0,0,1});}
mat4 mat4::rot_z(float a) {auto s=std::sin(a); auto c=std::cos(a); return mat4({c,-s,0,0,s,c,0,0,0,0,1,0,0,0,0,1});}
mat4 mat4::scale(vec3::cref v)     {return {v.x,0,0,0,0,v.y,0,0,0,0,v.z,0,0,0,0,1};}
mat4 mat4::translate(vec3::cref v) {return {1,0,0,v.x,0,1,0,v.y,0,0,1,v.z,0,0,0,1};}

mat4 mat4::perspective(float fov,float aspect,float n,float f) // fix: unsafe!
{
    float h = std::tan(fov * DEG2RAD * .5);
    float w = h * aspect;
    float dz = f-n;
    return mat4({1/w,0,0,0,0,1/h,0,0,0,0,-(f+n)/dz,-2*f*n/dz,0,0,-1,0});
}

mat4 mat4::frustum(float l, float r, float b, float t, float n, float f) //fix: unsafe!
{
    float dx = r - l;
    float dy = t - b;
    float dz = f - n;
    return mat4({2.0f*n/dx,0,(r+l)/dx,0,0,2.0f*n/dy,(t+b)/dy,0,0,0,-(f+n)/dz,-2.0f*f*n/dz,0,0,-1,0});
}

mat4 mat4::inverse() const
{
    mat4 tmp = *this;
    tmp.inv();
    return tmp;
}   

void mat4::inv() // wasted space and time :(
{
    double det, invDet;

    float det2_01_01 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    float det2_01_02 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
    float det2_01_03 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
    float det2_01_12 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    float det2_01_13 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
    float det2_01_23 = m[0][2] * m[1][3] - m[0][3] * m[1][2];

    float det3_201_012 = m[2][0] * det2_01_12 - m[2][1] * det2_01_02 + m[2][2] * det2_01_01;
    float det3_201_013 = m[2][0] * det2_01_13 - m[2][1] * det2_01_03 + m[2][3] * det2_01_01;
    float det3_201_023 = m[2][0] * det2_01_23 - m[2][2] * det2_01_03 + m[2][3] * det2_01_02;
    float det3_201_123 = m[2][1] * det2_01_23 - m[2][2] * det2_01_13 + m[2][3] * det2_01_12;
    det = ( - det3_201_123 * m[3][0] + det3_201_023 * m[3][1] - det3_201_013 * m[3][2] + det3_201_012 * m[3][3] );
    invDet = 1.0f / det;
    float det2_03_01 = m[0][0] * m[3][1] - m[0][1] * m[3][0];
    float det2_03_02 = m[0][0] * m[3][2] - m[0][2] * m[3][0];
    float det2_03_03 = m[0][0] * m[3][3] - m[0][3] * m[3][0];
    float det2_03_12 = m[0][1] * m[3][2] - m[0][2] * m[3][1];
    float det2_03_13 = m[0][1] * m[3][3] - m[0][3] * m[3][1];
    float det2_03_23 = m[0][2] * m[3][3] - m[0][3] * m[3][2];
    float det2_13_01 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
    float det2_13_02 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
    float det2_13_03 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
    float det2_13_12 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
    float det2_13_13 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
    float det2_13_23 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
    float det3_203_012 = m[2][0] * det2_03_12 - m[2][1] * det2_03_02 + m[2][2] * det2_03_01;
    float det3_203_013 = m[2][0] * det2_03_13 - m[2][1] * det2_03_03 + m[2][3] * det2_03_01;
    float det3_203_023 = m[2][0] * det2_03_23 - m[2][2] * det2_03_03 + m[2][3] * det2_03_02;
    float det3_203_123 = m[2][1] * det2_03_23 - m[2][2] * det2_03_13 + m[2][3] * det2_03_12;
    float det3_213_012 = m[2][0] * det2_13_12 - m[2][1] * det2_13_02 + m[2][2] * det2_13_01;
    float det3_213_013 = m[2][0] * det2_13_13 - m[2][1] * det2_13_03 + m[2][3] * det2_13_01;
    float det3_213_023 = m[2][0] * det2_13_23 - m[2][2] * det2_13_03 + m[2][3] * det2_13_02;
    float det3_213_123 = m[2][1] * det2_13_23 - m[2][2] * det2_13_13 + m[2][3] * det2_13_12;
    float det3_301_012 = m[3][0] * det2_01_12 - m[3][1] * det2_01_02 + m[3][2] * det2_01_01;
    float det3_301_013 = m[3][0] * det2_01_13 - m[3][1] * det2_01_03 + m[3][3] * det2_01_01;
    float det3_301_023 = m[3][0] * det2_01_23 - m[3][2] * det2_01_03 + m[3][3] * det2_01_02;
    float det3_301_123 = m[3][1] * det2_01_23 - m[3][2] * det2_01_13 + m[3][3] * det2_01_12;
    m[0][0] = - det3_213_123 * invDet;
    m[1][0] = + det3_213_023 * invDet;
    m[2][0] = - det3_213_013 * invDet;
    m[3][0] = + det3_213_012 * invDet;
    m[0][1] = + det3_203_123 * invDet;
    m[1][1] = - det3_203_023 * invDet;
    m[2][1] = + det3_203_013 * invDet;
    m[3][1] = - det3_203_012 * invDet;
    m[0][2] = + det3_301_123 * invDet;
    m[1][2] = - det3_301_023 * invDet;
    m[2][2] = + det3_301_013 * invDet;
    m[3][2] = - det3_301_012 * invDet;
    m[0][3] = - det3_201_123 * invDet;
    m[1][3] = + det3_201_023 * invDet;
    m[2][3] = - det3_201_013 * invDet;
    m[3][3] = + det3_201_012 * invDet;
}

const vec3 vec3::zero = vec3(0,0,0);
const mat4 mat4::identity = mat4({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1});

}