#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int substr_compare(string substr) {
    for (int i = 0; i < substr.length(); i++)
        for (int j = i+1; j < substr.length(); j++)
            if (substr[i] == substr[j]) return i;
    return -1;
}

int system(int size) {
    ifstream fileStream;
    fileStream.open("input.txt");
    string line;
    getline(fileStream, line); 
    int i = 0, c;
    while (true) {
        c = substr_compare(line.substr(i, size));
        if (c == -1) return i+size;
        if (c > -1)  i = i+c+1;
    }
}

int main() {
        cout << "Part 1: " << system(4) << endl;
        cout << "Part 2: " << system(14) << endl;
}
