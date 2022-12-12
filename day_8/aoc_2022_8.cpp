#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> create_matrix() {
    ifstream fileStream;
    fileStream.open("input.txt");

    vector<string> trees;
    string line;
    while(getline(fileStream, line)) {
        trees.push_back(line);
    }
    return trees;
}

vector<string> transpose_matrix(vector<string> trees) {
    vector<string> trees_T = trees;
    for (int i = 0; i < trees.size(); ++i)
        for (int j = 0; j < trees[0].size(); ++j)
            trees_T[j][i] = trees[i][j];
    return trees_T;
}

bool is_visible(string sub_row, char target) {
    for (char tree: sub_row)
        if (tree >= target) return false;
    return true;
}

int scenic_score(string sub_row, char target) {
    int score = 0;
    for (char tree : sub_row)
        if (tree >= target) return ++score;
        else score++;
    return score;
}

string rev(string str){
    reverse(str.begin(), str.end());
    return str;
}

int main() {
    vector<string> trees = create_matrix();
    vector<string> trees_T = transpose_matrix(trees);

    int m = trees.size();
    int n = trees_T.size(); // m x n matrix
    int visible = 2*m + 2*n - 4;
    int hi_score = 0;

    for (int i = 1; i < m-1; i++)
        for (int j = 1; j < n-1; j++) {
            visible += (is_visible(trees[i].substr(0, j), trees[i][j])          //left
            || (is_visible(trees[i].substr(j+1), trees[i][j]))                  //right
            || (is_visible(trees_T[j].substr(0, i), trees_T[j][i]))             //top
            || (is_visible(trees_T[j].substr(i+1), trees_T[j][i])));            //bottom;

            int score = (scenic_score(rev(trees[i].substr(0, j)), trees[i][j])  //left
            * (scenic_score(trees[i].substr(j+1), trees[i][j]))                 //right
            * (scenic_score(rev(trees_T[j].substr(0, i)), trees_T[j][i]))       //top
            * (scenic_score(trees_T[j].substr(i+1), trees_T[j][i]))             //bottom
            );
            if (score > hi_score) hi_score = score;
        }
    cout << "Part 1: " << visible << endl;
    cout << "Part 2: " << hi_score << endl;
}
