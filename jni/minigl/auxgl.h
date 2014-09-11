#ifndef __GRASSHOPPER_AUXGL__
#define __GRASSHOPPER_AUXGL__

#include "common.h"
#include "minimath.h"

struct vertex
{
	vec3 position;  
	vec3 uv;  
	vec3 tangent;  
	vec3 binormal;
	vec3 normal;  
};

template <typename T>
struct uniform
{
public:
    uniform(strref name, const T& def) : 
    _name(name),
    _def(def) 
    {}    

    void set(const T &) const;
    const T & def() const {return _def;}
    bool find(int matID) 
    {
        _id = glGetUniformLocation(matID, _name.c_str());
        return (_id != -1);
    } 
private:
    std::string _name;
    int         _id;
    T           _def;
};
namespace GL
{
	void   COMPILE_CHECK(GLuint);
    void   LINK_CHECK(GLuint);
}



#endif
