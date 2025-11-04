#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int arr[10];
vector<string> str_vect = { "ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN" };
int main() {
    int T;
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++) {
        int num, length;
        cin >> num >> length;
        int result;

        for (int i = 0; i < 10; i++) {
            arr[i] = 0;
        }

        string temp;
        getline(cin, temp);
        getline(cin, temp); // read the whole line, including spaces

        for (int i = 0; i + 2 < temp.size(); i += 4) { // +4 because of the space between
            string chunk = temp.substr(i, 3);
            auto it = find(str_vect.begin(), str_vect.end(), chunk);
            int index = distance(str_vect.begin(), it);
            arr[index]++;
        }

        cout << "#" << num << endl;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < arr[i]; j++) {
                cout << str_vect[i] << ' ';
            }
        }
        cout << endl;
    }

    return 0;
}
