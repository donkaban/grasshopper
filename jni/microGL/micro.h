#ifndef __GRASSHOPPER_MICROGL_API__
#define __GRASSHOPPER_MICROGL_API__

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
#include "detail.h"

using strref = const std::string &;

#define TAG "[GRASSHOPPER]"
#define INFO(...)  __android_log_print(ANDROID_LOG_WARN,TAG,__VA_ARGS__)
#define ERROR(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define FATAL(...) {ERROR(__VA_ARGS__); std::abort();}

template <typename T, typename ...A>
struct Iref 
{
public: 
    using ptr  = std::shared_ptr<T>;
    using cref = const ptr &;

    GLint   getID()   const {return _id;}
    bool    checkID() const {return _id!=-1;}

    static std::shared_ptr<T> make(A && ... args) {return std::make_shared<T>(args...);}
protected:
    GLuint _id  = -1;
};


class material : public Iref<material,strref>
{
public:
    material(strref);
    virtual ~material();
    inline const gl::attr_t & atr() const {return attributes;};
    inline const gl::unif_t & uni() const {return uniforms;}
private:
    gl::attr_t attributes;                   
    gl::unif_t uniforms;
};

class mesh : public Iref<mesh,const std::initializer_list<gl::vertex> &,const std::initializer_list<uint16_t> &,GLenum>
{
public:
    mesh(const std::initializer_list<gl::vertex> &, const std::initializer_list<uint16_t> &, GLenum draw=GL_TRIANGLES);
    virtual ~mesh();
    void render(material::cref);

    static ptr make_plane(float, float);
    static ptr make_cube (float, float, float);
 
private:
    std::vector<gl::vertex>  vertexes;
    std::vector<uint16_t>    indicies;
    GLenum                   draw_by;
};

class image : public Iref<image, strref>
{
public:
    image(strref);
    virtual ~image();
private:    
    std::vector<uint8_t> _data;
    int _bpp;    
    int _width;   
    int _height;
};

class object : public Iref<object, mesh::cref, material::cref>
{
    friend class scene; // nb: ugly hackaton style - no time for getters/setters :)
public: 
    object(mesh::cref, material::cref);
   ~object();   
    void render();

    void set_texture(int, image::cref);
    void translate(math::vec3::cref);
    void rotate(math::vec3::cref);
private:
    bool          _enabled = true;
    math::mat4    _transform;
    mesh::ptr     _mesh;
    material::ptr _material;
    image::ptr    _texture[4];
};

class scene : public Iref<scene, float,float,float,float>
{
public:
    scene(float,float,float,float);
    void add(object::cref);
    void translate(math::vec3::cref);
    void rotate(math::vec3::cref);
    void render();
    void wire(bool);   

    static float time(); 
private:
    math::mat4 prj_m;     
    math::mat4 iview_m;    
    std::vector<object::ptr> render_list;
    static std::chrono::time_point<std::chrono::system_clock> start_time;
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

class app : public Iref<app>  
{
public:
    virtual void onInit()        {};
    virtual void onUpdate(float) {};
    virtual void onExit()        {};
    inline scene::ptr & get_scene()       {return _scene;}
    inline void set_scene(scene::cref &s) {_scene = s;}
    
private:
    scene::ptr _scene;
};

extern app::ptr __APP_INSTANCE();  
#define RUN_APP(name) app::ptr __APP_INSTANCE() {return std::shared_ptr<app>(new name());}  


#endif



