#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class Entry {
    public:
        string type; // dir or file
        string name;
        unordered_set<Entry*> members;
        Entry* parent;

        Entry(string _type, string _name, int _size, Entry *_parent = nullptr) {
            type = _type;
            name = _name;
            members = {};
            parent = _parent;
            file_size = _size;
        }

        void add_member(Entry* child) {
            this->members.insert(child);
        }

        int size() {
            if (this->type == "file") return this->file_size;
            int dir_size = 0;
            for (Entry* member: members)
                dir_size += member->size();
            return dir_size;
        }
        
        private:
            int file_size;
};

Entry create_file_system() {
    ifstream fileStream;
    fileStream.open("input.txt");
    Entry root = Entry("dir", "/", 0);
    Entry* current = &root;
    string line;
    while(getline(fileStream, line))
        if (line == "$ cd /" || line.substr(2, 2) == "ls"); // Do nothing
        else if (line[0] != '$') { // Add new File
            string _name = line.substr(line.find(' ')+1);
            string _size = line.substr(0, line.find(' '));
            if (_size != "dir") current->add_member(new Entry("file", _name, stoi(_size), current));
        }
        else if (line.substr(5) == "..") current = current->parent; // Go to parent dir
        else {
        Entry *child = new Entry("dir", line.substr(5), 0, current);
        current->add_member(child);
        current = child;
        }
    return root; 
}

int sum_small_dirs(Entry &dir) {
    int sum = 0;
    for (Entry* member : dir.members) {
        if (member->type == "dir" && member->size() <= 100000) sum += member->size();
        sum += sum_small_dirs(*member);  
    } return sum;
}

vector<int> find_all_dir_sizes(Entry &root, vector<int> dir_sizes = {}) {
    if (root.type == "dir") dir_sizes.push_back(root.size());
    for (Entry* member : root.members)
        dir_sizes = find_all_dir_sizes(*member, dir_sizes);
    return dir_sizes;
}

int find_suitable_smallest(Entry dir) {
    int needed = 30000000 - (70000000 - dir.size());
    vector<int> dir_sizes = find_all_dir_sizes(dir);
    sort(dir_sizes.begin(), dir_sizes.end());
    for (int i : dir_sizes)
        if (i >= needed) return i;
    return 0;
}

int main() {
        Entry root = create_file_system();
        cout << "Part 1: " << sum_small_dirs(root) << endl;
        cout << "Part 2: " << find_suitable_smallest(root) << endl;
}
