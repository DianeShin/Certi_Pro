#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int result = 0;

int main() {
    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        long long N, P;
        cin >> N >> P;

        long long q = N / P;
        long long r = N % P;

        long double result = pow(q + 1, r) * pow(q, P - r);

        cout << "#" << test_case << " " << fixed << (long long)result << endl;
    }
    return 0;
}
