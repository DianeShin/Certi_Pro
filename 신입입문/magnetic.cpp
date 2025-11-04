#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int board[100][100];

int main() {
    for (int test_case = 1; test_case <= 10; test_case++) {
        int temp;
        cin >> temp;
        
        int result = 0;

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                cin >> board[i][j];
            }
        }
        for (int j = 0; j < 100; j++) {
            bool stuck = false;
            for (int i = 0; i < 100; i++) {
                if (stuck) {
                    if (board[i][j] == 1) continue;
                    else if (board[i][j] == 2) {
                        result++;
                        stuck = false;
                    }
                }
                else {
                    if (board[i][j] == 2) continue;
                    else if (board[i][j] == 1) {
                        stuck = true;
                    }
                }
            }
        }

        cout << "#" << test_case << " " << result << endl;
    }

    return 0;
}
