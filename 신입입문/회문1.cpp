#include <iostream>
#include <string>
using namespace std;

char board[8][8];

bool isPalindromeRow(int row, int start, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (board[row][start + i] != board[row][start + len - 1 - i])
            return false;
    }
    return true;
}

bool isPalindromeCol(int col, int start, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (board[start + i][col] != board[start + len - 1 - i][col])
            return false;
    }
    return true;
}

int main() {
    for (int test_case = 1; test_case <= 10; test_case++) {
        int length;
        cin >> length;

        for (int i = 0; i < 8; i++) {
            string temp;
            cin >> temp;
            for (int j = 0; j < 8; j++) {
                board[i][j] = temp[j];
            }
        }

        int result = 0;

        // Check rows
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j <= 8 - length; j++) {
                if (isPalindromeRow(i, j, length)) result++;
            }
        }

        // Check columns
        for (int j = 0; j < 8; j++) {
            for (int i = 0; i <= 8 - length; i++) {
                if (isPalindromeCol(j, i, length)) result++;
            }
        }

        cout << "#" << test_case << " " << result << endl;
    }

    return 0;
}
