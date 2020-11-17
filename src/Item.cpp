#include "Item.h"

#include <string>
#include <tuple>

using namespace std;

// Constructor for entering item
Item::Item (int itemSku, string itemName, int itemStockCount, tuple<int, int> itemLocation) {
    sku = itemSku;
    name = itemName;
    stockCount = itemStockCount;
    fixtureLocation = itemLocation;
}

Item::Item (){
    sku = -1;
    name = "";
    stockCount = 0;
    fixtureLocation = make_tuple(NULL, NULL);
}

string Item::print () {
    return name + ", " + to_string(sku) + " | " + "Stock: " + to_string(stockCount) + ", Location: " + to_string(get<0>(fixtureLocation)) + ", "+ to_string(get<1>(fixtureLocation));
}

string Item::printForFile () {
    return to_string(sku) + " " + name + " " + to_string(stockCount) + " " + to_string(get<0>(fixtureLocation)) + " " + to_string(get<1>(fixtureLocation));
}
