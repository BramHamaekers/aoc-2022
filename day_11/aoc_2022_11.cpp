#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <queue>
using namespace std;
long long flag = 1;
long long lcm = 1;

class Monkey {
    public:
        queue<long long> items;
        function<long long(long long)> func;
        long long test;
        long long T;
        long long F;
        long long inspect_ctr=0;

        Monkey(queue<long long> _items, function<long long(long long)> _func, long long _test, long long _T, long long _F) {
            items = _items;
            func = _func;
            test = _test;
            T = _T;
            F = _F;
        }

        long long inspect() {
            inspect_ctr++;
            long long item = items.front();
            items.pop();
            if (flag == 1) item = func(item)/3;
            return item;
        }
};

queue<long long> parse_items (string items_str) {
    queue<long long> items;
    stringstream ss(items_str);
    long long item;
    while (ss >> item) {
        items.push(item);
        if (ss.peek() == ',') ss.ignore();
    } return items;
}

long long add(long long a, long long b) { return a + b; }
long long multiply(long long a, long long b) { return a * b; }

function<long long(long long)> string_to_lambda (string lambda_str) {
    function fn = (lambda_str[4] == '+') ? add : multiply;
    if (lambda_str.substr(6) == "old") return [=](long long x) -> long long {return fn(x,x);};
    return [=](long long x) -> long long {return fn(x,stoi(lambda_str.substr(6)));};
}

vector<Monkey> parse_monkeys() {
    ifstream fileStream;
    fileStream.open("input.txt");
    long long line_ctr = 0;
    vector<Monkey> monkeys;
    queue<long long> items;
    function<long long(long long)> func;
    long long test; long long T; long long F;
    string line;
    while(getline(fileStream, line)) {
        if (line_ctr % 7 == 1) items = parse_items(line.substr(18));
        else if (line_ctr % 7 == 2) func = string_to_lambda(line.substr(19));
        else if (line_ctr % 7 == 3) test = stoi(line.substr(21));
        else if (line_ctr % 7 == 4) T = stoi(line.substr(29));
        else if (line_ctr % 7 == 5) F = stoi(line.substr(30));
        else if (line_ctr % 7 == 6) monkeys.push_back(Monkey(items, func, test, T, F));
        line_ctr++; 
    } monkeys.push_back(Monkey(items, func, test, T, F));
    return monkeys;
}

vector<Monkey> round(vector<Monkey> monkeys) {
    for (long long i = 0; i < monkeys.size(); i++) {
        Monkey monkey = monkeys[i];
        while (!monkey.items.empty()) {
            long long item = monkey.inspect();
            if ((item % lcm) % monkey.test == 0) monkeys[monkey.T].items.push(item);
            else monkeys[monkey.F].items.push(item);
        } monkeys[i] = monkey;
    } return monkeys;
}

int main() {
    vector<Monkey> monkeys = parse_monkeys();
    vector<long long> inspects;
    for (Monkey monkey : monkeys) lcm *= monkey.test; //lcm for part 2 but it doesn't work for some reason
    
    long long rounds = 20;
    while (rounds-- > 0) monkeys = round(monkeys);
    
    for (Monkey monkey : monkeys) inspects.push_back(monkey.inspect_ctr);
    sort(inspects.rbegin(), inspects.rend());
    cout << "Part 1: " << inspects[0] * inspects[1] << endl;
}
