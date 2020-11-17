#ifndef ITEM_H 
#define ITEM_H

#include <string>
#include <tuple>

using namespace std;


// Schema for items in the database
class Item {
    public:
        int sku;
        string name;
        int stockCount;
        tuple<int, int> fixtureLocation;
        Item (); 
        Item (int, string, int, tuple<int, int>); 
        string print ();
        string printForFile ();
};

#endif
