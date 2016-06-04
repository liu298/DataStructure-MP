#include "image.h"
#include "png.h"
#include "rgbapixel.h"
#include<iostream>

using namespace std;

    //public function flipleft
    void Image::flipleft ()
    {
        size_t image_width = width();
        size_t image_height = height();

        for(size_t i = 0;i < image_width / 2;i++)
        {
            for(size_t j = 0;j < image_height;j++)
            {
            RGBAPixel temp = (*(*this)(i,j));
            (*(*this)(i,j)) = (*(*this)(image_width-1-i, j));
           (*(*this)(image_width-1-i, j)) = temp;
            }
        }

    }

    //public function adjustbrightness
    void Image::adjustbrightness (int r, int g, int b)
    {
        size_t image_width = width();
        size_t image_height = height();

        for(size_t i = 0;i < image_width;i++)
        {
            for(size_t j = 0;j < image_height;j++)
            {
            if (((*this)(i,j)->red + r) < 0)
                ((*this)(i,j))->red = 0;
            else if (((*this)(i,j)->red + r) > 255)
                ((*this)(i,j))->red = 255;
            else
                ((*this)(i,j))->red =((*this)(i,j))->red + r;

            if (((*this)(i,j)->green + g) < 0)
                ((*this)(i,j))->green = 0;
            else if (((*this)(i,j)->green + g) > 255)
                ((*this)(i,j))->green = 255;
            else
                ((*this)(i,j))->green = ((*this)(i,j))->green + g;

            if (((*this)(i,j)->blue + b) < 0)
                ((*this)(i,j))->blue = 0;
            else if (((*this)(i,j)->blue + b) > 255)
                ((*this)(i,j))->blue = 255;
            else
                ((*this)(i,j))->blue = ((*this)(i,j))-> blue + b;

            }
        }

    }

    //public function invertcolors
    void Image::invertcolors ()
    {
        size_t image_width = width();
        size_t image_height = height();

        for(size_t i = 0;i < image_width;i++)
        {
            for(size_t j = 0;j < image_height;j++)
            {
             ((*this)(i,j))->red = (255 - ((*this)(i,j))->red);
             ((*this)(i,j))->green = (255 - ((*this)(i,j))->green);
             ((*this)(i,j))->blue = (255 - ((*this)(i,j))->blue);

            }
        }

    }
