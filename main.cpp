#include <iostream>
#include <fstream>
#include <vec3.h>
#include <color.h>
using namespace std;


void makeImage(){
    int height,width; 
    cout << "Give The Height and width of the image" << endl ;
    cin >>  height >> width  ;
    ofstream image ;
    image.open("image.ppm");
    image << "P3\n" << width << " " << height << "\n255\n";
    for(int i = 0 ; i< height ; ++i)
        for(int j=0 ; j< width ; ++j)
            {
                color p_color(double(i)/height, double(j)/width, double(i*j)/(height*width));
                write_color(image,p_color);
            }
    image.close();
}


int main(int, char**){
   makeImage();
   return 0;
}
