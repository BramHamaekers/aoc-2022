#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int cycle = 0;
int x = 1;
int signal_strenght = 0;
stringstream render;

void draw() {
    render << ((abs(((cycle-1) % 40)-x) < 2) ? "#" : " ");
    if ((cycle % 40) == 0) render << endl;
}

void tick_cycle() {
    cycle++;
    if ((cycle - 20) % 40 == 0) signal_strenght += x * cycle;
    draw();
}

void noop() {
    tick_cycle();
}

void addx (int addx) {
    tick_cycle();
    tick_cycle();
    x += addx;
}

int main() {
    ifstream fileStream;
    fileStream.open("input.txt");
    string line;
    while(getline(fileStream, line))
        (line == "noop") ? noop() : addx(stoi(line.substr(5)));
    cout << "Part 1: " << signal_strenght << endl;
    cout << "Part 2: " << endl << render.str() << endl;
}
