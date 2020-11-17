#include "QuickSort.h"

#include <iostream>

// Using a modified version of the RandQuickSort psuedocode shown in lectures
// Slide 15: https://cs.anu.edu.au/courses/comp3600/week4-probAnalysis-aftClass.pdf

// This is similar to my assignment 2 code but has been altered to fully sort 
// the array and compare items based on stock levels

void swap(vector<Item*> &arr, int a, int b) {
	Item* x = arr[a];
	arr[a] = arr[b];
	arr[b] = x;
}

int partition(vector<Item*> &arr, int p, int r) { 
	Item* x = arr[r]; 
	int i = p - 1; 
	for (int j = p; j < r; j++) { 
		if (arr[j]->stockCount <= x->stockCount) { 
			i++; 
			swap(arr, i, j); 
		} 
	} 
	//Swap the pivot (arr[r]) into its correct location (i+1)
	swap(arr, i + 1, r); 
	// Return the index of the pivot, this is the correct spot for this element if the array were sorted
	return i + 1; 
} 

int randPartition (vector<Item*> &arr, int p, int r) {
    // Generate a random integer between p and r inclusive of both p and r    
	int i = p + (rand() % (r - p + 1));
	// Put pivot at the end of array (precondition for partition())
	swap(arr, i, r);
	return partition(arr, p, r);
}

void randQuickSort (vector<Item*> &arr, int p, int r) {	
    if (p < r) {		
        int q = randPartition(arr, p, r);
		randQuickSort(arr, p, q-1);
        randQuickSort(arr, q+1, r);
    } 
}
