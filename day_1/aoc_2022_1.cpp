#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int part_1() {
    ifstream fileStream;
    fileStream.open("input.txt");
    int total = 0;
    int highest = 0;

    string line;
    while(getline(fileStream, line)) {
        if (line.empty()) {
            if (total > highest) highest = total;
            total = 0;
            continue;
        }
        total = total + stoi(line);
    }
    return highest;
}

int part_2() {
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

    int top = 0;
    for(int i = 0; i < 3; i++) {
        top = top + total_list.front();
        total_list.pop_front();
    }
    return top;
}


int main()
{
    cout << "Part 1: " << part_1() << endl;
    cout << "Part 2: " << part_2() << endl;
    return 0;
}