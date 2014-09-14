#ifndef __GRASSHOPPER_TERRAIN__
#define __GRASSHOPPER_TERRAIN__

#include "micro.h"


class terrain : public Iref<terrain>
{
public:	
	terrain();
	

	static mesh::ptr make_tile(float, uint16_t, float, image::cref);
private:






};



#endif

