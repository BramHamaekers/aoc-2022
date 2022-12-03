#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int get_priority(int item_type) {
    if (item_type > 96) return item_type - 96;
    else return item_type - 38;
}

char find_common_item(vector<string> strings) {
    for (string &str : strings) {
        sort(str.begin(), str.end());
    }
    string item;
    for (string str : strings) {
        if (item.empty()) item = str;
        else {
            string tmp;
            set_intersection(item.begin(), item.end(), str.begin(), str.end(), inserter(tmp, tmp.begin()));
            item = tmp;
        }
    }
    return item[0];
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
        item_sum += get_priority(find_common_item({a, b}));

        counter++;
        lines.push_back(line);
        if (counter == 3) {
            badge_sum += get_priority(find_common_item(lines));
            lines.clear();
            counter = 0;
        }
    }
    cout << "Part 1: " << item_sum << endl;
    cout << "Part 2: " << badge_sum << endl;
    return 0;
}