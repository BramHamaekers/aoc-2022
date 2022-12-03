#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

char find_item_type(string a, string b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    string item_type;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(item_type));
    return item_type[0];
}

int get_priority(int item_type) {
    if (item_type > 96) return item_type - 96;
    else return item_type - 38;
}

char find_badge(vector<string> lines) {
    sort(lines[0].begin(), lines[0].end());
    sort(lines[1].begin(), lines[1].end());
    sort(lines[2].begin(), lines[2].end());
    string temp, badge;
    set_intersection(lines[0].begin(), lines[0].end(), lines[1].begin(), lines[1].end(), back_inserter(temp));    
    set_intersection(temp.begin(), temp.end(), lines[2].begin(), lines[2].end(), back_inserter(badge));
    return badge[0];
}

int main() {
    ifstream fileStream;
    fileStream.open("input.txt");

    vector<string> lines;
    int counter = 0, item_sum = 0, badge_sum = 0;
    string line;
    while (getline(fileStream, line)) {
        string a = line.substr(0, line.length()/2);
        string b = line.substr(line.length()/2);
        item_sum += get_priority(find_item_type(a, b));

        counter++;
        lines.push_back(line);
        if (counter == 3) {
            badge_sum += get_priority(find_badge(lines));
            lines.clear();
            counter = 0;
        }
    }
    cout << "Part 1: " << item_sum << endl;
    cout << "Part 2: " << badge_sum << endl;
    return 0;
}