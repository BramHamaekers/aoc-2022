#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <tuple>

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

vector<SuplyStack> parse_stacks(ifstream &fileStream){
    vector<SuplyStack> stacks(9);
    string line;
    while (getline(fileStream, line)) {
        if (line.empty()) break;
        if (line[1] == '1') continue;
        for (int i=1; i<=1+(9-1)*4; i+=4) {
            if (line[i] == ' ') continue;
            stacks[i/4].crates.push_back(line[i]);
        }
    }
    return stacks;
}

tuple<int, int, int> parse_command(string line) {
    return make_tuple(
        atoi(&line[5]),
        atoi(&line[12])-1,
        atoi(&line[17])-1
    );
}

void part_1() {
    ifstream fileStream;
    fileStream.open("input.txt");
    string line;
    vector<SuplyStack> stacks = parse_stacks(fileStream);
    while (getline(fileStream, line)) {
        int n, from, to;
        tie(n, from, to) = parse_command(line);
        stacks[from].move_single(n, stacks[to]);
    } for (SuplyStack stack : stacks) cout << stack.crates.front();
}

void part_2() {
    ifstream fileStream;
    fileStream.open("input.txt");
    string line;
    vector<SuplyStack> stacks = parse_stacks(fileStream);
    while (getline(fileStream, line)) {
        int n, from, to;
        tie(n, from, to) = parse_command(line);
        stacks[from].move_multiple(n, stacks[to]);
    } for (SuplyStack stack : stacks) cout << stack.crates.front(); 
}

int main() {
        cout << "Part 1: "; part_1(); cout << endl;
        cout << "Part 2: "; part_2(); cout << endl;
}
