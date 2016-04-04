/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include <math.h>
#include <algorithm> // std::max
#include <iostream>  // std::cout
/**
    * Deletes the current contents of this Quadtree object, 
    * then turns it into a Quadtree object representing the 
    * upper-left d by d block of source.
    **/
#include "quadtree.h"
using std::max;
using std::cout;
using std::endl;

void Quadtree::buildTree(PNG const & source, int resol)
{
	resolution = resol;
	clear(root);
	if(resolution == 0)
		return;
	int h=0;
	embedPNG(source,root,h,(double)(resolution-1)/2,(double)(resolution-1)/2,resolution);

}

void Quadtree::embedPNG(PNG const & source, QuadtreeNode * &subRoot,int h, 
								double x_cor, double y_cor, int resolution)
{
	if(h>log2(resolution))
		return;
	if(resolution == 0) 
		return;
	subRoot = new QuadtreeNode();
	int height = log2 (resolution);
	double nodeWidth = resolution/pow(2,h);
	
	if(h==height) //base case
	{	
		subRoot->element = *source(x_cor,y_cor);
		return;
	}	

	embedPNG(source,subRoot->nwChild,h+1,x_cor-nodeWidth/4,y_cor-nodeWidth/4,resolution);
	embedPNG(source,subRoot->neChild,h+1,x_cor+nodeWidth/4,y_cor-nodeWidth/4,resolution);
	embedPNG(source,subRoot->swChild,h+1,x_cor-nodeWidth/4,y_cor+nodeWidth/4,resolution);
	embedPNG(source,subRoot->seChild,h+1,x_cor+nodeWidth/4,y_cor+nodeWidth/4,resolution);
	
	if(h<height)
	{
		(subRoot->element).red = ((subRoot->nwChild->element).red + (subRoot->neChild->element).red + (subRoot->swChild->element).red + (subRoot->seChild->element).red)/4;
		(subRoot->element).blue = ((subRoot->nwChild->element).blue + (subRoot->neChild->element).blue + (subRoot->swChild->element).blue + (subRoot->seChild->element).blue)/4;
		(subRoot->element).green = ((subRoot->nwChild->element).green + (subRoot->neChild->element).green + (subRoot->swChild->element).green + (subRoot->seChild->element).green)/4;

	}

}

/*****************************
  * The big three
  ****************************/

// The no argument constructor 
Quadtree::Quadtree():root(NULL),resolution(0)
{ }

// The 	two arguments constructor 
Quadtree::Quadtree(PNG const & source, int resol)
{
	resolution = resol;
	int height=log2 (resolution);
	int h=0;
	embedPNG(source,root,h,(double)(resolution-1)/2,(double)(resolution-1)/2,resol);
}

//copy constructor
Quadtree::Quadtree(Quadtree const & other)
{
	root = NULL;
	if(other.root == NULL) 
		return;
	if(other.resolution == 0)
		return;
	root = copyNode(other.root);
	resolution = other.resolution;
}

//copyNode: helper function for copy constructor
Quadtree::QuadtreeNode * Quadtree::copyNode(QuadtreeNode * const &subRoot) const
{
	if(subRoot == NULL)
		return NULL;
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
	if(subRoot == NULL) return;
	clear(subRoot->nwChild);
	clear(subRoot->neChild);
	clear(subRoot->swChild);
	clear(subRoot->seChild);

	delete subRoot;
	subRoot = NULL;
}

//assignment operator=
Quadtree const & Quadtree::operator=(Quadtree const & other)
{
	if(this == &other) 
		return *this;
	clear(root);
	if(other.resolution == 0)
		return *this;
	if(other.root == NULL) 
		return *this;
	root = copyNode(other.root);
	resolution = other.resolution;
	return *this;
}	

RGBAPixel Quadtree::getPixel(int x, int y)	const
{
	RGBAPixel ret;
	if(x>int(resolution) || y>int(resolution) ||root == NULL)
		return ret;

	int h=0;
	return findPixel(root,x,y,(double)(resolution-1)/2,(double)(resolution-1)/2,h)->element;


}

Quadtree::QuadtreeNode * Quadtree::findPixel(QuadtreeNode * const &subRoot,
									int x,int y,double cur_x,double cur_y, int h) const
{
	if(subRoot == NULL) return subRoot;
	if(x==cur_x && y==cur_y)
		return subRoot;
	//int height=log2 (resolution);
	double nodeWidth = resolution/pow(2,h);

	if(subRoot->nwChild == NULL)  // does not contain the specific node
		return subRoot;
	if((double)(cur_x-nodeWidth/2) <= x && x <= cur_x)     //find the west children node
	{
		if((double)(cur_y-nodeWidth/2)<=y && y<=cur_y)    //find nwChild
			return findPixel(subRoot->nwChild,x,y,(double)cur_x-nodeWidth/4,(double)cur_y-nodeWidth/4,h+1);
		//if(cur_y<y<=(cur_y+nodeWidth/2))    //find swChild
		 else return findPixel(subRoot->swChild,x,y,(double)cur_x-nodeWidth/4,(double)cur_y+nodeWidth/4,h+1);
	}
	else //if(cur_x<x<=(cur_x+nodeWidth/2))     //find the east nodes
	{
		if((double)(cur_y-nodeWidth/2)<=y && y<=cur_y)    //find neChild
			return findPixel(subRoot->neChild,x,y,(double)cur_x+nodeWidth/4,(double)cur_y-nodeWidth/4,h+1);
		//if(cur_y<y<=(cur_y+nodeWidth/2))    //find seChild
		else return findPixel(subRoot->seChild,x,y,(double)cur_x+nodeWidth/4,(double)cur_y+nodeWidth/4,h+1);
	}
}


PNG Quadtree::decompress () const
{
/*	PNG ret;
	int h=0;
	if(root == NULL)
		return ret;
	ret.resize(resolution,resolution);
	decompressNode(ret,root,resolution/2-1,resolution/2-1,h);
	return ret;
*/
   	PNG new_image= PNG(resolution,resolution);
	for(int i=0;i<resolution;i++)
		for(int j=0;j<resolution;j++)
		{
			
		(new_image)(i,j)->red=getPixel(i,j).red;
		(new_image)(i,j)->green=getPixel(i,j).green;
		(new_image)(i,j)->blue=getPixel(i,j).blue;
		(new_image)(i,j)->alpha=getPixel(i,j).alpha;
		}
	return new_image;
}

// Using pointer manipulation, rotates the Quadtree object's underlying image clockwise by 90 degrees.
void Quadtree::clockwiseRotate()
{
	if(root == NULL) return;
	rotateNode(root);

}	

// The helper function of clockRotate
void Quadtree::rotateNode(QuadtreeNode * &subRoot)
{
	if(subRoot == NULL) return;

	QuadtreeNode * temp1 = subRoot->nwChild;
	QuadtreeNode * temp2 = subRoot->neChild;
	//QuadtreeNode * temp1 = subRoot->nwChild;

	subRoot->nwChild = subRoot->swChild;
	subRoot->neChild = temp1;
	subRoot->swChild = subRoot->seChild;
	subRoot->seChild = temp2;

	rotateNode(subRoot->nwChild);
	rotateNode(subRoot->neChild);
	rotateNode(subRoot->swChild);
	rotateNode(subRoot->seChild);
}

// Compresses the image this Quadtree represents.
void Quadtree::prune(int tolerance)
{
	if(root == NULL)
		return;
	pruneNode(root, tolerance);

}	

// The helper function of prune
void Quadtree::pruneNode(QuadtreeNode * &subRoot, int tolerance)
{
	if(subRoot == NULL) return;

	//bool prunable = checkPrunable(subRoot, subRoot->element,tolerance);
	bool prunable = checkPrunable(subRoot,subRoot->nwChild,tolerance) && checkPrunable(subRoot,subRoot->neChild,tolerance) && checkPrunable(subRoot,subRoot->swChild,tolerance) && checkPrunable(subRoot,subRoot->seChild,tolerance);
	if(prunable)
	{
		clear(subRoot->nwChild);
		clear(subRoot->neChild);
		clear(subRoot->swChild);
		clear(subRoot->seChild);
		return;
	}

	pruneNode(subRoot->nwChild, tolerance);
	pruneNode(subRoot->neChild, tolerance);
	pruneNode(subRoot->swChild, tolerance);
	pruneNode(subRoot->seChild, tolerance);
	


}

/*
bool Quadtree::checkPrunable(QuadtreeNode * &subRoot, RGBAPixel color, int tolerance)
{
	if(subRoot == NULL) return false;

	bool ret = false;

	if(ret == true) return ret;

	if(subRoot->nwChild == NULL)
	{
		int distance = pow(subRoot->element.red-color.red,2) + pow(subRoot->element.blue-color.blue,2) + pow(subRoot->element.green-color.green,2);
		if(distance <= tolerance) return true;
		else return false;
	}

	ret = ret && checkPrunable(subRoot->nwChild, color, tolerance);
	ret = ret && checkPrunable(subRoot->neChild, color, tolerance);
	ret = ret && checkPrunable(subRoot->swChild, color, tolerance);
	ret = ret && checkPrunable(subRoot->seChild, color, tolerance);

	return checkPrunable(subRoot->nwChild, color, tolerance) && checkPrunable(subRoot->neChild, color, tolerance) && checkPrunable(subRoot->swChild, color, tolerance) && checkPrunable(subRoot->seChild, color, tolerance);
}
*/

bool Quadtree::checkPrunable(QuadtreeNode * const &subRoot, QuadtreeNode * const &childLeave, int tolerance) const
{
	if(childLeave == NULL) return false;

	bool ret = false;

	if(ret == true) return ret;

 //without distance helper function
	if(childLeave->nwChild == NULL)
	{
		int distance = pow(subRoot->element.red-childLeave->element.red,2) + pow(subRoot->element.blue-childLeave->element.blue,2) + pow(subRoot->element.green-childLeave->element.green,2);
		if(distance <= tolerance) return true;
		else return false;
	}
/*
// with distance helper function
	if(childLeave->nwChild == NULL)
	{
		int distance = pow(subRoot->element.red-childLeave->element.red,2) + pow(subRoot->element.blue-childLeave->element.blue,2) + pow(subRoot->element.green-childLeave->element.green,2);
		if(distance <= tolerance) return true;
		else return false;
	}
*/
/*
	ret = ret && checkPrunable(subRoot, childLeave->nwChild, tolerance);
	ret = ret && checkPrunable(subRoot, childLeave->neChild, tolerance);
	ret = ret && checkPrunable(subRoot, childLeave->swChild, tolerance);
	ret = ret && checkPrunable(subRoot, childLeave->seChild, tolerance);
*/
	return checkPrunable(subRoot, childLeave->nwChild, tolerance) && checkPrunable(subRoot, childLeave->neChild, tolerance) && checkPrunable(subRoot, childLeave->swChild, tolerance) && checkPrunable(subRoot, childLeave->seChild, tolerance);
}

// Returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.
int Quadtree::pruneSize	(int tolerance)	const
{
	if(root == NULL) return 0;
	return (pow(resolution,2) - pruneCount(root, tolerance, 0));
}

int Quadtree::pruneCount(QuadtreeNode * const &subRoot, int tolerance, int h) const
{

	if(subRoot == NULL) return 0;
	bool prunable = checkPrunable(subRoot,subRoot->nwChild,tolerance) && checkPrunable(subRoot,subRoot->neChild,tolerance) && checkPrunable(subRoot,subRoot->swChild,tolerance) && checkPrunable(subRoot,subRoot->seChild,tolerance);
	if(prunable)
	{
		return pow(resolution, 2)/(pow(4,h))-1;
	}

	else return pruneCount(subRoot->nwChild,tolerance,h+1) + pruneCount(subRoot->neChild,tolerance,h+1) +pruneCount(subRoot->swChild,tolerance,h+1) +pruneCount(subRoot->seChild,tolerance,h+1);

}


int Quadtree::idealPrune(int numLeaves)	const
{
	if(root == NULL) return 0;
	int maxTol = pow(255,2)*3;
	int minTol = 0;

	if(numLeaves < 1) 
	{
		cout << "Wrong num of leaves!" << endl;
		return maxTol+1;
	}
		
	if(numLeaves > pruneSize(0))
		numLeaves = pruneSize(0);
	//if(numLeaves < 1) return idealPrune(1);
	//int maxTol = maxDistRoot2Leave(root, root);

	return checkNumLeaves(numLeaves, (minTol+maxTol)/2, minTol, maxTol);

}

int Quadtree::checkNumLeaves(int numLeaves, int quasiTol, int min, int max) const
{


	int curNum = pruneSize(quasiTol);
	if (max<=min)
		return min;
	if(curNum>numLeaves )
		return checkNumLeaves(numLeaves, (quasiTol+max+1)/2, quasiTol+1, max);
	if(curNum<numLeaves )
		return checkNumLeaves(numLeaves, (quasiTol+min-1)/2, min, quasiTol-1);
	else 
	{

		while(pruneSize(quasiTol)==numLeaves)
		{
			quasiTol = quasiTol-1;
		}
		return quasiTol+1;

	}
}

/*
gdb test code

display numLeaves
display quasiTol
display curNum
display min
display max



b quadtree.cpp:33
display height
display resolutioon
display h
display x_cor
display y_cor
display resolution
display nodeWidth

display ret
display subRoot->element.red
display subRoot->element.blue
display subRoot->element.green

display childLeave->element.red
display childLeave->element.blue
display childLeave->element.green


*/

