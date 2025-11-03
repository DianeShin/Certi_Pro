#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

long long nCr(int n, int r) {
	if (r > n) return 0;
	long long res = 1;
	for (int i = 1; i <= r; ++i) {
		res = res * (n - i + 1) / i;
	}
	return res;
}


int main(void) {
	int test_case;
	int T;
	cin >> T;

	// Can make total of 18
	// 2 3 5 7 11 13 17
	// 1 - both make non prime
	vector<int> prime = { 2,3,5,7,11,13,17 };
	for (test_case = 1; test_case <= T; ++test_case) {
		float result = 0;
		int skillOfMasterA, skillOfMasterB;
		
		cin >> skillOfMasterA >> skillOfMasterB;

		float masterA_prob = (float) skillOfMasterA / 100;
		float masterB_prob = (float) skillOfMasterB / 100;

		// probability of A making prime
		float A_prime = 0.0; 
		float B_prime = 0.0;
		for (int num : prime) {
			A_prime += nCr(18, num) * pow(masterA_prob, num) * pow(1 - masterA_prob, 18 - num);
			B_prime += nCr(18, num) * pow(masterB_prob, num) * pow(1 - masterB_prob, 18 - num);
		}

		result = 1 - (1 - A_prime) * (1 - B_prime);
		cout << "#" << test_case << " " << fixed << setprecision(6) << result << endl;

	}

	return 0;
}