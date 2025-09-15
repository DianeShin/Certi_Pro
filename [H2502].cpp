#include <vector>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

#define MAX_CITY 1000
#define MAX_ROAD 2000

typedef pair<int, int> pii;

vector<vector<pii>> graph;
int N;

void init(int N, int K, int sCity[], int eCity[], int mLimit[]) {
	::N = N;

	vector<vector<pii>> new_graph(N);
	graph = new_graph;

	for (int i = 0; i < K; i++) {
		graph[sCity[i]].push_back(pii(eCity[i], mLimit[i]));
		graph[eCity[i]].push_back(pii(sCity[i], mLimit[i]));
	}

	return;
}

void add(int sCity, int eCity, int mLimit) {
	graph[sCity].push_back(pii(eCity, mLimit));
	graph[eCity].push_back(pii(sCity, mLimit));
	return;
}

int dijkstra(int start, vector<int> *stopover) {
    vector<int> dist(N, 0);
    priority_queue<pii, vector<pii>, less<pii>> pq; // greater : small to big

    dist[start] = INT_MAX;
    pq.push({ INT_MAX, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d < dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (min(dist[u], weight) > dist[v]) {
                dist[v] = min(dist[u], weight);
                pq.push({ dist[v], v });
            }
        }
    }

    int result = INT_MAX;

    for (int i = 0; i < stopover->size(); i++) {
        if (dist[stopover->at(i)] == 0) return -1;
        else result = min(result, dist[stopover->at(i)]);
    }

    return result;
}

int calculate(int sCity, int eCity, int M, int mStopover[]) {
    vector<int> stopover(mStopover, mStopover + M);
    stopover.push_back(eCity);
	return dijkstra(sCity, &stopover);
}