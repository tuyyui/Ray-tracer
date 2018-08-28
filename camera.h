#include "vect.h"


class Camera {
    Vec3 origin;
    Vec3 direction;

public:
    Camera(Vec3 ori, Vec3 dir) {
        origin = ori;
        direction = dir;
    }
    Vec3 get_origin() {
        return origin;
    }
};
