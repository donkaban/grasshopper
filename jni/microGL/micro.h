#ifndef __GRASSHOPPER_MICROGL_API__
#define __GRASSHOPPER_MICROGL_API__

#include <memory>
#include <vector>
#include <unordered_map>
#include <chrono>

#include "minimath.h"
#include "detail.h"
#include "logger.h"

using strref = const std::string &;

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

class material : public 
    Iref<material,strref>
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

class mesh : public 
    Iref<mesh,const std::vector<gl::vertex> &,const std::vector<uint16_t> &,GLenum>
{
public:
    mesh(const std::vector<gl::vertex> &, const std::vector<uint16_t> &, GLenum draw=GL_TRIANGLES);
    virtual ~mesh();
    void render(material::cref);

    static ptr make_plane(float, float);
    static ptr make_cube (float, float, float);
 
private:
    std::vector<gl::vertex>  vertexes;
    std::vector<uint16_t>    indicies;
    GLenum                   draw_by;
};

struct image : public Iref<image, strref>
{
    image(strref);
    virtual ~image();

    std::vector<uint8_t> _data;
    int _bpp;    
    int _width;   
    int _height;
};

class object : public 
    Iref<object, mesh::cref, material::cref>
{
    friend class scene; // fixit: ugly hackaton style - no getters/setters :)
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

class camera : public 
    Iref<camera, float,float,float,float>
{
public:
    camera(float,float,float,float);
    void translate(math::vec3::cref);
    void rot_x(float);
    void rot_y(float);
    void rot_z(float);
    inline math::mat4::cref prj()  const {return _prj_m;}
    inline math::mat4::cref view() const {return _view_m;}
    inline math::vec3       pos()  const {return _transform.pos();}

private:
    math::mat4 _transform;  
    math::mat4 _prj_m;     
    math::mat4 _view_m;    
};  

class scene : public 
    Iref<scene, int, int>
{
public:
    scene(int, int);
    void add(object::cref);
    void render();
    inline camera::cref cam() const {return _cam;}

    static float time(); 
private:
    camera::ptr _cam;
    std::vector<object::ptr> render_list;
    static std::chrono::time_point<std::chrono::system_clock> start_time;
};

class app : public 
    Iref<app>  
{
public:
    virtual void onInit()              {};
    virtual void onUpdate(float)       {};
    virtual void onExit()              {};
    virtual void onTouch(uint,uint)    {};
    virtual void onMove(int, int)      {};
    virtual void onRelease(uint,uint)  {};

    inline scene::ptr & get_scene()       {return _scene;}
    inline void set_scene(scene::cref &s) {_scene = s;}
    
private:
    scene::ptr _scene;
};

extern app::ptr __APP_INSTANCE();  
#define RUN_APP(name) app::ptr __APP_INSTANCE() {return std::shared_ptr<app>(new name());}  


#endif



