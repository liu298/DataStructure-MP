/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <utility> 

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */

     int rows = theSource.getRows();
     int cols = theSource.getColumns();
     MosaicCanvas * ret = new MosaicCanvas(rows, cols);

     // create color2tiles map 
     map<Point<3>, TileImage> color2tiles;
     vector<Point<3>> colors;

     for(size_t i=0;i<theTiles.size();i++)
     {
     	RGBAPixel tilesColor = theTiles[i].getAverageColor();
     	double tilesColorArr[3] = {(double)tilesColor.red, (double)tilesColor.green, (double)tilesColor.blue};
     	Point<3> tilesColorPoint(tilesColorArr);
		pair<Point<3>, TileImage> newPair = make_pair(tilesColorPoint, theTiles[i]);
		color2tiles[tilesColorPoint] =  theTiles[i];

		colors.push_back(tilesColorPoint);
     }
     	
     // create kdtree with points of all colors from tilesImages

     KDTree<3> colorTree(colors);
     
     for(int i=0;i<rows;i++)
     {
     	for(int j=0;j<cols;j++)
     	{
     		RGBAPixel sourceColor = theSource.getRegionColor(i,j);
     		double arrSourceColor[3] = {(double)sourceColor.red, (double)sourceColor.green, (double)sourceColor.blue};
     		Point<3> sourceColorPoint(arrSourceColor);
     		Point<3>  foundTileColor = colorTree.findNearestNeighbor(sourceColorPoint);
     		TileImage targetTileImage = color2tiles[foundTileColor];
     		ret->setTile(i, j, targetTileImage);
     	}
     }

    return ret;

}

