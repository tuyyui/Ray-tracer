#include "vect.h"

 

class Sphere {
    Vec3 Center;
    float Radius;
public:
    Sphere(Vec3 center, float radius) {
        Center = center;
        Radius = radius;
    }
    bool intersect(Vec3 &rayorig, Vec3 &raydir, float &t0, float &t1) {
     
    }
};
