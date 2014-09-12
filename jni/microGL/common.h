#ifndef __GRASSHOPPER_COMMON__
#define __GRASSHOPPER_COMMON__

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <chrono>


#include <android/log.h>
#include <android/asset_manager.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "minimath.h"

using strref = const std::string &;

#define TAG "[GRASSHOPPER]"
#define INFO(...)  __android_log_print(ANDROID_LOG_WARN,TAG,__VA_ARGS__)
#define ERROR(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define FATAL(...)  {ERROR(__VA_ARGS__); std::abort();}

template <typename T>
struct Iref 
{
public: 
    using ref  = std::shared_ptr<T>;
    using cref = const ref &;

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

struct material : public Iref<material>
{
    material(strref);
    virtual ~material();

    attr_t attributes;                   
    unif_t uniforms;
};

class mesh : public Iref<mesh>
{
public:
    mesh(strref);
    mesh(const std::vector<vertex> &);
    virtual ~mesh();
    
    void render(material::cref);

private:
    std::vector<vertex>   vertexes;
    int indicies {};
};

class image : public Iref<image>
{
public:
    image(strref);
   ~image();

private:    
    std::vector<uint8_t> _data;
    int _bpp;    
    int _width;   
    int _height;
};

class object : public Iref<object>
{
    friend class scene; // nb: only hackaton style - no time for getters/setters :)
public: 
    object(mesh::cref, material::cref);
   ~object();   

   void render(material::cref);
   void set_texture(int, image::cref);
private:
    bool          _enabled = true;
    mat4          _transform;
    mesh::ref     _mesh;
    material::ref _material;
    image::ref    _texture[4];
};

class scene
{
public:
    scene(float,float,float,float);
    void add(object::cref);
    void translate(vec3::cref);
    void rotate(vec3::cref);
    void render();

    static float time(); 

private:
    mat4 prj_m;     
    mat4 iview_m;    
    std::vector<object::ref> render_list;
    static std::chrono::time_point<std::chrono::system_clock> start_time;
};

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

#endif



