#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <unordered_map>
#include <algorithm>

#define MAX_N 1000
#define MAX_K 5000

using namespace std;

int graph[MAX_N][MAX_N];
int city_num;
unordered_map<int, pair<int, int>> mID_map;

void init(int N, int K, int mId[], int sCity[], int eCity[], int mTime[]) {
	// init
	city_num = N;
	for (int row = 0; row < city_num; row++) {
		for (int col = 0; col < city_num; col++) {
			graph[row][col] = 0;
		}
	}

	// fill in roads
	for (int i = 0; i < K; i++) {
		graph[sCity[i]][eCity[i]] = mTime[i];
		mID_map[mId[i]] = make_pair(sCity[i], eCity[i]);
	}
	return;
}

void add(int mId, int sCity, int eCity, int mTime) {
	graph[sCity][eCity] = mTime;
	mID_map[mId] = make_pair(sCity, eCity);
	return;
}

void remove(int mId) {
	auto it = mID_map.find(mId);
	graph[it->second.first][it->second.second] = 0;
	mID_map.erase(mId);
	return;
}

int dijkstra(int sCity, int eCity) {
	vector<int> dist(city_num, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	dist[sCity] = 0;
	pq.push({ 0, sCity });

	while (!pq.empty()) {
		int currentDist = pq.top().first;
		int currentNode = pq.top().second;
		pq.pop();

		if (currentNode == eCity) {
			return currentDist;
		}

		if (currentDist > dist[currentNode]) {
			continue;
		}

		for (int i = 0; i < city_num; i++) {
			if (graph[currentNode][i]) {
				int nextNode = i;
				int nextDist = graph[currentNode][i];
				if (dist[currentNode] + nextDist < dist[nextNode]) {
					dist[nextNode] = dist[currentNode] + nextDist;
					pq.push({ dist[nextNode], nextNode });
				}
			}
		}
	}
	return -1; // If no path exists
}

// Function to find the path using Dijkstra's algorithm
vector<pair<int, int>> findPath(int sCity, int eCity) {
	vector<int> dist(city_num, INT_MAX);
	vector<pair<int, int>> parent(city_num, { -1, -1 }); // To track the path as pairs
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	dist[sCity] = 0;
	pq.push({ 0, sCity });

	while (!pq.empty()) {
		int currentDist = pq.top().first;
		int currentNode = pq.top().second;
		pq.pop();

		if (currentNode == eCity) {
			// Reconstruct the path
			vector<pair<int, int>> path;
			for (int at = eCity; at != -1; at = parent[at].first) {
				if (parent[at].second != -1) {
					path.push_back({ parent[at].first, parent[at].second });
				}
			}
			reverse(path.begin(), path.end());
			return path;
		}

		if (currentDist > dist[currentNode]) {
			continue;
		}

		for (int i = 0; i < city_num; i++) {
			if (graph[currentNode][i]) {
				int nextNode = i;
				int nextDist = graph[currentNode][i];
				if (dist[currentNode] + nextDist < dist[nextNode]) {
					dist[nextNode] = dist[currentNode] + nextDist;
					parent[nextNode] = { currentNode, nextNode }; // Update parent
					pq.push({ dist[nextNode], nextNode });
				}
			}
		}
	}

	return {}; // If no path exists
}

int calculate(int sCity, int eCity) {
	// Step 1: Find the shortest path
	vector<pair<int, int>> path = findPath(sCity, eCity);
	if (path.empty()) return -1; // No path exists

	// Step 2: Calculate the original shortest path distance
	int originalDistance = 0;
	for (const auto& edge : path) {
		originalDistance += graph[edge.first][edge.second];
	}

	// Step 3: Try removing each road in the path and recalculate
	int maxIncrease = 0;
	for (const auto& edge : path) {
		int u = edge.first;
		int v = edge.second;

		// Remove the road
		int temp_road_weight = graph[u][v];
		graph[u][v] = 0;

		// Recalculate the shortest path
		int newDistance = dijkstra(sCity, eCity);

		// Restore the road
		graph[u][v] = temp_road_weight;
			
		// Calculate the increase in distance
		if (newDistance == -1) return -1; // cannot go
		else if (newDistance - originalDistance > maxIncrease) {
			maxIncrease = newDistance - originalDistance;
		}
	}

	return maxIncrease;
}