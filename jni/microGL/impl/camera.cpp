#include "micro.h"
_MODULE("CAMERA");

using namespace math;

camera::camera(float f,float a, float zn, float zf) :
	_transform(math::mat4::identity),
    _prj_m(mat4::perspective(f, a, zn, zf)),
    _view_m(_transform.inverse())
{
    INFO("create camera : fov:", f, ", near: ",zn,", far: ",zf);
} 

void camera::translate(vec3::cref v) {_transform *= mat4::translate(v);	_view_m = _transform.inverse();}
void camera::rot_x(float a)          {_transform *= mat4::rot_x(a);		_view_m = _transform.inverse();}
void camera::rot_y(float a)          {_transform *= mat4::rot_y(a);		_view_m = _transform.inverse();}
void camera::rot_z(float a)          {_transform *= mat4::rot_z(a);		_view_m = _transform.inverse();}
