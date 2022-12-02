#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int main() {
    ifstream fileStream;
    fileStream.open("input.txt");
    int total = 0;
    list<int> total_list;

    string line;
    while(getline(fileStream, line)) {
        if (line.empty()) {
            total_list.push_back(total);
            total = 0;
            continue;
        }
        total = total + stoi(line);
    }
    total_list.push_back(total);
    total_list.sort();
    total_list.reverse();

    int top = total_list.front();
    int top3 = 0;
    for(int i = 0; i < 3; i++) {
        top3 = top3 + total_list.front();
        total_list.pop_front();
    }
    cout << "Part 1: " << top << endl;
    cout << "Part 2: " << top3 << endl;
    return 0;
}