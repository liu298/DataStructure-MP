/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <math.h>
#include <iostream>
#include <vector>
#include <math.h> 
 using std::cout;
 using std::endl;


template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim]<second[curDim])
        return true;
     if(first[curDim]>second[curDim])
        return false;
    else return (first<second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double bestDist = 0;
     double curDist = 0;
     for(int i=0;i<Dim;i++)
     {
        bestDist += pow(target[i]-currentBest[i], 2);
        curDist += pow(target[i]-potential[i], 2);
     }

     if(curDist<bestDist)
        return true;
    if(curDist>bestDist)
        return false;
    else return (potential<currentBest);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(!newPoints.empty())
    {
    //points = newPoints;
    size = newPoints.size();
   // cout<< "index size = " << index.size() << endl;
     //cout<< "newPoints size = " << size << endl;
    for(int i=0;i<size;i++)
        index.push_back(i);
    //cout<< "index size = " << index.size() << endl;

    KDPoint(newPoints, 0, size-1, 0);
/*
        cout<< "index size = " << index.size() << endl;
    for(int i=0;i<size;i++)
        cout << "index[" << i << "] = "<< index[i] << endl;
*/
    for(int i=0;i<size;i++)
        points.push_back(newPoints[index[i]]);
/*
    // print index and points 
    for(int i=0;i<size;i++)
        cout << "index[" << i << "] = "<< index[i] << endl;
    for(int i=0;i<size;i++)
        cout << "points[" << i << "] = "<< points[i] << endl;
*/  
    }


}

template <int Dim>
void KDTree<Dim>::KDPoint(const vector<Point<Dim>>& newPoints, int low, int up, int curDim)
{
    if(low<up)
    {   
    int subsize = up-low+1;
    int med = quickSelect(newPoints, low, up, curDim, (int)(subsize+1)/2);


    //cout << "med = " << med << endl;
    //index[(int)(low+up)/2] = med;
  //  for(int i=0;i<size;i++)
    //    cout << "index[" << i << "] = "<< index[i] << endl;

    int left_size = ((int)(subsize+1)/2)-1;
     //cout << "left_size = " << left_size << endl;
   // vector<int> left_index;
   // for(int i=0;i<left_size;i++)
     //   left_index.push_back(subindex[i]);
    KDPoint(newPoints, low, low+left_size-1, ((curDim+1)%Dim));

    int right_size = subsize-left_size -1;
    //cout << "right_size = " << right_size << endl;
    // vector<int> right_index;
    // for(int i=0;i<right_size;i++)
       // right_index.push_back(subindex[i+left_size+1]);
    KDPoint(newPoints, low+left_size+1, up, ((curDim+1)%Dim));

    }
    
}

// helper function for patrition 
template <int Dim>
int KDTree<Dim>::partition(const vector<Point<Dim>>& points, int l, int r, int curDim)
{
    
    //if(r>size)
      //  return r;
    Point<Dim> pivot = points[index[r]];
    while(l < r)
    {
        while(smallerDimVal(points[index[l]],pivot,curDim))
        //while(points[index[l]][curDim]<pivot)
            l++;
        while(smallerDimVal(pivot,points[index[r]],curDim)) 
        //while(points[index[r]][curDim]>pivot)
            r--;

        if(points[index[l]] == points[index[r]])
            l++;
        else if(l < r)
        {
            int temp = index[l];
            index[l] = index[r];
            index[r] = temp;

        }
    }

    return r;
}

template <int Dim>
int KDTree<Dim>::quickSelect(const vector<Point<Dim>>& points, int l, int r, int curDim, int median)
{
    if ( l == r ) 
        return index[l];
   // cout << ".cpp line 144. index[l]= " << index[l] <<" index[r] = "<< index[r] << endl;
    int j = partition(points, l, r, curDim);
    int length = j - l + 1;
    if ( length == median ) 
        return index[j];
    else if ( median < length ) 
        return quickSelect(points, l, j - 1, curDim, median);//
    else  
        return quickSelect(points, j + 1, r, curDim, median - length);//

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int ret = findNearestNeighbor(query, 0, size-1, (int)(size-1)/2, -1);
    return points[ret];

}


template <int Dim>
int KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int l, int u, int curIndex, int curDim) const
{
    curDim = (curDim+1)%Dim; // curDim = (0, 1, 2 ...), Dim = 2, curDim = (0=>0, 1=>1, 2=>0)
    int med = ( l + u )/2;   
    if(l >= u)
    {
        //cout << "l: " << l << " >= u: " << u <<endl;
        if(shouldReplace(query,points[curIndex],points[l]))
        {
            //cout << "Shold Replace points[curIndex]" << points[curIndex][0] << "with points[l]" << points[l][0] << endl;
            return l;
        }
            
        else 
        {
           //cout << "Shold NOT Replace points[curIndex]" << points[curIndex][0] << "with points[l]" << points[l][0] << endl;
           return curIndex;
        }
            
    }
       // cout << "cur_index " << curIndex << endl;
       
        //cout << "L = " << l << ", U = " << u <<endl;
        //cout << "Check point: " << med <<endl;
        //cout << "curDim = " << curDim<<endl;
    
    {
        if(smallerDimVal(points[med], query, curDim))
        {
            //cout << "cur parent " << points[med][curDim] << " < " << query[curDim] << endl;
            curIndex = findNearestNeighbor(query, med+1, u, curIndex, curDim);
/*
                double dimDist_med2target = fabs(points[med][curDim]-query[curDim]);
                double dimDist_cur2target = fabs(points[curIndex][curDim]-query[curDim]);
                if(dimDist_med2target<=dimDist_cur2target)
                    curIndex = findNearestNeighbor(query, l, med-1, curIndex, curDim);
                if(shouldReplace(query,points[curIndex],points[med]))
                curIndex = index[med];
*/
            if(shouldReplace(query,points[curIndex],points[med]))
                curIndex = med;
            double dimDist_med2target = pow(points[med][curDim] - query[curDim],2);
            double dimDist_cur2target = 0;
            for(int i=0;i<Dim;i++)
            {
                dimDist_cur2target += pow(points[curIndex][i]-query[i],2);
            }
            if(dimDist_med2target<=dimDist_cur2target)
            //if(fabs(points[index[med]][curDim]-query[curDim]) <= fabs(points[curIndex][curDim]<query[curDim]))
            curIndex = findNearestNeighbor(query, l, med-1, curIndex, curDim);

        }
        else
        {
            //cout << "cur parent " << points[med][curDim] << " > " << query[curDim] << endl;
            curIndex = findNearestNeighbor(query, l, med-1, curIndex, curDim);

            if(shouldReplace(query,points[curIndex],points[med]))
                curIndex = med;

            double dimDist_med2target = pow(points[med][curDim] - query[curDim],2);
            double dimDist_cur2target = 0;
            for(int i=0;i<Dim;i++)
            {
                dimDist_cur2target += pow(points[curIndex][i]-query[i],2);
            }
/*                
                curIndex = findNearestNeighbor(query, l, med-1, curIndex, curDim);
                double dimDist_med2target = fabs(points[med][curDim]-query[curDim]);
                double dimDist_cur2target = fabs(points[curIndex][curDim]-query[curDim]);
*/ 
            if(dimDist_med2target<=dimDist_cur2target)
                curIndex = findNearestNeighbor(query, med+1, u, curIndex, curDim);

        }
            return curIndex; 
    }

 // l==u, leave point
/*
    else
    {
        if(shouldReplace(query,points[curIndex],points[med]))
            return index[med];
        else return curIndex;
    }
*/

}

/**********
gdb test code

gdb testkdtree
b kdtree.cpp:63
b kdtree.cpp:117
run testkdtree

display l
display r
display curDim
display median
display index[0]
display index[1]

display l
display u
display currentBest
display med
**************************/







