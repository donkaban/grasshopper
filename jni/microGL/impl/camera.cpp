#include "micro.h"
_MODULE("CAMERA");

using namespace math;

camera::camera(float f,float a, float zn, float zf) :
	_transform(math::mat4::identity * math::mat4::translate(math::vec3(0,0,-16)) * math::mat4::rot_x(DEG2RAD * -120)),
    _prj_m(mat4::perspective(f, a, zn, zf)),
    _view_m(_transform.inverse())
{
    INFO("create camera : fov:", f, ", near: ",zn,", far: ",zf);
} 
void camera::move(vec3::cref v)  
{
	auto p = pos() + v;
	_transform.pos(p);;
	_view_m = _transform.inverse();
}
void camera::rotate(float a) 
{
	_transform *= mat4::rot_y(a) ;		
	_view_m = _transform.inverse();
}

math::mat4::cref camera::prj()  const {return _prj_m;}
math::mat4::cref camera::view() const {return _view_m;}
math::vec3       camera::pos()  const {return _transform.pos();}