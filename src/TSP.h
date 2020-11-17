#ifndef TSP_H 
#define TSP_H

#include <vector>
#include <tuple>

using namespace std;

/*
Gets distance between 2 stockroom locations
Inputs:
    a, b: Tuples containing x, y coordinates to get the distance between 
Outputs:
    Distance between provided tuples
*/
int distance (tuple<int, int> a, tuple<int, int> b);

/*
A DP solution the the travelling salesman problem. Returns the route user should take the collect items.
Inputs:
    vertices: Locations of items to be collected. No more than 20 vertices should be entered.
Outputs:
    Locations of items, ordered according to the optimal collection order
*/
vector<tuple<int, int>> tsp (vector<tuple<int, int>> vertices);

#endif
