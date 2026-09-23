#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// include your swag() implementation here
#include "lab7_green.cpp"

template<typename T1, typename T2>
void print_map(const unordered_map<T1, T2>& m) {
    for (auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
    cout << "----------------------" << endl;
}

int main() {

    // ---------- NUMERIC TESTS ----------
    vector<pair<string, int>> nums = {
        {"a", 5}, {"a", 1}, {"a", 3},
        {"b", 10}, {"b", 2}
    };

    cout << "SUM (op=0)" << endl;
    print_map(swag(nums, 0));   // a=9, b=12

    cout << "MIN (op=1)" << endl;
    print_map(swag(nums, 1));   // a=1, b=2

    cout << "MEDIAN (op=2)" << endl;
    print_map(swag(nums, 2));   // a=3 (sorted: 1,3,5 → middle=3), b=2 (sorted: 2,10 → left middle=2)

    cout << "MAX (op=3)" << endl;
    print_map(swag(nums, 3));   // a=5, b=10


    // ---------- STRING TESTS ----------
    vector<pair<string, string>> strs = {
        {"x", "cat"}, {"x", "apple"}, {"x", "banana"},
        {"y", "dog"}, {"y", "ant"}
    };

    cout << "STRING SUM (concat) (op=0)" << endl;
    print_map(swag(strs, 0));   // x="catapplebanana" (order depends on input), y="dogant"

    cout << "STRING MIN (op=1)" << endl;
    print_map(swag(strs, 1));   // x="apple", y="ant"

    cout << "STRING MEDIAN (op=2)" << endl;
    print_map(swag(strs, 2));   // x="banana" (sorted: apple, banana, cat), y="ant" (sorted: ant, dog → left middle=ant)

    cout << "STRING MAX (op=3)" << endl;
    print_map(swag(strs, 3));   // x="cat", y="dog"

    return 0;
}
