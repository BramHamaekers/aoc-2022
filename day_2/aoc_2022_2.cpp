#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int calculate_score_1(char a, char b) {
    if (b == 'X') return 3*(a == 'A') + 6*(a == 'C') + 1; // rock
    if (b == 'Y') return 3*(a == 'B') + 6*(a == 'A') + 2; // paper
    if (b == 'Z') return 3*(a == 'C') + 6*(a == 'B') + 3; // scissors
    else return 0; 
}

int calculate_score_2(char a, char b) {
    if (b == 'X') return (a == 'B') + 2*(a == 'C') + 3*(a == 'A') + 0; // lose
    if (b == 'Y') return (a == 'A') + 2*(a == 'B') + 3*(a == 'C') + 3; // draw
    if (b == 'Z') return (a == 'C') + 2*(a == 'A') + 3*(a == 'B') + 6; // win
    else return 0;
}

int main() {
    ifstream fileStream;
    fileStream.open("input.txt");

    int score_1 = 0;
    int score_2 = 0;
    string line;
    while (getline(fileStream, line)) {
        char a = line[0];
        char b = line[2];
        score_1 += calculate_score_1(a, b);
        score_2 += calculate_score_2(a, b);
    }
    cout << "Part 1: " << score_1 << endl;
    cout << "Part 2: " << score_2 << endl;
    return 0;
}