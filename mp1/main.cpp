#include <iostream>
#include <png.h>
#include "png.h"
#include "rgbapixel.h"

using namespace std;
int main(int argc, const char * argv[]){

	if (argc < 3)
	{
		printf("Usage: mp1 in.png out.png\n");
		exit(1);
	}
    //input png a and obtian the dimensions
    PNG a;
    a.readFromFile(argv[1]);
    size_t a_width = a.width();
    size_t a_height = a.height();
    
    //create png b with the same dimensions
    PNG b;
    b.readFromFile(argv[1]); 
    
    //rotate png a, give the pixel to png b
    
    for (size_t i = 0; i  < a_width; i++)
    {
        for (size_t j = 0; j < a_height; j++)
        {       
         *b.operator()(i,j) = *a.operator()(a_width-1-i, a_height-1-j);        
        }     
    }
   
 b.writeToFile(argv[2]);
     
}
 
