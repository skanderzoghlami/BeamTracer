#include <iostream>
#include <fstream>
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
            image << int(255 * double(i)/height) << " " << int(255 * double(j)/width) << " " << int(255 * double(i*j)/(height*width)) << "\n";
    image.close();
}


int main(int, char**){
   makeImage();
   return 0;
}
