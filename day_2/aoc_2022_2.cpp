#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// PART 1 //
map<char, char> win_map;
map<char, char> draw_map;

// Working with maps here is pointless. However, I wanted to learn how maps work in c++.
void init_maps() {
    win_map['A'] = 'Y';
    win_map['B'] = 'Z';
    win_map['C'] = 'X';

    draw_map['A'] = 'X';
    draw_map['B'] = 'Y';
    draw_map['C'] = 'Z';
}

bool draw_1(char a, char b) {
    return (draw_map.at(a) == b);
}

bool win_1(char a, char b) {
    return (win_map.at(a) == b);
}

int calculate_score_1(char a, char b) {
    if (draw_1(a, b)) return 3;
    if (win_1(a, b)) return 6;
    else return 0;
}

int selection_bonus_1(char b) {
    if (b == 'X') return 1;
    if (b == 'Y') return 2;
    if (b == 'Z') return 3;
    else return 0;

}

int part_1() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int score = 0;
    string line;
    while (getline(fileStream, line))
    {
        char a = line[0];
        char b = line[2];
        score += calculate_score_1(a, b) + selection_bonus_1(b);
    }
    return score;
}


// PART 2 //
int lose_2(char a) {
    if (a == 'A') return 3;
    if (a == 'B') return 1;
    if (a == 'C') return 2;
    else return 0;
}

int draw_2(char a) {
    if (a == 'A') return 1;
    if (a == 'B') return 2;
    if (a == 'C') return 3;
    else return 0;
}

int win_2(char a) {
    if (a == 'A') return 2;
    if (a == 'B') return 3;
    if (a == 'C') return 1;
    else return 0;
}


int calculate_score_2(char b) {
    if (b == 'X') return 0;
    if (b == 'Y') return 3;
    if (b == 'Z') return 6;
    else return 0;
}

int selection_bonus_2(char a, char b) {
    if (b == 'X') return lose_2(a);
    if (b == 'Y') return draw_2(a);
    if (b == 'Z') return win_2(a);
    else return 0;

}

int part_2() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int score = 0;
    string line;
    while (getline(fileStream, line))
    {
        char a = line[0];
        char b = line[2];
        score += calculate_score_2(b) + selection_bonus_2(a, b);
    }
    return score;
}

int main()
{
    init_maps();
    cout << "Part 1: " << part_1() << endl;
    cout << "Part 2: " << part_2() << endl;
    return 0;
}