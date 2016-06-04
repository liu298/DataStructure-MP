#ifndef image_h
#define image_h

#include <stdio.h>
#include "png.h"

class Image : public PNG
{
public:
    void 	flipleft ();

	void 	adjustbrightness (int r, int g, int b);

	void 	invertcolors ();

};

#endif /* image_h */
