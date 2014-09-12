#include "common.h"

object::object(mesh::cref _mesh, material::cref _mat):
    _mesh(_mesh),
    _material(_mat)
{}

 object::~object()
 {} 
