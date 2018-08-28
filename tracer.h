#include "sphere.h"
#include "vect.h"
#include "camera.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Tracer {
    vector<Sphere> spheres;
public:
    Tracer() {
    }
    void add(Sphere sphere) {
        spheres.push_back(sphere);
    }
    void trace(Camera* cam, Color* framebuffer, int Height, int Width) {
        for(int y = 0; y < Height; y++)  {
            for(int x = 0; x < Width; x++)  {
                    
                const Ray ray(Vec3(x,y,0),Vec3(0,0,1));
                if (sphere.intersect(ray, t)) {
                    
                    const Vec3 pi = ray.o + ray.d*t;  // intersection point of the ray with the sphere
                    const Vec3 L = light.c - pi;      // Light vector
                    const Vec3 N = sphere.getNormal(pi); // Normal of the sphere at the point of intersection
                    
                    const double dt = dot(L.normalize(), N.normalize()); // incidence angle measure
                    
                    //const Vec3 R = N*(2*dt) - L;
                    //const double other = pow(dot(R,V),alpha);
                        
                    pix_col = Vec3(0,0,100) + (red + white*dt) * 0.5; //(red + white*other) * 0.5;
                    clamp255(pix_col);
                    }
                framebuffer[j * imageWidth + i] = objects[k].color;

            }
        }
    }

};
