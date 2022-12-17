#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <limits>

using namespace std;

pair<int, int> S;
pair<int, int> E;

pair<int, int> find_best_node(map<pair<int, int>, int> g_score, set<pair<int,int>> open_set) {
    pair<int, int> best;
    int best_value = numeric_limits<int>:: max();
    for (pair<int, int> node : open_set) {
        if (g_score[node] < best_value) {
            best_value = g_score[node];
            best = node;
        }
    } return best;
}

vector<pair<int, int>> get_neighbours(pair<int, int> node, vector<string> heightmap) {
    int i = node.first; 
    int j = node.second;
    int m = heightmap.size() - 1;
    int n = heightmap[0].size() - 1;
    vector<pair<int, int>> neighbours;
    if ((i != 0) && (heightmap[i-1][j] - heightmap[i][j] < 2)) neighbours.push_back(pair(i-1, j)); // UP
    if ((i != m) && (heightmap[i+1][j] - heightmap[i][j] < 2)) neighbours.push_back(pair(i+1, j)); // DOWN 
    if ((j != 0) && (heightmap[i][j-1] - heightmap[i][j] < 2)) neighbours.push_back(pair(i, j-1)); // LEFT
    if ((j != n) && (heightmap[i][j+1] - heightmap[i][j] < 2)) neighbours.push_back(pair(i, j+1)); // RIGHT
    return neighbours;
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
int A_Star(vector<string> heightmap) {
    set<pair<int,int>> open_set;
    open_set.insert(S);

    map<pair<int, int>, int> g_score; // f_score(node) = g_score(node) + heuristic(node)
    g_score[S] = 0;

    while (!open_set.empty()) {
        pair <int, int> current = find_best_node(g_score, open_set);
        if (current == E) return g_score[current];

        open_set.erase(current);
        for (pair<int, int> neighbour : get_neighbours(current, heightmap)) {
            int tentative_g_score = g_score[current] + 1;
            if ((tentative_g_score < g_score[neighbour]) || ((g_score[neighbour] == 0) && (neighbour != S))) {
                g_score[neighbour] = tentative_g_score;
                if (open_set.find(neighbour) == open_set.end()) {
                    open_set.insert(neighbour);
                }
            }
        }
    } return 0; // error
}

bool has_b_neighbour(pair<int, int> node, vector<string> heightmap) {
    vector<pair<int, int>> neightbours = get_neighbours(node, heightmap);
    for (pair<int, int> n : neightbours) {
        if (heightmap[n.first][n.second] == 'b') return true;
    } return false;
}

set<pair<int, int>> find_all_a(vector<string> heightmap) {
    set<pair<int, int>> a_set;
    for (int i = 0; i < heightmap.size(); i++)
        for (int j=0; j < heightmap[0].size(); j++)
            if ((heightmap[i][j] == 'a') && (has_b_neighbour(pair(i, j), heightmap))) a_set.insert(pair(i,j));
    return a_set;
}

int shortest_from_a(vector<string> heightmap) {
    set<pair<int, int>> a_set = find_all_a(heightmap);
    int shortest = numeric_limits<int>:: max();
    for (pair<int, int> a : a_set) {
        S = pair(a.first, a.second);
        int path_len_a = A_Star(heightmap);
        if (path_len_a < shortest) {
            shortest = path_len_a;
        }
    } return shortest;
}

vector<string> get_heightmap() {
    ifstream fileStream;
    fileStream.open("input.txt");
    vector<string> heightmap;
    int i = 0;
    string line;
    while(getline(fileStream, line)) {
        heightmap.push_back(line);
        if (line.find('S') != string::npos) {
            S = pair(i, line.find('S'));
            heightmap[i][line.find('S')] = 'a';
        }
        if (line.find('E') != string::npos){
            E = pair(i, line.find('E'));
            heightmap[i][line.find('E')] = 'z';
        }
        i++;
    } return heightmap;
}

int main() {
    vector<string> heightmap = get_heightmap();
    cout << "Part 1: " << A_Star(heightmap) << endl;
    cout << "Part 2: " << shortest_from_a(heightmap) << endl;
}
