#ifndef Objects_h
#define Objects_h

#include "color.h"
#include "vect.h"
#include "ray.h"
#include <cmath>
#include <vector>

enum Texture_t {MAT, REFLECTIVE, SPECULAR};
// abstract base class for objects in our scene
class Object {
public:
	Color_t color;
	Texture_t texture;
	Object(Color_t color_, Texture_t texture_= MAT) : color(color_), texture(texture_) {}
	virtual Vec3 get_normal(const Vec3& p) const = 0;
	virtual bool intersect(const Ray& ray, double& t) const = 0;
	const double SELF_AVOID_T = 1e-2;
};

class Sphere : public Object {
    Vec3 Center;
    double Radius;

public:
    Sphere(Vec3 center, double radius, Color_t color, Texture_t texture=MAT) : Center(center), Radius(radius), Object(color, texture) {}
    
    Vec3 get_center() const{
        return Center;
    }

    Vec3 get_normal(const Vec3& p) const {
		return ((p - Center)*(-1/Radius)).normalize();// *(-1 / Radius);
    }

    bool intersect(const Ray& ray, double &t) const {
        Vec3 v = ray.origin - Center;

        const double b = 2 * v.dot(ray.direction);
        const double c = v.dot(v) - Radius*Radius;
        double delta = b*b - 4 * c;

		if (delta < 0) { // was 1e-4, why?
			t = FLT_MAX; // no intersection, at 'infinity'
			return false;
		}

        const double t1 = (-b - sqrt(delta))/2;
        const double t2 = (-b + sqrt(delta))/2;

		if (t2 < SELF_AVOID_T) { // the sphere is behind us
			t = FLT_MAX; // no intersection, at 'infinity'
			return false;
		}

        //t = (t1 < t2) ? t1 : t2; // get the first intersection only
		t = (t1 >= SELF_AVOID_T) ? t1 : t2; // t1 is the first intersection, unless we're inside the sphere.
        
        return true;
    }
};


class Cylinder : public Object {
	Vec3 center;
	Vec3 direction;
	double radius;
	double height;

public:
	Cylinder(Vec3 center_, Vec3 direction_, double radius_, double height_, Color_t color, Texture_t texture = MAT) : center(center_), direction(direction_.normalize()), radius(radius_), height(height_), Object(color, texture) {}

	Vec3 get_center() const {
		return center;
	}
	// do we need this accessor?
	//Vec3 get_direction() const {
		//return direction;
	//}

	Vec3 get_normal(const Vec3& p) const {
		Vec3 to_center = p - center;
		return ((to_center - direction*(to_center.dot(direction))).normalize());
	}

	bool intersect(const Ray & ray, double& t) const {
		Vec3 rel_origin = ray.origin - center;

		const double directions_dot = ray.direction.dot(direction);
		const double a = 1 - directions_dot* directions_dot;
		const double b = 2 * (rel_origin.dot(ray.direction) - directions_dot *rel_origin.dot(direction));
		const double c = rel_origin.dot(rel_origin) -rel_origin.dot(direction)* rel_origin.dot(direction) - radius * radius;

		double delta = b * b - 4 * a * c;

		if (delta < 0) { // was 1e-4, why?
			t = FLT_MAX; // no intersection, at 'infinity'
			return false;
		}

		const double sqrt_delta_2a = sqrt(delta) / (2 * a);
		double t1 = (-b) / (2*a);
		const double t2 = t1 + sqrt_delta_2a;
		t1 -= sqrt_delta_2a;

		if (t2 < SELF_AVOID_T) { // the cylinder is behind us
			t = FLT_MAX; // no intersection, at 'infinity'
			return false;
		}
		double center_proj = center.dot(direction);
		double t1_proj = ray.get_point(t1).dot(direction);
		if (t1 >= SELF_AVOID_T && t1_proj > center_proj && t1_proj < center_proj+height) {
			t = t1;
			return true;
		}
		double t2_proj = ray.get_point(t2).dot(direction);
		if (t2 >= SELF_AVOID_T && t2_proj > center_proj && t2_proj < center_proj+height) {
			t = t2;
			return true;
		}
		t = FLT_MAX; // no intersection, at 'infinity'
		return false;
	}
};
#endif
