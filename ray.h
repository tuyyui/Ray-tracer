#include "vect.h"


class Ray {
    Vec3 origin;
    Vec3 direction;

    int R;
    int G;
    int B;
public:
    Camera(Vec3 ori, Vec3 dir) {
        origin = ori;
        direction = dir;
    }
};