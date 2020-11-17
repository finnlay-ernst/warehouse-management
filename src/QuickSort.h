#ifndef QUICKSORT_H 
#define QUICKSORT_H

#include <vector>
#include "Item.h"

using namespace std;

/*
Utility for swapping two elements' positions a vector
Inputs:
    arr: Reference to the vector to perform the swap on
    a, b: The two indices to be swapped in the vector
Outputs:
    N/A
*/
void swap(vector<Item*> &arr, int a, int b);

/*
Partitions the array based on arr[r], leaving the item at arr[r]
in its sorted position at the end
Inputs:
    arr: vector to sort
    p: Start point of subsection of array we are sorting
    r: End point of subsection of array we are sorting
Outputs:
    Index of item that is now in its correct position
*/
int partition(vector<Item*> &arr, int p, int r);

/*
Generates a random index to partition the array with
Inputs:
    arr: vector to sort
    p: Start point of subsection of array we are sorting
    r: End point of subsection of array we are sorting
Outputs:
    Index of item that is now in its correct position
*/
int randPartition (vector<Item*> &arr, int p, int r);

/*

Inputs:
    arr: vector to sort
    p: Start point of subsection of array we are sorting
    r: End point of subsection of array we are sorting
Outputs:
    N/A
*/
void randQuickSort (vector<Item*> &arr, int p, int r);

#endif
