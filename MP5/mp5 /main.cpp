/**
 * @file main.cpp
 * Contains code to test your Quadtree implementation.
 */

#include <iostream>
#include "png.h"
#include "quadtree.h"

using std::cout;
using std::endl;

int main()
{
    
    PNG imgIn, imgOut;
    imgIn.readFromFile("in.png");

    // test constructor, decompress
 Quadtree halfTree(imgIn, 128);
    imgOut = halfTree.decompress();
    imgOut.writeToFile("outHalf.png");

    // now for the real tests
    Quadtree fullTree;
    fullTree.buildTree(imgIn, 256);
    

    // you may want to experiment with different commands in this section

   // test pruneSize and idealPrune (slow in valgrind, so you may want to
    // comment these out when doing most of your testing for memory leaks)
    cout << "fullTree.pruneSize(0) = "      << fullTree.pruneSize(0) << endl;
    cout << "fullTree.pruneSize(100) = "    << fullTree.pruneSize(100) << endl;
    cout << "fullTree.pruneSize(1000) = "   << fullTree.pruneSize(1000) << endl;
    cout << "fullTree.pruneSize(100000) = " << fullTree.pruneSize(100000) << endl;

   // cout << "fullTree.pruneSize(195075) = " << fullTree.pruneSize(195075) << endl;
   // cout << "fullTree.idealPrune(1) = "  << fullTree.idealPrune(1) << endl;
    //cout << "fullTree.idealPrune(2) = "  << fullTree.idealPrune(2) << endl;
    // << "fullTree.idealPrune(3) = "  << fullTree.idealPrune(3) << endl;
    cout << "fullTree.idealPrune(1000) = "  << fullTree.idealPrune(1000) << endl;
    cout << "fullTree.idealPrune(5000) = "  << fullTree.idealPrune(5000) << endl;
    cout << "fullTree.idealPrune(10000) = " << fullTree.idealPrune(10000) << endl;
    //cout << "fullTree.idealPrune(0) = " << fullTree.idealPrune(0) << endl;
    //cout << "fullTree.pruneSize(fullTree.idealPrune(1)) "<< fullTree.pruneSize(fullTree.idealPrune(1)) << endl;
    //cout << "fullTree.pruneSize(fullTree.idealPrune(2)) "<< fullTree.pruneSize(fullTree.idealPrune(2)) << endl;
    //cout << "fullTree.pruneSize(fullTree.idealPrune(3)) "<< fullTree.pruneSize(fullTree.idealPrune(3)) << endl;

    cout<< "fullTree.pruneSize(fullTree.idealPrune(255*255*3)) "<< fullTree.pruneSize(fullTree.idealPrune(255*255*3)) << endl;
    cout<< "fullTree.pruneSize(fullTree.idealPrune(5000)) "<< fullTree.pruneSize(fullTree.idealPrune(5000)) << endl;

    // Test some creation/deletion functions
    Quadtree fullTree2;
    fullTree2 = fullTree;
    imgOut = fullTree2.decompress();
    imgOut.writeToFile("outCopy.png");
  

    // test clockwiseRotate
    fullTree.clockwiseRotate();
    imgOut = fullTree.decompress();
    imgOut.writeToFile("outRotated.png");

    // test prune
    fullTree = fullTree2;
    fullTree.prune(1000);
    imgOut = fullTree.decompress();
    imgOut.writeToFile("outPruned.png");

    // test several functions in succession
    Quadtree fullTree3(fullTree2);
    fullTree3.clockwiseRotate();
    fullTree3.prune(10000);
    fullTree3.clockwiseRotate();
    fullTree3.clockwiseRotate();
    fullTree3.clockwiseRotate();
    imgOut = fullTree3.decompress();
    imgOut.writeToFile("outEtc.png");
/*
    // ensure that printTree still works
    Quadtree tinyTree(imgIn, 32);
    //Quadtree temp = tinyTree;
    cout << "Printing tinyTree:\n";
    tinyTree.prune(100);
    tinyTree.printTree();
*/
    //test pruneSize

    //cout << "tinyTree.pruneSize(100) = "      <<   temp.pruneSize(100) << endl;
    Quadtree emptyTree;
    Quadtree test = Quadtree(emptyTree);
    test.printTree();
    Quadtree test2 = emptyTree;
    test.printTree();
    test2.printTree();
    //test prune
    //Quadtree tinyPrune = tinyTree;
    //tinyPrune.prune(10);
    //cout << "Printing tinyPrune:\n";
   //tinyTree.prune(100);
    //tinyPrune.printTree();

    return 0;
}
