#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(void) {
	int test_case;
	int T;
	cin >> T;
	vector<int> group;
	for (test_case = 1; test_case <= T; ++test_case) {
		group.clear();
		int N;
		cin >> N;
		int result = 0;
		for (int i = 0; i < N; i++) {
			int temp;
			cin >> temp;
			group.push_back(temp);

			if (i <= 3) {
				continue;
			}

			else {
				if (i != 4) {
					group.erase(group.begin());
				}
				int a = max(group[0], group[1]);
				int b = max(group[3], group[4]);
				int max_building = max(a, b);
				int res = group[2] - max_building;
				if (res > 0) result += res;
			}
		}
		cout << "#" << test_case << " " << result << endl;
	}
	return 0;
}