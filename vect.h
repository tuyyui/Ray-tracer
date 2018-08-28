#include <cmath>


using namespace std;

class Vec3 {
    float X;
    float Y;
    float Z;
public:
    Vec3(float x, float y, float z) {
        X = x;
        Y = y;
        Z = z;
    }
    Vec3 operator +(Vec3 vec) {
        return Vec3(X+vec.X,Y+vec.Y,Z+vec.Z);
    }
    Vec3 operator -(Vec3 vec) {
        return Vec3(X-vec.X,Y-vec.Y,Z-vec.Z);
    }
    Vec3 operator *(Vec3 vec) {
        return Vec3(0,0,0);
    }
    Vec3 operator *(float scalar) {
        return Vec3(scalar*X,scalar*Y,scalar*Z);
    }
    float dot(Vec3 vec) {
        return X*vec.X+Y*vec.Y+Z*vec.Z;
    }
    float norm() {
        return sqrt(dot(*this));
    }
    Vec3 normalize() {
        return (*this)*(1/norm());
    }
    
};