#ifndef __GRASSHOPPER_ENGINE__
#define __GRASSHOPPER_ENGINE__

#include "common.h"
#include "minimath.h"
#include "auxgl.h"


struct Ibindable
{
	int getID() const {return _id;}
protected:
	int _id;
};

class material : public Ibindable
{
public:
	using ref  = std::shared_ptr<material>;
	using cref = const ref &;

	material(strref, strref);
	virtual ~material();
	
private:	
	
};

class mesh : public Ibindable
{
public:
	mesh();
	virtual ~mesh();


private:
	std::vector<vertex>   vertexes;
	std::vector<uint16_t> indicies;
};


class miniengine
{
public:


private:

};

#endif