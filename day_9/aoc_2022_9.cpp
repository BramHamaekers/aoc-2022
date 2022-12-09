#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

struct Knod {
    int x;
    int y;
    Knod* next;
};
set<pair<int,int>> pos;

bool adjacent(Knod &head, Knod &tail) {
    return (abs(head.x - tail.x) < 2) && (abs(head.y - tail.y) < 2);
}

void adjust(Knod &head, Knod &tail) {
    if (adjacent(head, tail)) return;
    if (head.x == tail.x) tail.y += (head.y > tail.y) ? 1 : -1;
    else if (head.y == tail.y) tail.x += (head.x > tail.x) ? 1 : -1;
    else if (head.x > tail.x) {
        tail.x++;
        tail.y += (head.y > tail.y) ? 1 : -1;
    }
    else if (head.x < tail.x) {
        tail.x--;
        tail.y += (head.y > tail.y) ? 1 : -1;
    }
    if(tail.next) adjust(tail, *tail.next);
    else pos.insert(pair{tail.x, tail.y});
}

void move(char dir, int d, Knod &head) {
    while(d-- > 0) {
        if (dir == 'R') head.x++;
        if (dir == 'L') head.x--;
        if (dir == 'U') head.y++;
        if (dir == 'D') head.y--;
        if (head.next) adjust(head, *head.next);
    }
}

Knod* rope(int n) {
    pos.clear();
    pos.insert(pair{0,0});
    Knod* head = new Knod{0,0,nullptr};
    Knod* cur = head;
    for (int i = 1; i < n; i++) {
        cur->next = new Knod{0,0,nullptr};
        cur = cur->next;
    } return head;
}

int find_positions(int n) {
    ifstream fileStream;
    fileStream.open("input.txt");
    Knod* head = rope(n);
    string line;
    while(getline(fileStream, line)) {
        move(line[0],stoi(line.substr(2)), *head);
    } return pos.size();
    
}

int main() {
        cout << "Part 1: " << find_positions(2) << endl;
        cout << "Part 2: " << find_positions(10) << endl;
}
