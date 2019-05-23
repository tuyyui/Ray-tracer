#ifndef Scene_h
#define Scene_h

#include "objects.h"
#include "color.h"
#include <iostream>

#include <vector>


using namespace std;

class Lightsource {
public:
	Vec3 position;
	Color_t color;
	double intensity = 100;
	Lightsource(Vec3 position_, Color_t color_ = Color_t(255,255,255)) : position(position_), color(color_) {}
};

class Scene {
   
    vector<Object*> objects;
	vector<Lightsource*> lightsources;
	//Camera camera;

public:
    Scene() {}

    void add(Object *object) {
		objects.push_back(object);
    }
	
	void add(Lightsource* object) {
		lightsources.push_back(object);
	}

    Color_t Shading(const Ray& ray, const Object& object, double t, int depth) {          
            Vec3 intersect_point = ray.origin + ray.direction * t;
            Vec3 normal = object.get_normal(intersect_point);
    
			switch (object.texture){ 
			case MAT:
				//cout << normal.dot(ray.direction) << "\n";
				return (object.color).scale_by(normal.dot(ray.direction) * 0.5);
			case REFLECTIVE:
			{
				Color_t c = (object.color).scale_by(normal.dot(ray.direction) * 0.5); 
				if (depth > 0)
					c = c+ trace_ray(Ray(intersect_point, (ray.direction - normal * ray.direction.dot(normal) * 2).normalize()), &object, depth -1);
				return c;
			}
			case SPECULAR:
			{
				Color_t c = Color_t(0, 0, 0);
				for (unsigned int i = 0; i < lightsources.size(); i++) {
					Vec3 light2pos = lightsources[i]->position - intersect_point;
					//specular:
					c = c + lightsources[i]->color.scale_by2(ray.reflect_by(normal).dot(light2pos.normalize())); // add check for occlusion
					//mat:
					c = c + (object.color).mix_with(lightsources[i]->color).scale_by(lightsources[i]->intensity/(lightsources[i]->position - intersect_point).norm2());
				}
				//reflections:
				if (depth > 0)
					c = c + trace_ray(Ray(intersect_point, (ray.direction - normal * ray.direction.dot(normal) * 2).normalize()), &object, depth - 1);
				return c;
				
			}
			default:
				throw exception("unrecognized texture");// UNRECOGNIZED_TEXTURE
			}
    }

	Color_t trace(int x, int y) {
// This function works as the camera, translating pixels to rays
		Vec3 ray_origin = Vec3(0, 0, -1000);
		Vec3 ray_direction = Vec3(x, y, 1250).normalize();

		return trace_ray(Ray(ray_origin, ray_direction), 0, 50);
	}
	Color_t trace_ray(const Ray& ray, const Object* exclude_obj, int depth) {
		double min_t = FLT_MAX;
		int min_i = -1;
		double t = FLT_MAX;
		for (unsigned int i = 0; i < objects.size(); i++) {
			//if (objects[i] != exclude_obj) {
				if ((*objects[i]).intersect(ray, t)) {
					if (min_t > t) {
						min_i = i;
						min_t = t;
					}
				}
			//}
		}
		if (min_i > -1) {
			return Shading(ray, *objects[min_i], min_t, depth);
		}
		return Color_t(0, 0, 0);
	}
};

#endif
