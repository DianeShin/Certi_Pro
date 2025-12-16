/*
     
* @file: [H2522][Pro] 도로 파괴
     
* @brief: 모범 답안 
    
* @copyright: All rights reserved (c) 2025 Samsung Electronics, Inc. 
    
*/
 
 
 
 
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>
 
 
using namespace std;
 
 
constexpr int MAX_N = 1000;
constexpr int INF = 0x7f7f7f7f;
 
 
typedef unsigned long long ull;
 
 
unordered_map<int, int> Hash;
vector<ull> Graph[MAX_N];
int PrevNode[MAX_N], PrevRoad[MAX_N];
 
 
int dijkstra(int src, int dst) {
    int dist[MAX_N];
    memset(dist, 0x7f, sizeof(dist));
    memset(PrevNode, -1, sizeof(PrevNode));
 
 
    priority_queue<int, vector<int>, greater<int>> pq;
 
 
    dist[src] = 0;
    pq.emplace(src);
 
 
    while (!pq.empty()) {
        int currCost = pq.top() >> 10;
        int u = pq.top() & 0x3ff;
        pq.pop();
 
 
        if (dist[u] < currCost) continue;
        if (u == dst) return currCost;
 
 
        for (auto val : Graph[u]) {
            int v = val >> 48;
            int nextCost = currCost + (val >> 32) & 0xffff;
 
 
            if (dist[v] > nextCost) {
                dist[v] = nextCost;
                PrevNode[v] = u;
                PrevRoad[v] = val & 0xffffffff;
                pq.emplace(nextCost << 10 | v);
            }
        }
    }
    return INF;
}
 
 
int dijkstraExclude(int src, int dst, int excludedId) {
    int dist[MAX_N];
    memset(dist, 0x7f, sizeof(dist));
 
 
    priority_queue<int, vector<int>, greater<int>> pq;
 
 
    dist[src] = 0;
    pq.emplace(src);
 
 
    while (!pq.empty()) {
        int currCost = pq.top() >> 10;
        int u = pq.top() & 0x3ff;
        pq.pop();
 
 
        if (dist[u] < currCost) continue;
        if (u == dst) return currCost;
 
 
        for (auto val : Graph[u]) {
            if (excludedId == (val & 0xffffffff)) continue;
 
 
            int v = val >> 48;
            int nextCost = currCost + (val >> 32) & 0xffff;
 
 
            if (dist[v] > nextCost) {
                dist[v] = nextCost;
                pq.emplace(nextCost << 10 | v);
            }
        }
    }
    return INF;
}
 
 
void init(int N, int K, int mId[], int sCity[], int eCity[], int mTime[]) {
    Hash.clear();
    for (int i = 0; i < N; ++i) {
        Graph[i].clear();
    }
    for (int i = 0; i < K; ++i) {
        Graph[sCity[i]].emplace_back((ull)eCity[i] << 48 | (ull)mTime[i] << 32 | mId[i]);
        Hash[mId[i]] = sCity[i];
    }
}
 
 
void add(int mId, int sCity, int eCity, int mTime) {
    Graph[sCity].emplace_back((ull)eCity << 48 | (ull)mTime << 32 | mId);
    Hash[mId] = sCity;
}
 
 
void remove(int mId) {
    int sCity = Hash[mId];
    for (int i = 0; i < Graph[sCity].size(); ++i) {
        if (mId == (Graph[sCity][i] & 0xffffffff)) {
            Graph[sCity].erase(Graph[sCity].begin() + i);
            return;
        }
    }
}
 
 
int calculate(int sCity, int eCity) {
    int dist = dijkstra(sCity, eCity);
    if (dist == INF) return -1;
 
 
    int curr = eCity;
    int maxDist = 0;
    while (PrevNode[curr] != -1) {
        int newDist = dijkstraExclude(sCity, eCity, PrevRoad[curr]);
        if (newDist == INF) return -1;
 
 
        maxDist = max(maxDist, newDist);
        curr = PrevNode[curr];
    }
 
 
    return maxDist - dist;
}