#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

using namespace std;

tuple<int, int, int, int> get_boundries(string line) {
    int comma = line.find(',');
    string range_1 = line.substr(0, comma), range_2 = line.substr(comma+1);
    int dash_1 = range_1.find('-'), dash_2 = range_2.find('-');
    return make_tuple (
        stoi(range_1.substr(0, dash_1)),
        stoi(range_1.substr(dash_1 + 1)),
        stoi(range_2.substr(0, dash_2)),
        stoi(range_2.substr(dash_2 + 1)));
}

bool contains(int min_1, int max_1, int min_2, int max_2) {
    return (min_1 <= min_2 && max_1 >= max_2) || (min_1 >= min_2 && max_1 <= max_2);
}

bool overlaps(int min_1, int max_1, int min_2, int max_2) {
  return (min_1 <= max_2 && min_2 <= max_1);
}

int main() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int contains_total = 0, overlaps_total = 0;
    int min_1, max_1, min_2, max_2;
    tuple<int, int, int, int> boundries;
    string line;
    while (getline(fileStream, line)) {
        tie(min_1, max_1, min_2, max_2) = get_boundries(line);
        contains_total += contains(min_1, max_1, min_2, max_2);
        overlaps_total += overlaps(min_1, max_1, min_2, max_2);
    }
    cout << "Part 1: " << contains_total << endl;
    cout << "Part 2: " << overlaps_total << endl;
    return 0;
}