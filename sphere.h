#ifndef Sphere_h
#define Sphere_h

#include "vect.h"
#include "ray.h"
#include <cmath>

 

class Sphere {
    Vec3 Center;
    float Radius;
public:
    Vec3 Color;
    Sphere(Vec3 center, float radius, Vec3 color) : Center(center), Radius(radius), Color(color) {}
    
    Vec3 get_center() {
        return Center;
    }

    Vec3 get_normal(Vec3 p) {
        return (p - Center) * (-1/Radius);
    }

    bool intersect(Ray& ray, float &t) {
        Vec3 o = ray.get_origin();
        Vec3 d = ray.get_direction();
        Vec3 oc = o - Center;

        const float b = 2 * oc.dot(d);
        const float c = oc.dot(oc) - Radius*Radius;
        double disc = b*b - 4 * c;

        if (disc < 1e-4)
            return false;

        disc = sqrt(disc);

        const float t0 = -b - disc;
        const float t1 = -b + disc;

        t = (t0 < t1) ? t0 : t1;

        return true;
    }
};
#endif
