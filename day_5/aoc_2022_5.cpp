#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class SuplyStack {
    public:
        deque<char> crates;

        void move_single(int n, SuplyStack &stack) {
            for (int i = 0; i<n; i++) {
                stack.push(this->pop());
            }
        }

        void move_multiple(int n, SuplyStack &stack ) {
            stack.push_stack(this->pop_stack(n));
        }

        void push(char crate) {
            crates.push_front(crate);
        }

        void push_stack(deque<char> stack) {
            while(!stack.empty()) {
                this->push(stack.front());
                stack.pop_front();
            }
        }

    private:
        char pop() {
            char crate = crates.front();
            crates.pop_front();
            return crate;
        }

        deque<char> pop_stack(int n) {
            deque<char> stack;
            for (int i = 0; i<n; i++) {
                stack.push_front(this->pop());
            }
            return stack;
        }
};


void part_1() {
    ifstream fileStream;
    fileStream.open("input.txt");
    int num_of_stacks = 9; // Change Depending on the inputFile

    vector<SuplyStack> stacks(num_of_stacks);

    string line;
    while (getline(fileStream, line)) {

        if (line.empty()) break;
        if (line[1] == '1') continue;
        for (int i=1; i<=1+(num_of_stacks-1)*4; i+=4) {
            if (line[i] == ' ') continue;
            stacks[i/4].crates.push_back(line[i]);
        }
    }
    while (getline(fileStream, line)) {
        int n = atoi(&line[5]);
        int from = atoi(&line[12])-1;
        int to = atoi(&line[17])-1;
        stacks[from].move_single(n, stacks[to]);
    }
        for (SuplyStack stack : stacks) cout << stack.crates.front();
 
}

void part_2() {
    ifstream fileStream;
    fileStream.open("input.txt");
    int num_of_stacks = 9; // Change Depending on the inputFile

    vector<SuplyStack> stacks(num_of_stacks);

    string line;
    while (getline(fileStream, line)) {

        if (line.empty()) break;
        if (line[1] == '1') continue;
        for (int i=1; i<=1+(num_of_stacks-1)*4; i+=4) {
            if (line[i] == ' ') continue;
            stacks[i/4].crates.push_back(line[i]);
        }
    }
    while (getline(fileStream, line)) {
        int n = atoi(&line[5]);
        int from = atoi(&line[12])-1;
        int to = atoi(&line[17])-1;
        stacks[from].move_multiple(n, stacks[to]);
    }
        for (SuplyStack stack : stacks) cout << stack.crates.front();
 
}

int main() {
        cout << "Part 1: "; part_1(); cout << endl;
        cout << "Part 2: "; part_2(); cout << endl;
}
