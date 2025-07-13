#include "Functions.h"

void read_distribution(const char* filename, double distribution[30]) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file!");
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}