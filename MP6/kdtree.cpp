/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <math.h>

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

    for(int i=0;i<newPoints.size();i++)
        index[i] = i;
    KDPoint(newPoints,index, 0);
}

template <int Dim>
void KDTree<Dim>::KDPoint(const vector<Point<Dim>>& newPoints, vector<int> &index, int curDim)
{
    //if(newPoints.empty())
      //  return Point<Dim>();
    int subsize = index.size();
    int med = quickSelect(newPoints, index, 0, subsize-1, curDim, (subsize-1)/2);
    index[med] = med;
    //Point<Dim> subPoint = newPoints[med];

    int left_size = (subsize-1)/2;
    vector<int> left_index;
    for(int i=0;i<left_size;i++)
        left_index[i] = index[i];
    KDPoint(newPoints,left_index, ((curDim+1)%Dim));

    int right_size = subsize-(subsize-1)/2-1;
    vector<int> right_index;
    for(int i=0;i<right_size;i++)
        right_index[i] = index[i+left_size];
    KDPoint(newPoints,right_index, ((curDim+1)%Dim));
}

// helper function for patrition 
template <int Dim>
int KDTree<Dim>::partition(const vector<Point<Dim>>& points, vector<int> &index, int l, int r, int curDim)
{
    double pivot = points[r][curDim];
    if(r>=size)
        return r;
    while(l < r)
    {
        while(points[l][curDim]<pivot)
        //while(smallerDimVal(points[l],points[r],curDim))
            l++;
        while(points[r][curDim]>pivot)
            r--;

        if(points[l][curDim] == points[r][curDim])
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
int KDTree<Dim>::quickSelect(const vector<Point<Dim>>& points, vector<int> &index, int l, int r, int curDim, int median)
{
    if ( l == r ) 
        return index[l];
    int j = partition(points, index, l, r, curDim);
    int length = j - l + 1;
    if ( length == median ) 
        return index[j];
    else if ( median < length ) 
        return quickSelect(points, index, l, j - 1, curDim, median);
    else  
        return quickSelect(points, index, j + 1, r, curDim, median - length);

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int ret = findNearestNeighbor(query, index, 0, size-1, (size-1)/2, 0);
    return points[ret];

}


template <int Dim>
int KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, const vector<int> &index, int l, int u, int curIndex, int curDim) const
{
    if(l > u)
        return curIndex;
    //if(l == u)   // base case
    double currentBest = 0;
    for(int i=0;i<Dim;i++)
        currentBest += pow(query[i]-points[curIndex][i],2);

        int med = ( l + u )/2;
        if(l != u)
        {
            if(smallerDimVal(points[med], query, curDim))
            {
                curIndex = findNearestNeighbor(query, index, l, med-1, curIndex, (curDim+1)%Dim);
                currentBest = 0;
                for(int i=0;i<Dim;i++)
                    currentBest += pow(query[i]-points[curIndex][i],2);
                double med_dist = 0;
                for(int i=0;i<Dim;i++)
                    med_dist += pow(query[i]-points[med][i],2);
                if(med_dist<=currentBest)
                    curIndex = findNearestNeighbor(query, index, med+1, u, curIndex, (curDim+1)%Dim);
            }
          
            else
            {
                curIndex = findNearestNeighbor(query, index, med+1, u, curIndex, (curDim+1)%Dim);
                currentBest = 0;
                for(int i=0;i<Dim;i++)
                    currentBest += pow(query[i]-points[curIndex][i],2);
                double med_dist = 0;
                for(int i=0;i<Dim;i++)
                    med_dist += pow(query[i]-points[med][i],2);
                if(med_dist<=currentBest)
                    curIndex = findNearestNeighbor(query, index, l, med-1, curIndex, (curDim+1)%Dim);
            }
               
        }

        double distance = 0;
        for(int i=0;i<Dim;i++)
            distance += pow(query[i]-points[med][i],2);
        if(distance == 0)
            return med;
        if(distance < currentBest)
        {
            curIndex = med;
            currentBest = distance; 
        }
        else if(distance == currentBest)
        {
            if(points[med]<points[curIndex])
            {
               curIndex = med;
               currentBest = distance; 
            }
        }
return curIndex;


}








