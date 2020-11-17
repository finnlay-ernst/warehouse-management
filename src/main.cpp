// Compiler Modules
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <time.h>
// #include <chrono>

// My Modules
#include "AVL.h"
#include "TSP.h"
#include "QuickSort.h"
#include "Item.h"

using namespace std;

// Valid inputs to access functionalities
enum supportedFunctionality {
    FIND,
    INSERT,
    REMOVE,
    PATH,
    UPDATE,
    PRIORITY,
    INVALID
};

supportedFunctionality inputToEnum (string const& functionality) {
    if (functionality == "find") return FIND;
    if (functionality == "insert") return INSERT;
    if (functionality == "remove") return REMOVE;
    if (functionality == "path") return PATH;
    if (functionality == "update") return UPDATE;
    if (functionality == "priority") return PRIORITY;
    return INVALID;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please supply the mode of operation & the input file :)" << endl;
        return 0;
    }

    if (string (argv[1]) == "F1") {
        cout << "Testing functionality 1..." << endl << endl;

        Node* root = NULL;
        fstream dataFile(argv[2]);
        Item item;
        int x, y;

        // int itemCount, prevHeight;        
        // auto algo_s = chrono::steady_clock::now();
        
        // Group runtimes by tree height and count items inserted in that time so we can get 
        // an average insertion runtime for each height
        while (dataFile >> item.sku >> item.name >> item.stockCount >> x >> y) {
            // itemCount++;
            item.fixtureLocation = make_tuple(x, y);
            root = insert(root, item);
            // if (root->height != prevHeight) {
            //     auto algo_e = chrono::steady_clock::now();
            //     auto algo_duration = chrono::duration_cast<chrono::nanoseconds>(algo_e - algo_s);
            //     cout << root->height << " " << algo_duration.count() << " " << itemCount << endl;                 
            //     itemCount = 0;
            //     algo_s = chrono::steady_clock::now();
            // }
            // prevHeight = root->height;
        }
        cout << "Tree height: " << root->height << endl;
        dataFile.close();
    }
    else if (string (argv[1]) == "F2") {
        cout << "Testing functionality 2..." << endl << endl;

        fstream dataFile(argv[2]);
        vector<tuple<int, int>> locations;
        int x, y;
        while (dataFile >> x >> y) {
            locations.push_back(make_tuple(x, y));
            // auto algo_s = chrono::steady_clock::now();
            // vector<tuple<int, int>> shortestPath = tsp(locations);
            // auto algo_e = chrono::steady_clock::now();
            // auto algo_duration = chrono::duration_cast<chrono::nanoseconds>(algo_e - algo_s);
            
            // cout << locations.size() << " " << algo_duration.count() << endl;
        }

        
        vector<tuple<int, int>> shortestPath = tsp(locations);
        cout << "Please take this path to collect your items:";
        for (unsigned int i = 0; i < shortestPath.size(); i++) {
            cout << "-> (" << get<0>(shortestPath[i]) << ", " << get<1>(shortestPath[i]) << ") ";
        }
        cout << endl;
    }
    else if (string (argv[1]) == "F3") {
        cout << "Testing functionality 3..." << endl << endl;
        
        // Initialise the RNG for random partition selection in QuickSort
        srand(time(NULL));
        fstream dataFile(argv[2]);
        Node* root = NULL;
        Item item;
        int x, y, itemCount;        
        while (dataFile >> item.sku >> item.name >> item.stockCount >> x >> y) {
            itemCount++;
            item.fixtureLocation = make_tuple(x, y);
            root = insert(root, item);            
        }
        dataFile.close();
        
        // Test sorting item lists of size 2^i
        // for (int i = 1; i < itemCount; i<<=1) {            
        //     auto algo_s = chrono::steady_clock::now();
        //     vector<Item*> arr = getRange(root, 0, 1000000+i);    
        //     randQuickSort(arr, 0, arr.size()-1);
        //     auto algo_e = chrono::steady_clock::now();            
                    
        //     auto algo_duration = chrono::duration_cast<chrono::nanoseconds>(algo_e - algo_s);            
        //     cout << arr.size() << " " << algo_duration.count() << endl;
        // }
        vector<Item*> arr = getRange(root, 0, 1000000+itemCount);    
        randQuickSort(arr, 0, arr.size()-1);
        if (arr.size() < 100) {
            for (unsigned int i = 0; i < arr.size(); i++) {
                cout << arr[i]->print() << endl;
            }
        }
        cout << endl;
    }
    else {
        cout << "Welcome to the COMP3600 warehouse management system! Press esc & enter to exit." << endl;

        Node* root = NULL;
        // Tree data will be read from file here
        fstream dataFile(argv[2]);

        Item item;
        int x, y;
        while (dataFile >> item.sku >> item.name >> item.stockCount >> x >> y) {
            item.fixtureLocation = make_tuple(x, y);            
            root = insert(root, item);
        }
        dataFile.close();

        char input[256];
        while (true) {
            cin.getline(input, 256);

            if (input[0] == 27) break;

            string stringArgs = string (input);
            vector<string> args;

            // Spliting into vector based on code by Shiqi Ai & Biswajit Roy here: https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
            while (stringArgs.size()) {
                unsigned int index = stringArgs.find(" ");
                if (index != string::npos) {
                    args.push_back(stringArgs.substr(0,index));
                    stringArgs = stringArgs.substr(index+1);
                    if (!stringArgs.size()) args.push_back(stringArgs);
                }
                else {
                    args.push_back(stringArgs);
                    stringArgs = "";
                }
            }

            string functionality = args[0];
            args.erase (args.begin());

            // Excess arguments will be ignored
            if (args.size() < 1) {
                cout << "ERROR: Please enter arguments" << endl;
                continue;
            }

            // String switch statements based on code by D.Shawley https://stackoverflow.com/questions/650162/why-the-switch-statement-cannot-be-applied-on-strings
            switch (inputToEnum (functionality)) {
                case FIND: {
                    if (args.size() < 1) {
                        cout << "ERROR: Please provide all arguments" << endl;
                        break;
                    }

                    Node* result = find (root, stoi(args[0]));
                    if (result) {
                        cout << result->value.print() << endl;
                    }
                    else {
                        cout << "Could not find item in database" <<endl;
                    }
                    break;
                }
                case INSERT: {
                    if (args.size() < 5) {
                        cout << "ERROR: Please provide all arguments" << endl;
                        break;
                    }

                    tuple<int, int> location (make_tuple(stoi(args[3]), stoi(args[4])));
                    Item x(stoi (args[0]), args[1], stoi(args[2]), location);

                    cout << "Inserting '" << x.Item::print() << "' into database" << endl;
                    root = insert (root, x);                    
                    break;
                }
                case UPDATE: {
                    if (args.size() < 2) {
                        cout << "ERROR: Please provide all arguments" << endl;
                        break;
                    }

                    cout << "Updating " << args[0] << "'s stock count to " << args[1] << endl;
                    updateCount(root, stoi (args[0]), stoi (args[1]));
                    break;
                }
                case REMOVE: {
                    cout << "Removing " << args[0] << " from database" << endl;
                    root = remove (root, stoi(args[0]));                    
                    break;
                }
                case PATH: {
                    cout << "Finding optimal path between points..." << endl;
                    vector<tuple<int, int>> locations;
                    int n = (args.size() > 20) ? 20 : args.size();

                    for (int i = 0; i < n; i++) {
                        Node* x = find (root, stoi (args[i]));
                        // Ignore non-existant SKUs
                        if (x) {
                            locations.push_back(x->value.fixtureLocation);
                        }
                    }
                    cout << endl;
                    vector<tuple<int, int>> shortestPath = tsp(locations);
                    cout << "Please take this path to collect your items:";
                    for (unsigned int i = 0; i < shortestPath.size(); i++) {
                        cout << "-> (" << get<0>(shortestPath[i]) << ", " << get<1>(shortestPath[i]) << ") ";
                    }
                    cout << endl;
                    break;
                }
                case PRIORITY: {
                    if (args.size() < 2) {
                        cout << "ERROR: Please provide all arguments" << endl;
                        break;
                    }

                    cout << "Ranking items with sku between " << args[0] << " and " << args[1] << " by stock level..." << endl;

                    vector<Item*> arr = getRange(root, stoi(args[0]), stoi(args[1]));    
                    randQuickSort(arr, 0, arr.size()-1);
                    for (unsigned int i = 0; i < arr.size(); i++) {
                        cout << arr[i]->print() << endl;
                    }
                    break;
                }
                default: {
                    cout << "Invalid functionality: " << functionality << endl;
                }
            }
        }

        // Tree will be written back to file here
        fstream outputFile(argv[2]);
        outputFile << save(root) << endl;
        outputFile.close();
    }


    return 0;
}
