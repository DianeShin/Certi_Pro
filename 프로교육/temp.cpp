#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<int>> graph;
int N;
unordered_map<int, int> IDLen;
unordered_map<int, int> IDDest;
unordered_map<int, int> IDSource;

void init(int N)
{
	::N;
	vector<vector<int>> new_graph(N);
	graph = new_graph;
	IDLen.clear();
	IDDest.clear();
	IDSource.clear();
}

void addRoad(int K, int mID[], int mSpotA[], int mSpotB[], int mLen[])
{
	for (int i = 0; i < K; i++) {
		graph[mSpotA[i]].push_back(mID[i]);
		graph[mSpotB[i]].push_back(mID[i]);
		IDLen[mID[i]] = mLen[i];
		IDDest[mID[i]] = mSpotB[i];
		IDSource[mID[i]] = mSpotA[i];
	}
}

void removeRoad(int mID) // vector에서는 지우지 말고, map에서만 지우는 것도 좋은 생각.
{
	if (IDLen.find(mID) != IDLen.end()) {
		int start = IDSource[mID];
		int end = IDDest[mID];
		IDLen.erase(mID);
		IDDest.erase(mID);
	}
}

void dfs()
{
}

int getLength(int mSpot)
{
	
}

/*
* @file: [H2516][Pro] 마라톤 코스
  
* @brief: 모범 답안
  
* @copyright: All rights reserved (c) 2025 Samsung Electronics, Inc.
*/
 
 
#include <unordered_map>
#include <vector>
using namespace std;
 
#define PII        pair<int,int>
#define PIII    pair<int,PII>
 
#define MAXLEN    42195
 
struct {
    vector <PII> rids;
    vector <PIII> paths;    //len, rid0 + rid1, rid2 + rid3
} Node[1001];
 
struct {
    int active;
    int visit;
    int na, nb;
    int len;
} Road[5000];
int rcnt;
 
unordered_map<int, int> roadIDs;
 
int startNID, maxLength;
int runPath[10];
int N;
 
void init(int _N)
{
    N = _N;
    for (int i = 1; i <= N; i++) {
        Node[i].rids.clear();
    }
 
    roadIDs.clear();
    rcnt = 0;
}
 
void addRoad(int K, int mID[], int mSpotA[], int mSpotB[], int mLen[])
{
    for (int i = 0; i < K; i++) {
        int rid = rcnt++;
        roadIDs[mID[i]] = rid;
 
        Road[rid].active = 1;
        Road[rid].visit = 0;
        Road[rid].na = mSpotA[i];
        Road[rid].nb = mSpotB[i];
        Road[rid].len = mLen[i];
 
        Node[mSpotA[i]].rids.push_back({ rid, mSpotB[i] });
        Node[mSpotB[i]].rids.push_back({ rid, mSpotA[i] });
    }
}
 
void removeRoad(int mID)
{
    if (roadIDs.find(mID) == roadIDs.end())
        return;
 
    int rid = roadIDs[mID];
    Road[rid].active = 0;
}
 
int check_rids(int rids[])
{
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            if (runPath[i] == rids[k]) return 0;
        }
    }
    return 1;
}
 
void calc_length(int nid, int len)
{
    for (PIII it : Node[nid].paths) {
        int maxlen = it.first + len;
        if (MAXLEN < maxlen || maxlen <= maxLength) continue;
 
        int check[4];
        check[0] = it.second.first >> 16;
        check[1] = it.second.first & 0xffff;
        check[2] = it.second.second >> 16;
        check[3] = it.second.second & 0xffff;
 
        if (check_rids(check) == 0) continue;
 
        maxLength = maxlen;
    }
}
 
void dfs(int nid, int cnt, int len)
{
    if (cnt == 4) {
        calc_length(nid, len);
        Node[nid].paths.push_back({ len, {(runPath[0] << 16) + runPath[1], (runPath[2] << 16) + runPath[3]} });
        return;
    }
 
    for (PII it : Node[nid].rids) {
        int rid = it.first;
        int next_nid = it.second;
 
        if (next_nid == startNID || Road[rid].active == 0 || Road[rid].visit == 1) continue;
        runPath[cnt] = rid;
 
        Road[rid].visit = 1;
        dfs(next_nid, cnt + 1, len + Road[rid].len);
        Road[rid].visit = 0;
    }
}
 
int getLength(int mSpot)
{
    for (int i = 1; i <= N; i++) {
        Node[i].paths.clear();
    }
    for (int i = 0; i < rcnt; i++) {
        Road[i].visit = 0;
    }
 
    startNID = mSpot;
    maxLength = -1;
 
    dfs(mSpot, 0, 0);
 
    return maxLength;
}