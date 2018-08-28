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

        Vec3 l = center - rayorig;
        float tca = l.dot(raydir);
        if(tca < 0) return false;
        float d2 = l.dot(l) - tca * tca;
        if(d2 > radius2) return false;
        float thc =sqrt(radius - d2);
        t0 = tca - thc;
        t1 = tca + thc;

        return true;
    }
};
