#ifndef Ray_h
#define Ray_h

#include "vect.h"


class Ray {
public:
    Vec3 origin;
    Vec3 direction;

	Ray(Vec3 ori, Vec3 dir) : origin(ori), direction(dir) {}
	
	Vec3 get_point(double t) const{
		return origin + direction * t;
	}
	/* // these accessors are very inefficient, making copies
    Vec3 get_origin() const {
        return origin;
    }
    
    Vec3 get_direction() const{
        return direction;
    }
	*/
};
#endif
