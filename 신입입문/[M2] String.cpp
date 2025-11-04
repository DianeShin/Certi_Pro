#include <iostream>
#include <string>
using namespace std;

int main() {
    for (int test_case = 1; test_case <= 10; test_case++) {
        int temp;
        cin >> temp;
        string search_target, input;
        cin >> search_target >> input;

        int result = 0;
        size_t pos = 0;

        while ((pos = input.find(search_target, pos)) != string::npos) {
            result++;
            pos += search_target.size();
        }

        cout << "#" << test_case << " " << result << endl;
    }
    return 0;
}
