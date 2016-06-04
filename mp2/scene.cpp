#include "scene.h"
#include "image.h"
#include "png.h"
#include "rgbapixel.h"

#include<iostream>
using namespace std;

Scene::Scene (int max_arg)
{
	max = max_arg;
	_image = new Image*[max];
    for(int i=0;i<max;i++)
    {
        _image[i] = NULL;
    }

	_x = new int[max];
	_y = new int[max];

}

Scene::~Scene ()
{
	clear();


}

Scene::Scene (const Scene &source)
{
	copy(source);
}

const Scene & Scene::operator=(const Scene & 	source)
{
	if (this != &source)
	{
		clear();
		copy(source);
	}

	return *this;
}
// note: *this = a; return the reference?
void Scene::copy(Scene const & other)
{
	max = other.max;
	//_image = new Image*[max];
	_image = new Image*[max];
	for(int i=0;i<max;i++)
		_image[i] = NULL;
	_x = new int[max];
	_y = new int[max];
	for (int i = 0;i < max;i++)
	{
	if(other._image[i]!=NULL)
		_image[i] = new Image(*other._image[i]);
		_x[i] = other._x[i];
		_y[i] = other._y[i];

	}

}

void Scene::changemaxlayers	(int newmax)
{
	if (newmax == max)
		return;
	else if (newmax < max)
		{
		    cout << "invalid newmax" << endl;
			return;
		}

	else
	{
	    Image **new_image;
        int * new_x;
        int * new_y;
        // new_image = new Image*[newmax];
        new_image = new Image*[newmax];
        for(int i=0;i<newmax;i++)
			new_image[i] = NULL;
		new_x = new int[newmax];
		new_y = new int[newmax];

		for (int i=0;i<newmax;i++)
		{
			if(_image[i] != nullptr)
			{
				new_image[i] = new Image(*_image[i]);
				new_x[i] = _x[i];
				new_y[i] = _y[i];

			}

		}
		for(int i=0;i<max;i++)
		{
			delete _image[i];
			_image[i] = NULL;
	    }
		delete []_image;
		delete []_x;
		delete []_y;
		_image = new_image;
		_x = new_x;
		_y = new_y;

		//overwrite max
		max = newmax;
		return;
	}
}

void Scene::addpicture (const char *FileName, int index, int x, int y)
{
	if(index < 0 || index > max-1)
	{
		cout << "index out of bounds" << endl;
		return;
	}
	else
	{
		Image * add_file = new Image;
        add_file->readFromFile(FileName);
		_image[index] = add_file;
		_x[index] = x;
		_y[index] = y;
	}
}

void Scene::changelayer	(int index, int newindex)
{
	if (index == newindex)
		return;
	else if((index < 0) || (index > max-1) || (newindex < 0) || (newindex > max-1))
	{
		cout << "invalid index" << endl;
		return;
	}

	else
	{
       	_x[newindex] = _x[index];
		_y[newindex] = _y[index];
		_image[newindex] = _image[index];

		_image[index] = NULL;
		_x[index] = 0;
		_y[index] = 0;

	}
}

void Scene::translate (int index, int xcoord, int ycoord)
{
	if((index < 0)|| (index > max-1))
	{
		cout << "invalid index" << endl;
		return;
	}
	else
	{
		_x[index] = xcoord;
		_y[index] = ycoord;
		return;
	}

}

void Scene::deletepicture (int index)
{
	if((index < 0)|| (index > max-1))
	{
		cout << "invalid index" << endl;
		return;
	}
	else
	{
		_image[index] = NULL;
		_x[index] = 0;
		_y[index] = 0;
		return;
	}
}

Image * Scene::getpicture (int index) const
{
	if((index < 0)|| (index > max-1) )
	{
		cout << "invalid index" << endl;
		return NULL;
	}
	else
		return _image[index];
}

Image Scene::drawscene ()
{
    size_t _width = 0;
	size_t _height = 0;

	for(int i = 0;i < max;i++)
	{
		if(_image[i] != NULL)
		{
/*
cout << "i = " << i << endl;
cout << "_x[i] = "<< _x[i]<<endl;
cout << "_y[i] = "<< _y[i]<<endl;
cout << "_image[i]->width() = " <<_image[i]->width()<<endl;
*/
			if ((_x[i] + _image[i]->width()) > _width)
				_width = (_x[i] + _image[i]->width() );

			if ((_y[i] + _image[i]->height()) > _height)
				_height = (_y[i] + _image[i]->height());
		}
	}

    Image _scene;
	_scene.resize(_width, _height);
	for (int n=0; n < max; n++)
	{ 
//cout << "_image[n]->width() = " <<_image[n]->width()<<endl;
		if (_image[n] != NULL)
		{
			for (size_t i=0; i < _image[n]->width(); i++)
			{
				for (size_t j=0; j < _image[n]->height(); j++)
				{
					_scene((i+_x[n]), (j+_y[n]))->red =(*_image[n])(i,j) -> red;
					_scene((i+_x[n]), (j+_y[n]))->green =(*_image[n])(i,j) -> green;
					_scene((i+_x[n]), (j+_y[n]))->blue =(*_image[n])(i,j) -> blue;
				}
			}
		}
		
	}

	return _scene;

}

void Scene::clear()
{
	for(int i=0;i<max;i++)
	{
		delete _image[i];
		_image[i] = NULL;
	}
		
	delete []_image;
	delete []_x;
	delete []_y;

	_image = NULL;
	_x = NULL;
	_y = NULL;
}


