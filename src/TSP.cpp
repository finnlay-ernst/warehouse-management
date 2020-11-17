#include "TSP.h"

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int distance (tuple<int, int> a, tuple<int, int> b) {
    // For our layout distance between locations is always diff x's + diff y's
    // This function could be altered to serve different layouts and TSP would still work
    return abs(get<0>(a) - get<0>(b)) + abs(get<1>(a) - get<1>(b));
}

vector<tuple<int, int>> tsp (vector<tuple<int, int>> vertices) {
    vector<tuple<int, int>> path;
    // Always start from the first entered item
    path.push_back(vertices[0]);
    // Remove first item (not needed in the DP as we have assumed we are starting from here)
    vertices.erase(vertices.begin());
    
    const int n = vertices.size();
    if (n > 20 || n < 1) {
        return path;
    }

    // 2^n (powers of 2 can be calulated with a bit shift)
    const int subProblems = 1 << n;

    // Tabulation for cost of sub problem
    vector<vector<int>> cost(subProblems);
    // Tabulation for item selected for sub problem
    vector<vector<int>> sel(subProblems);
    
    for (int i = 0; i < subProblems; i++) {
        cost[i] = vector<int> (n);
        sel[i] = vector<int> (n);        
        for (int j = 0; j < n; j++) {
            if (i == 0) {                
                // The cost[{ }][j] should be the distance from j to the starting point (path[0])
                cost[i][j] = distance(path[0], vertices[j]);
                sel[i][j] = -1;
                continue;
            }
            if (!(i & (1<<j))) {
                // If j is not in the subset skip this iteration (can't remove j if its already been removed)
                // -1 indicates cost[i][j] is an invalid path
                cost[i][j] = -1;
                sel[i][j] = -1;                                
                continue;
            }
            // Credit to Tanmay Sahay for idea of encoding subsets via bit toggle https://www.hackerearth.com/practice/notes/codemonk-dynamic-programming-ii-1/
            // New subset achieved by removing j
            int subset = i ^ (1 << j);
            int min = -1;
            // -1 indicates no item selected
            sel[i][j] = -1;
            for (int k = 0; k < n; k++) {
                if (k == j) {
                    continue;
                }
                if (cost[subset][k] < 0) {
                    // Skip invalid paths
                    continue;
                }
                const int optionCost = cost[subset][k] + distance(vertices[k], vertices[j]);
                if (optionCost < min || min == -1) {
                    min = optionCost;
                    sel[i][j] = k;
                }
            }
            cost[i][j] = min;
        }
    }

    int selected = subProblems - 1;       
    int x = 0;
    for (int i = 0; i < n; i++) {        
        const int iCost = cost[selected][i] + distance (vertices[i], path[0]);        
        const int xCost = cost[selected][x] + distance (vertices[x], path[0]);
        if ((iCost < xCost && iCost >= 0) || cost[selected][x] < 0) {
            x = i;
        }
    }
    cout << "Optimal path length (returning to the first item): " << cost[selected][x] + distance (vertices[x], path[0]) << endl;
    while (selected) {        
        path.push_back(vertices[x]);
        int oldX = x;
        x = sel[selected][x];
        // Removes the selected item from the set
        selected = selected ^ (1 << oldX);        
    }
    path.push_back(path[0]);
    return path;
}
