/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include <math.h>
/**
    * Deletes the current contents of this Quadtree object, 
    * then turns it into a Quadtree object representing the 
    * upper-left d by d block of source.
    **/
#include 'quadtree.h'

void Quadtree::buildTree(PNG const & source, int resolution)
{
	clear(root);
	//Quadtree tree;
	int h=0;
	embedPNG(source,root,h,resolution/2-1,resolution/2-1);

}

void Quadtree::embedPNG(PNG const & source, QuadtreeNode * subRoot,int &h, 
								size_t x_cor, size_t y_cor, int resolution)
{
	int height = log2 (resolution);
	size_t nodeWidth = resolution/pow(2,h);
	if(h==height) //base case
	{	
		subRoot->nwChild->element = *source(x_cor,y_cor);
		subRoot->neChild->element = *source(x_cor,y_cor);
		subRoot->swChild->element = *source(x_cor,y_cor);
		subRoot->seChild->element = *source(x_cor,y_cor);
	}

	subRoot = new QuadtreeNode();
	//do something
	embedPNG(source,subRoot->nwChild,h+1,x_cor-nodeWidth/4,y_cor-nodeWidth/4,resolution);
	embedPNG(source,subRoot->neChild,h+1,x_cor+nodeWidth/4,y_cor-nodeWidth/4,resolution);
	embedPNG(source,subRoot->swChild,h+1,x_cor-nodeWidth/4,y_cor+nodeWidth/4,resolution);
	embedPNG(source,subRoot->seChild,h+1,x_cor+nodeWidth/4,y_cor+nodeWidth/4,resolution);

	if(h<height)
	{
		subRoot->element.red = (subRoot->nwChild->element->red 
								+subRoot->neChild->element->red 
								+subRoot->swChild->element->red
								+subRoot->seChild->element->red)/4;
		subRoot->element.blue = (subRoot->nwChild->element->blue 
								+subRoot->neChild->element->blue 
								+subRoot->swChild->element->blue
								+subRoot->seChild->element->blue)/4;
		subRoot->element.green = (subRoot->nwChild->element->green 
								+subRoot->neChild->element->green 
								+subRoot->swChild->element->green
								+subRoot->seChild->element->green)/4;

	}


}

/*****************************
  * The big three
  ****************************/

// The no argument constructor 
Quadtree::Quadtree():root(NULL),resolution()
{ }

// The 	two arguments constructor 
Quadtree::Quadtree(PNG const & source, int resolution)
{
	resolution = resolution;
	int height=log2 (resolution);
	embedPNG(source,root,height,resolution/2-1,resolution/2-1);
}

//copy constructor
Quadtree::Quadtree(Quadtree const & other)
{
	if(other.root == NULL)
		return *this;
	root = copyNode(other.root);
	resolution = other.resolution;
}

//copyNode: helper function for copy constructor
Quadtree::QuadtreeNode * Quadtree::copyNode(QuadtreeNode * const &subRoot) const
{
	QuadtreeNode * node = new QuadtreeNode();
	node->element = subRoot->element;
	if(subRoot->nwChild != NULL)
	{
		node->nwChild = copyNode(subRoot->nwChild);
		node->neChild = copyNode(subRoot->neChild);
		node->swChild = copyNode(subRoot->swChild);
		node->seChild = copyNode(subRoot->seChild);
	}
	 return node;

}

//destructor
Quadtree::~Quadtree()
{
	clear(root);
	resolution = 0;
}

//clear: helper function for destructor
void Quadtree::clear(QuadtreeNode * &subRoot)
{
	if(subRoot->nwChild == NULL)
	{
		delete subRoot;
		subRoot = NULL;
	}
		
	clear(subRoot->nwChild);
	clear(subRoot->neChild);
	clear(subRoot->swChild);
	clear(subRoot->seChild);

}

//assignment operator=
Quadtree const & Quadtree::operator=(Quadtree const & other)
{
	if(this == &other);
	else
	{
		clear(root);
		root = copyNode(other.root);
		resolution = other.resolution;
	}
	return *this;

}	

RGBAPixel Quadtree::getPixel(size_t x, size_t y)	const
{
	RGBAPixel * ret;
	if(x>resolution || y>resolution ||root == NULL)
		return *ret;

	int h=0;
	return findPixel(root,x,y,resolution/2-1,resolution/2-1,h)->element;


}

Quadtree::QuadtreeNode * Quadtree::findPixel(QuadtreeNode * const &subRoot,
									size_t x,size_t y,size_t cur_x,size_t cur_y, int &h)
{
	if(x==cur_x && y==cur_y)
		return subRoot;
	//int height=log2 (resolution);
	size_t nodeWidth = resolution/pow(2,h);

	if(subRoot->nwChild == NULL && cur_x != x && cur_y != y)  // does not contain the specific node
		return subRoot;
	if((cur_x-nodeWidth/2)<=x<=cur_x)     //find the west children node
	{
		if((cur_y-nodeWidth/2)<=y<=cur_y)    //find nwChild
			findPixel(subRoot->nwChild,x,y,cur_x-nodeWidth/4,cur_y-nodeWidth/4,h+1);
		if(cur_y<y<=(cur_y+nodeWidth/2))    //find swChild
			findPixel(subRoot->swChild,x,y,cur_x-nodeWidth/4,cur_y+nodeWidth/4,h+1);
	}
	else if(cur_x<x<=(cur_x+nodeWidth/2))     //find the east nodes
	{
		if((cur_y-nodeWidth/2)<=y<=cur_y)    //find neChild
			findPixel(subRoot->neChild,x,y,cur_x+nodeWidth/4,cur_y-nodeWidth/4,h+1);
		if(cur_y<y<=(cur_y+nodeWidth/2))    //find seChild
			findPixel(subRoot->seChild,x,y,cur_x+nodeWidth/4,cur_y+nodeWidth/4,h+1);
	}
}


PNG Quadtree::decompress () const
{
	PNG ret;
	int h=0;
	if(root == NULL)
		return ret;
	ret.resize(resolution,resolution);
	decompressNode(ret,root,resolution/2-1,resolution/2-1,h);

}

void Quadtree::decompressNode(PNG &image, QuadtreeNode * const &subRoot,
								size_t x,size_t y, int &h)
{	
	int height = log2(resolution);
	size_t nodeWidth = resolution/pow(2,h);

	//reach the smallest leavenodes and they are original pixels
	if(subRoot->nwChild == NULL && h=height)   
		*image(x,y) = subRoot->element;

	//reach the smallest leavenodes and they have been pruned
	if (subRoot->nwChild == NULL && h<height)  //
	{
		for(size_t i=0;i<nodeWidth;i++)
		{
			for(size_t j=0;j<nodeWidth;j++)
				*image(x-nodeWidth/2+i,y-nodeWidth/2+j) = subRoot->element;
		}
	}

	decompressNode(image,subRoot->nwChild,x-nodeWidth/4,y-nodeWidth/4,h+1);
	decompressNode(image,subRoot->neChild,x+nodeWidth/4,y-nodeWidth/4,h+1);
	decompressNode(image,subRoot->swChild,x-nodeWidth/4,y+nodeWidth/4,h+1);	
	decompressNode(image,subRoot->seChild,x+nodeWidth/4,y+nodeWidth/4,h+1);																									)

}


