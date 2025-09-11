#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef pair<int, int> pii;
vector<vector<pii>> graph;
int N;

void init(int N, int K, int sCity[], int eCity[], int mLimit[]) {
    vector<vector<pii>> new_graph(N);
    graph = new_graph;

	::N = N;
	for (int i = 0; i < K; i++) {
        graph[sCity[i]].push_back(pii(eCity[i], mLimit[i]));
    }
	return;
}

void add(int sCity, int eCity, int mLimit) {
    graph[sCity].push_back(pii(eCity, mLimit));
	return;
}

int dijkstra(int sCity, int eCity) {
    vector<int> dist;
    dist.assign(N, 0);
    priority_queue<pii, vector<pii>, less<pii>> pq; // big to small.

    dist[sCity] = 0;
    pq.push({ INT_MAX, sCity });

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d < dist[u]) continue; // new path can shift less than known path -> continue

        for (pii it : graph[u]) {
            int w = it.second; // max weight from u to v

            if (w != 0 &&  min(d, w) > dist[it.first]) { // Check if there's an edge and if a shorter path is found
                dist[it.first] = min(d,w);
                pq.push({ dist[it.first], it.first });
            }
        }
    }

    return dist[eCity];
}

int calculate(int sCity, int eCity) {
	int result;
	result = dijkstra(sCity, eCity);
    if (result == 0) return -1;
    else return result;
}