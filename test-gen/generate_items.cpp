//File to generate random positive integers on new lines of a txt file
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Please specify the output file, followed by how many numbers to generate :)\n";
        return 0;
    }

    fstream outputFile(argv[1]);
    
    srand(time(NULL));
    // 3000000 Example_Item10 60 20 5
    int n{stoi(argv[2])};
    // outputFile << to_string(n) << "\n";
    int sku = 1000000;
    for (int i = 0; i < n; i++) {
        //Generate random number between 0 and 1000         
        outputFile << to_string(sku++) << " " << "Example_Item" << to_string(i)  << " " << to_string(1000 - (rand() % 1000)) << " " << to_string(320 - (rand() % 320)) << " " << to_string(320 - (rand() % 320)) << "\n";
    }
    outputFile.close();
    return 0;
}