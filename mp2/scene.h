#ifndef scene_h
#define scene_h
#include "image.h"
#include "png.h"
#include "rgbapixel.h"
#include <ostream>
#include <stdio.h>

class Scene
{
	public:
	Scene (int max);
	~Scene ();
	Scene (const Scene &source);
	const Scene & operator= (const Scene &source);
	void changemaxlayers (int newmax);
	void addpicture (const char *FileName, int index, int x, int y);
	void changelayer (int index, int newindex);
	void translate (int index, int xcoord, int ycoord);
 	void deletepicture (int index);
	Image * getpicture (int index) const;
	Image drawscene ();

	private:
	int max;
	//how to discriminate whether a member function or a var is public or private?
	void clear();
 	void copy(Scene const & other);

 	Image ** _image;
 	int * _x;
 	int * _y;


};

#endif /* scene_h */
