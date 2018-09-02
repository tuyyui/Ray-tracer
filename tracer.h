#ifndef Tracer_h
#define Tracer_h

#include "sphere.h"
#include "vect.h"
#include "camera.h"
#include "ray.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Tracer {
   
    vector<Sphere> spheres;
    Sphere Light;
    Sphere Light2;
public:
    Tracer(Sphere light,Sphere light2) : Light(light), Light2(light2) {}
    void add(Sphere sphere) {
        spheres.push_back(sphere);
        
    }
    Vec3 trace(Camera* cam, int x, int y) {
        

        Vec3 black(255, 0, 255);
        Vec3 pix_col(0, 0, 0);
        
        Vec3 cam_origin = cam->get_origin();
        Vec3 cam_direction = cam->get_direction();
        
        float t;
        float kd = 0.0025;
        float ks = 0.3;

        pix_col = black;
                
        Vec3 ray_origin = cam_origin+Vec3(x - 250 ,y -250,0);
        Vec3 ray_direction = cam_direction;
                
        Ray ray(ray_origin, ray_direction);
        for(int i = 0; i < spheres.size(); i++) {
        if (spheres[i].intersect(ray, t)) {
                    
            Vec3 pi = ray_origin + ray_direction*t;
            Vec3 L = Light.get_center() - pi;
            Vec3 N = spheres[0].get_normal(pi);
                    
            double dt = max((float)0,L.normalize().dot(N.normalize()));
            
            
             Vec3 V = (cam_origin - pi).normalize();
             Vec3 R = (N*(2*dt) - L).normalize();
             double other = max((float)0,(float)pow(R.dot(V),10));
                        
            pix_col = Vec3(90,90,90)*0.01+spheres[i].Color * kd * Light.Color * dt + spheres[i].Color * ks * Light.Color * other;
             pi = ray_origin + ray_direction*t;
             L = Light2.get_center() - pi;
             N = spheres[0].get_normal(pi);
            
            dt = max((float)0,L.normalize().dot(N.normalize()));
            
            
             V = (cam_origin - pi).normalize();
             R = (N*(2*dt) - L).normalize();
            
            
             other = max((float)0,(float)pow(R.dot(V),10));
            
            pix_col = pix_col + spheres[i].Color * kd * Light2.Color * dt + spheres[i].Color * ks * Light2.Color * other;
        }
        }
        return pix_col;
    }

};
#endif
