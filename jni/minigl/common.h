#ifndef __GRASSHOPPER_COMMON__
#define __GRASSHOPPER_COMMON__

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>


#include <android/log.h>
#include <android/asset_manager.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "minimath.h"

using strref = const std::string &;

#define TAG "[GRASSHOPPER]"
#define D_LOG(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define E_LOG(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define FATAL(...)  {E_LOG(__VA_ARGS__); std::abort();}

struct stream
{
public:
    stream(strref);
   ~stream();

    void open(strref);
    void close();
    void read(char *, size_t);
    void seek(long pos);
    size_t size() const;
    std::string str();

static void init(AAssetManager *);

private:
    static AAssetManager * _am;
    AAsset * _file;
    size_t   _size {};
};

struct Ibindable
{
    int getID() const {return _id;}
protected:
    GLuint _id;
};

struct vertex
{
    vec3 position;  
    vec3 uv;  
    vec3 tangent;  
    vec3 binormal;
    vec3 normal; 
    vertex(vec3::cref p, vec3::cref u,vec3::cref t,vec3::cref b,vec3::cref n):
        position(p),
        uv(u),
        tangent(t),
        binormal(b),
        normal(n)
    {}    

};


class material : public Ibindable
{
    friend class scene;
public:
    using ref  = std::shared_ptr<material>;
    using cref = const ref &;

    material(strref);
    virtual ~material();
private:    
                
};

class mesh : public Ibindable
{
    friend class scene;
public:
    using ref  = std::shared_ptr<mesh>;
    using cref = const ref &;

    mesh(strref);
    mesh(const std::vector<vertex> &);
    virtual ~mesh();

private:
    std::vector<vertex>   vertexes;
};

class image : public Ibindable
{
    friend class scene;
public:
    using ref  = std::shared_ptr<image>;
    using cref = const ref &;

    image(strref);
   ~image();

private:    
    std::vector<uint8_t> _data;
    int _bpp;    
    int _width;   
    int _height;
};

class object
{
    friend class scene;
public: 
    using ref  = std::shared_ptr<object>;
    using cref = const ref &;

    object(mesh::cref, material::cref);
   ~object();   

   void render() {};

private:
    bool          _enabled = true;
    mat4          _transform;
    mesh::ref     _mesh;
    material::ref _material;
    image::ref    _texture0;
    image::ref    _texture1;
};

class scene
{
public:
    scene(float,float,float,float);
    void add(object::cref);
    void translate(vec3::cref);
    void render();

private:
    mat4 prj_m;     
    mat4 iview_m;    
    std::vector<object::ref> render_list;
};




#endif



