#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

bool contains(string range_1, string range_2) {
    int dash_1 = range_1.find('-');
    int dash_2 = range_2.find('-');
    int min_1 = stoi(range_1.substr(0,dash_1));
    int max_1 = stoi(range_1.substr(dash_1 + 1));
    int min_2 = stoi(range_2.substr(0,dash_2));
    int max_2 = stoi(range_2.substr(dash_2 + 1));
    return (min_1 <= min_2 && max_1 >= max_2) || (min_1 >= min_2 && max_1 <= max_2);
}

bool overlaps(string range_1, string range_2) {
    int dash_1 = range_1.find('-');
    int dash_2 = range_2.find('-');
    int min_1 = stoi(range_1.substr(0,dash_1));
    int max_1 = stoi(range_1.substr(dash_1 + 1));
    int min_2 = stoi(range_2.substr(0,dash_2));
    int max_2 = stoi(range_2.substr(dash_2 + 1));
    return (min_1 <= min_2 && min_2 <= max_1) || (min_1 <= max_2 && max_2 <= max_1) || contains(range_1, range_2);
}

int part_1() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int comma;
    int total = 0;
    string line;
    while (getline(fileStream, line)) {
        comma = line.find(',');
        string range_1 = line.substr(0, comma);
        string range_2 = line.substr(comma+1);
        total += contains(range_1, range_2);
    }
    return total;
}

int part_2() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int comma;
    int total = 0;
    string line;
    while (getline(fileStream, line)) {
        comma = line.find(',');
        string range_1 = line.substr(0, comma);
        string range_2 = line.substr(comma+1);
        total += overlaps(range_1, range_2);
    }
    return total;
}

int main() {
    cout << "Part 1: " << part_1() << endl;
    cout << "Part 2: " << part_2() << endl;
}