#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int maxPrize;
unordered_set<string> visited[11];

void dfs(string num, int cnt) {
    if (cnt == 0) {
        maxPrize = max(maxPrize, stoi(num));
        return;
    }

    // visited
    if (visited[cnt].count(num)) return;
    visited[cnt].insert(num);

    int len = num.size();
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            swap(num[i], num[j]);
            dfs(num, cnt - 1);
            swap(num[i], num[j]);
        }
    }
}

int main() {
    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++) {
        string num;
        int K;
        cin >> num >> K;

        maxPrize = 0;

        for (int i = 0; i <= K; i++) visited[i].clear();

        dfs(num, K);

        cout << "#" << test_case << " " << maxPrize << endl;
    }

    return 0;
}
