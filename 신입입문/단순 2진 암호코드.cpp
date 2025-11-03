#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ZERO 0b00110
#define ONE 0b01100
#define TWO 0b01001
#define THREE 0b11110
#define FOUR 0b10001
#define FIVE 0b11000
#define SIX 0b10111
#define SEVEN 0b11101
#define EIGHT 0b11011
#define NINE 0b00101

int main(void) {
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		int result = 0;
		int row, col;
		cin >> row >> col;
		vector<int> code(col, 0);
		bool flag = false;
		int start;
		int end;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				char input_temp;
				cin >> input_temp;
				int temp = input_temp - '0';
				if (temp == 1) {
					if (!flag) {
						flag = true;
					}
					code[j] = 1;
					end = j;
				}
			}
		}

		start = end - 55;
		int even_sum = 0;
		int odd_sum = 0;
		for (int i = 0; i < 8; i++) {
			int res = 0;
			res |= (code[start + 7 * i + 1]) << 4;
			res |= (code[start + 7 * i + 2]) << 3;
			res |= (code[start + 7 * i + 3]) << 2;
			res |= (code[start + 7 * i + 4]) << 1;
			res |= (code[start + 7 * i + 5]) << 0;
			
			// find number
			if (res == ZERO) res = 0;
			else if (res == ONE) res = 1;
			else if (res == TWO) res = 2;
			else if (res == THREE) res = 3;
			else if (res == FOUR) res = 4;
			else if (res == FIVE) res = 5;
			else if (res == SIX) res = 6;
			else if (res == SEVEN) res = 7;
			else if (res == EIGHT) res = 8;
			else if (res == NINE) res = 9;

			// add
			if (i % 2 == 0) { // odd digit
				odd_sum += res;
			}
			else {
				even_sum += res;
			}
		}

		if ((odd_sum * 3 + even_sum) % 10 == 0) {
			result += odd_sum + even_sum;
		}

		cout << "#" << test_case << " " << result << endl;

	}
	return 0;
}