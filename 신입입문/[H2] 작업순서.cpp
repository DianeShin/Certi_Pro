#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    for (int test_case = 1; test_case <= 10; test_case++) {
        // input
        int V, E;
        cin >> V >> E;
        int start, end;
        vector<vector<int>> graph(V+1);
        vector<int> degree(V + 1, 0);
        for (int i = 0; i < E; i++) {
            cin >> start >> end;
            graph[start].push_back(end);
            degree[end]++;
        }

        // calculate
        queue<int> q;
        for (int i = 1; i <= V; i++) {
            if (degree[i] == 0) q.push(i);
        }
        vector<int> result;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            result.push_back(curr);

            // pre-requisite resolved
            for (int elem : graph[curr]) {
                degree[elem]--;
                if (degree[elem] == 0) q.push(elem);
            }
        }

        // print
        cout << "#" << test_case << " ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
