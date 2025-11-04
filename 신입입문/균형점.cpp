#include <vector>
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;


double findBalance(const vector<double>& x, const vector<double>& m, int i) {
    // Initial guess: weighted midpoint between x[i] and x[i+1]
    double lo = x[i], hi = x[i + 1];
    double xi = (x[i] * m[i + 1] + x[i + 1] * m[i]) / (m[i] + m[i + 1]);
    double x0 = xi;

    while (true) {
        double f = 0, df = 0;

        // Left 
        for (int j = 0; j <= i; j++) {
            double d = x0 - x[j];
            f += m[j] / (d * d);
            df += -2.0 * m[j] / (d * d * d);
        }

        // Right 
        for (int j = i + 1; j < x.size(); j++) {
            double d = x[j] - x0;
            f -= m[j] / (d * d);
            df += -2.0 * m[j] / (d * d * d);
        }

        double x1 = x0 - f / df;
        if (fabs(x1 - x0) < 1e-13) break; // stop when within 1e-12
        x0 = x1;
    }
    return x0;
}

int main() {
    int T;
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;

        vector<double> x_list(N), m_list(N);
        for (int i = 0; i < N; i++) cin >> x_list[i];
        for (int i = 0; i < N; i++) cin >> m_list[i];

        cout << "#" << test_case;
        for (int i = 0; i < N - 1; i++) {
            double bp = findBalance(x_list, m_list, i);
            cout << " " << fixed << setprecision(10) << bp;
        }
        cout << "\n";
    }
}
