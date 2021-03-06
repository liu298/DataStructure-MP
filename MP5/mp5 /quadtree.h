/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    Quadtree();
    
    Quadtree(PNG const & source, int resol);
    
    Quadtree(Quadtree const & other);
    
    ~Quadtree();
    
    Quadtree const & operator=(Quadtree const & other);
    
    RGBAPixel getPixel(int x, int y)  const;

    PNG decompress () const;

    void buildTree(PNG const & source, int resol); 

    void clockwiseRotate ();   

    void prune(int tolerance);

    int pruneSize (int tolerance) const;

    int idealPrune(int numLeaves) const;


  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */
        RGBAPixel element; /**< the pixel stored as this node's "data" */
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */
    int resolution;

    /**
    * Deletes the current contents of this Quadtree object, 
    * then turns it into a Quadtree object representing the 
    * upper-left d by d block of source.
    **/
    
    void embedPNG(PNG const & source, QuadtreeNode * &subRoot,int h, 
                double x_cor, double y_cor, int resolution);
    QuadtreeNode * copyNode(QuadtreeNode * const &subRoot) const;
    void clear(QuadtreeNode * &subRoot);
    QuadtreeNode * findPixel(QuadtreeNode * const &subRoot,
                                    int x,int y,double cur_x,double cur_y, int h) const;
    void rotateNode(QuadtreeNode * subRoot);
    
    void pruneNode(QuadtreeNode * &subRoot, int tolerance);
    
    bool checkPrunable(QuadtreeNode * const &subRoot, QuadtreeNode * const &childLeave, int tolerance) const;

    int pruneCount(QuadtreeNode * const &subRoot, int tolerance, int h) const;

    //int maxDistRoot2Leave(QuadtreeNode * const &subRoot, QuadtreeNode * const &childLeave) const;

    int checkNumLeaves(int numLeaves, int quasiTol, int min, int max) const;
    //int height; /**< the height of quadtree >**/

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
