#ifndef __GRASSHOPPER_DETAIL_
#define __GRASSHOPPER_DETAIL_

#include <string>
#include <android/asset_manager.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "minimath.h"

using strref = const std::string &;

namespace gl {
struct vertex
{
    union
    {   
        struct
        {
            math::vec3 position;  
            math::vec3 uv;           // :)  
            math::vec3 normal;
        };
        float data[sizeof(math::vec3) * 3];
    };
    vertex(const std::initializer_list<float> &l) {std::memcpy(data,l.begin(),sizeof(data));} 
};

struct attr_t 
{   
    int p,u,n;                         
    void lookup(int);
}; 
struct unif_t 
{
    int model,iview,prj,time,eye;
    int t[4];  
    void lookup(int);
}; 
}

struct pixel
{
    uint8_t r;
    uint8_t g; 
    uint8_t b;
    uint8_t a;
};

struct stream // motivation : RIAA
{
public:
    stream(strref);
   ~stream();
    void   read(char *, size_t);
    void   seek(size_t pos);
    size_t size() const;
    std::string str();
    
    static void init(AAssetManager *);
private:
    AAsset * _file;
    size_t   _size {};
    static AAssetManager * _am;
};

#endif