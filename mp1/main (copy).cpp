#include <iostream>
#include <png.h>
#include "png.h"
#include "rgbapixel.h"

using namespace std;
int main(){
    //input png a and obtian the dimensions
    PNG a;
    a.readFromFile("./in.png");
    size_t a_width = a.width();
    size_t a_height = a.height();
    
    //create png b with the same dimensions
//    PNG b;
//   b.readFromFile("in.png"); 
    
    //rotate png a, give the pixel to png b
    
    for (size_t i = 0; i  < a_width; i++)
    {
        for (size_t j = 0; j < a_height; j++)
        {       
        	 RGBAPixel * tmp = a(i,j);
		*a(i,j) = *a(a_width-1-i, a_height-1-j);
		*a(a_width-1-i,a_height-1-j) = *tmp;
	
	//	*a.operator()(i,j) = *a.operator()(a_width-1-i, a_height-1-j);        
        }     
    }
   
 a.writeToFile("./out.png");
     
}
 
