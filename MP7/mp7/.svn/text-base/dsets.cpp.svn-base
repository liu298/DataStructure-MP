/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements(int num)
{
	if(num<1)
		return;
	for(int i=0;i<num;i++)
		elements.push_back(-1);

}

int DisjointSets::find(int elem)
{
	if(elements[elem]<0)
		return elem;
	int index = elem;	
	while(elements[index]>=0)
		index = elements[index];
	elements[elem] = index;
	return index;

}

void DisjointSets::setunion(int a, int b)
{

	int aRoot = find(a);
	int bRoot = find(b);

	if(aRoot == bRoot)  // check if a and b are already in an union 
		return;
	if(abs(elements[aRoot]) >= abs(elements[bRoot]))
	{
		elements[aRoot] += elements[bRoot];
		elements[bRoot] = aRoot;
	}
	else
	{
		elements[bRoot] += elements[aRoot];
		elements[aRoot] = bRoot;
	}

}