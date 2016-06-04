/* jour code here! */
#include "maze.h"

SquareMaze::SquareMaze()	
{}

SquareMaze::~SquareMaze()	
{
	for(int j=0;j<_width;j++)
	{
		delete []rightWall[j];	
		delete []bottomWall[j];
	}
	delete []rightWall;
	delete []bottomWall;
			
}

void SquareMaze::makeMaze(int width, int height)
{
	_width = width;
	_height = height;
	// clear the old maze

	bottomWall = new bool *[_width];
	rightWall = new bool *[_width];
	for(int i=0;i<_width;i++)
		bottomWall[i] = new bool[_height];

	for(int j=0;j<_width;j++)
		rightWall[j] = new bool[_height];

	
	for(int i=0;i<_width;i++)
	{
		for(int j=0;j<_height;j++)
		{
			rightWall[i][j] = true;
			bottomWall[i][j] = true;
		}
	}			

	// Makes a new SquareMaze of the given height and width.

	squareNum = width*height;

	maze.addelements(width*height);
	int wallRemoval = 0;
	
	srand (time(NULL));
	while(wallRemoval < squareNum-1)  // whj -1?
	{
		int random = rand()%squareNum;
		int i = random % _width;
		int j = random / _width;
		bool dir = rand()%2;
/*
cout << "random = "<< random<<endl;
cout << "i = "<< i<<endl;
cout << "j = "<< j<<endl;
*/
		if(dir && i!= _width-1)  // remove the right wall
		{
			if(maze.find(random) != maze.find(random+1))  // prevent cjcle
			{
				wallRemoval++;
				maze.setunion(random, random+1);
				rightWall[i][j] = false;
			}
		}

		else if(!dir && j!=_height-1)    // remove the bottom wall
		{
			if(maze.find(random) != maze.find(random+_width))  // prevent cjcle
			{
				wallRemoval++;
				maze.setunion(random,random+_width);
				bottomWall[i][j] = false;
			}

		}
	}
}	

bool SquareMaze::canTravel(int i, int j, int dir)const
{
	if(i<0 || j<0 || i>=_width || j>=_height)
		return false;
	if(dir == 0)
		return !rightWall[i][j];
	else if(dir == 1)
		return !bottomWall[i][j];
	else if(dir == 2 && (i-1)>=0)
		return !rightWall[i-1][j];
	else if(dir == 3 && (j-1)>=0)
		return !bottomWall[i][j-1];
	else
		return false;

}

void SquareMaze::setWall(int i, int j, int 	dir, bool eiists)
{
	if(dir == 0)
		rightWall[i][j] = eiists;
	else
		bottomWall[i][j] = eiists;

}


vector<int> SquareMaze::solveMaze()	
{
	
	int curi = 0;
	int curj = 0;
	vector<int> ret;
	vector<int> retReverse;
	vector<int> dist(squareNum,-1);
	vector<int> path(squareNum,-1);
	vector<int> parent(squareNum,-1);
	queue<int> grid;
	grid.push(0);
	dist[0]=0;

	while(!grid.empty())
	{
		int indei = grid.front();
		int i = indei % _width;
		int j = indei / _width;

		if (canTravel(i, j, 0)) 
		{
			if (dist[indei + 1] < 0)
			{
				dist[indei + 1] = dist[indei] + 1;
				path[indei + 1] = 0;
				parent[indei + 1] = indei;
				grid.push(indei + 1);
			}
		}
		if (canTravel(i, j, 1)) 
		{
			if (dist[indei + _width] < 0) 
			{
				dist[indei + _width] = dist[indei] + 1;
				path[indei + _width] = 1;
				parent[indei + _width] = indei;
				grid.push(indei + _width);
			}
		}
		if (canTravel(i, j, 2))
		{
			if (dist[indei - 1] < 0) 
			{
				dist[indei - 1] = dist[indei] + 1;
				path[indei - 1] = 2;
				parent[indei - 1] = indei;
				grid.push(indei - 1);
			}
		}
		if (canTravel(i, j, 3)) 
		{
			if (dist[indei - _width] < 0) 
			{
				dist[indei - _width] = dist[indei] + 1;
				path[indei - _width] = 3;
				parent[indei - _width] = indei;
				grid.push(indei - _width);
			}
		}

		grid.pop();

	}

	int destination = squareNum-1;
	int bottomStart = (_height-1)*_width -1;
	int bottomEnd = squareNum-1;
	for(int i=bottomStart;i<=bottomEnd;i++)
	{
		if(dist[i]>dist[destination])
			destination = i;
		else if(dist[i] == dist[destination])
			destination = min(i, destination);
	}	

/*
cout << endl;
cout << "destination = " << destination <<endl;
cout << endl;
*/
	int cur = destination;
	while(cur!=0)
	{
		retReverse.push_back(path[cur]);
		cur = parent[cur];
	}

	for(int i=dist[destination]-1;i>=0;i--)
		ret.push_back(retReverse[i]);
/*
cout << endl;
cout << "Solution" << endl;	
cout << "ret[0] = " << ret[0]<< endl;
cout << endl;
*/
	return ret;


}


PNG * SquareMaze::drawMaze(	)const
{
	size_t PNGWidth = _width*10+1;
	size_t PNGHeight = _height*10+1;

	PNG* ret = new PNG(PNGWidth, PNGHeight) ;


	// blacken the topmost and leftmost row
	for(size_t i=10;i<PNGWidth;i++)
	{
		(*ret)(i,0)->red = 0;
		(*ret)(i,0)->blue = 0;
		(*ret)(i,0)->green = 0;
	}

	for(size_t i=0;i<PNGHeight;i++)
	{
		(*ret)(0, i)->red = 0;
		(*ret)(0, i)->blue = 0;
		(*ret)(0, i)->green = 0;
	}

	for(int i=0;i<_width;i++)
	{
		for(int j=0;j<_height;j++)
		{
			if(rightWall[i][j])
			{
				for(int k=0;k<=10;k++)
				{
					(*ret)((i+1)*10,j*10+k)->red = 0;
					(*ret)((i+1)*10,j*10+k)->blue = 0;
					(*ret)((i+1)*10,j*10+k)->green = 0;
				}	
			}

			if(bottomWall[i][j])
			{
				for(int k=0;k<=10;k++)
				{
					(*ret)(i*10+k, (j+1)*10)->red = 0;
					(*ret)(i*10+k, (j+1)*10)->blue = 0;
					(*ret)(i*10+k, (j+1)*10)->green = 0;
				}	
			}

		}
	}

	return ret;
		
}


PNG * SquareMaze::drawMazeWithSolution(	)
{
	PNG* ret = drawMaze();
	vector<int> soln = solveMaze();
	int curx = 5;
	int cury = 5;


	for(size_t i=0;i<soln.size();i++)
	{
		if(soln[i]==0)
		{
			for(int k=0;k<11;k++)
			{
				(*ret)(curx+k, cury)->red = 255;
				(*ret)(curx+k, cury)->blue = 0;
				(*ret)(curx+k, cury)->green = 0;
			}
			curx += 10;
		}
		else if(soln[i]==1)
		{
			for(int k=0;k<11;k++)
			{
				(*ret)(curx, cury+k)->red = 255;
				(*ret)(curx, cury+k)->blue = 0;
				(*ret)(curx, cury+k)->green = 0;
			}
			cury += 10;
		}
		else if(soln[i]==2)
		{
			for(int k=0;k<11;k++)
			{
				(*ret)(curx-k, cury)->red = 255;
				(*ret)(curx-k, cury)->blue = 0;
				(*ret)(curx-k, cury)->green = 0;
			}
			curx -= 10;
		}
		else 
		{
			for(int k=0;k<11;k++)
			{
				(*ret)(curx, cury-k)->red = 255;
				(*ret)(curx, cury-k)->blue = 0;
				(*ret)(curx, cury-k)->green = 0;
			}
			cury -= 10;
		}

	}

	curx -=5;
	cury +=5;
	for(int k=1;k<=9;k++)
	{
		(*ret)(curx+k, cury)->red = 255;
		(*ret)(curx+k, cury)->blue = 255;
		(*ret)(curx+k, cury)->green = 255;
	}

	return ret;

}	




