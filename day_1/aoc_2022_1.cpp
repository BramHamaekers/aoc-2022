#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int total = 0;
    vector<int> total_v;
    string line;
    while(getline(fileStream, line)) {
        if (!line.empty()) {
             total = total + stoi(line);
             continue;
        }
        total_v.push_back(total);
        total = 0;
    }
    total_v.push_back(total);
    sort(total_v.begin(), total_v.end());
    cout << "Part 1: " << total_v.back() << endl;
    cout << "Part 2: " << total_v.back() + total_v[total_v.size()-2] + total_v[total_v.size()-3] << endl;
    return 0;
}