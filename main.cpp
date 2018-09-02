#include "tracer.h"
#include "sphere.h"
#include "camera.h"
#include "vect.h"

#include <iostream>
#include <fstream>

using namespace std;

void clamp255(Vec3& col) {
    col.X = (col.X > 255) ? 255 : (col.X < 0) ? 0 : col.X;
    col.Y = (col.Y > 255) ? 255 : (col.Y < 0) ? 0 : col.Y;
    col.Z = (col.Z > 255) ? 255 : (col.Z < 0) ? 0 : col.Z;
}

int main() {
    
    int Height = 500;
    int Width = 500;
    
    Vec3 cam_ori(250, 250, -10);
    Vec3 cam_dir(0, 0, 1);
    
    
    Vec3 pix_col(0, 0, 0);
    
    Sphere light (Vec3(400, 100, 0), 1, Vec3(255,255,255));
    Sphere light2 (Vec3(0, 500, 50), 1, Vec3(255,255,255));
    
    Tracer mtracer = Tracer(light,light2);
    Camera mcam (cam_ori, cam_dir);
    
    Sphere sphere1 (Vec3(Width*0.5, Height*0.5, 50), 50, Vec3(255,40,40));
   // Sphere sphere2 (Vec3(Width*0.5, Height*0.2, 50), 50);
    
    mtracer.add(sphere1);
   // mtracer.add(sphere2);

    ofstream my_Image ("image.ppm");


    if (my_Image.is_open ()) {
        my_Image << "P3\n" << Width << " " << Height << " 255\n";
        for (int i = 0; i < Width; i++) {
            for (int j = 0; j < Height; j++)  {

            pix_col = mtracer.trace(&mcam, i, j);

            clamp255(pix_col);
             
            my_Image << (int)pix_col.X << ' ' << (int)pix_col.Y << ' ' << (int)pix_col.Z << "\n";
                cout << (int)pix_col.X << '\n';
            }
        }
        my_Image.close();
    }
    else
      cout << "Could not open the file";
    
    return 0;
    

}
