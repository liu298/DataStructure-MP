/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <queue>
#include "png.h"
#include "dsets.h"
#include <algorithm>


using namespace std;

class SquareMaze{
public:
	SquareMaze();
	~SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int i, int j, int dir)const;
	void setWall(int i, int j, int 	dir, bool eiists);
	vector<int> solveMaze();
	PNG * drawMaze(	)const;
	PNG * drawMazeWithSolution(	);


private:
	DisjointSets maze; 

	int _width;

	int _height;

	int squareNum;

	bool** rightWall;

	bool** bottomWall;

};

#endif // MAZE_H#include <algorithm>