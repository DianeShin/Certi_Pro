/*
* @file: [H2529][Pro] 스마트 팜
  
* @brief: 모범 답안
  
* @copyright: All rights reserved (c) 2025 Samsung Electronics, Inc.
*/
 
 
 
 
#define MAX_N 1000
#define MAX_PLANTS 100001
#define BUC_SIZE 20
#define INF -1000000000
 
 
#include <algorithm>
#include <vector>
 
 
using namespace std;
 
 
int N, GrouwthTime[3], plantcnt;
int mt[MAX_N / BUC_SIZE][MAX_N / BUC_SIZE][3], wt[MAX_N / BUC_SIZE][MAX_N / BUC_SIZE];
struct Plant {
    int r, c, time, category;
} plants[MAX_PLANTS];
vector<int> buc[MAX_N / BUC_SIZE][MAX_N / BUC_SIZE];
 
 
 
 
int purgeBucket(int rb, int cb) {
    int ret = buc[rb][cb].size();
    buc[rb][cb] = {}, wt[rb][cb] = 0;
    for (int c = 0; c < 3; ++c) mt[rb][cb][c] = INF;
    return ret;
}
 
 
 
 
void init(int N, int mGrowthTime[3]) {
    ::N = N, plantcnt = 0;
    for (int i = 0; i < 3; ++i) GrouwthTime[i] = mGrowthTime[i];
    for (int i = 0; i < MAX_N / BUC_SIZE; ++i)
        for (int j = 0; j < MAX_N / BUC_SIZE; ++j)
            purgeBucket(i, j);
}
 
 
 
 
int sow(int mTime, int mRow, int mCol, int mCategory) {
    int rb = mRow / BUC_SIZE, cb = mCol / BUC_SIZE;
    for (int idx : buc[rb][cb]) if (plants[idx].r == mRow && plants[idx].c == mCol) return 0;
 
 
    plants[plantcnt] = { mRow, mCol, mTime + wt[rb][cb] * GrouwthTime[mCategory], mCategory};
    buc[rb][cb].push_back(plantcnt++);
    mt[rb][cb][mCategory] = max(mt[rb][cb][mCategory], mTime + wt[rb][cb] * GrouwthTime[mCategory]);
    return 1;
}
 
 
 
 
int bucketWater(int G, int rb, int cb, int sr, int er, int sc, int ec) {
    int ret = 0;
    for (int i = 0; i < 3; ++i) mt[rb][cb][i] = INF;
 
 
    for (int pid : buc[rb][cb]) {
        if (sr <= plants[pid].r && plants[pid].r <= er && sc <= plants[pid].c && plants[pid].c <= ec) {
            plants[pid].time -= G * GrouwthTime[plants[pid].category];
            ret++;
        }
        mt[rb][cb][plants[pid].category] = max(mt[rb][cb][plants[pid].category], plants[pid].time);
    }
    return ret;
}
 
 
 
 
int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth) {
    int ret = 0;
    int sr = mRow, sc = mCol, er = mRow + mHeight - 1, ec = mCol + mWidth - 1;
    int srb = sr / BUC_SIZE, erb = er / BUC_SIZE, scb = sc / BUC_SIZE, ecb = ec / BUC_SIZE;
 
 
    for (int rb = srb + 1; rb < erb; ++rb) {
        for (int cb = scb + 1; cb < ecb; ++cb) {
            ret += buc[rb][cb].size();
            wt[rb][cb] += G;
        }
    }
 
 
    for (int rb = srb, cb = scb; rb <= erb; ++rb) ret += bucketWater(G, rb, cb, sr, er, sc, ec);
    if (scb != ecb)    for (int rb = srb, cb = ecb; rb <= erb; ++rb) ret += bucketWater(G, rb, cb, sr, er, sc, ec);
    for (int rb = srb, cb = scb + 1; cb < ecb; ++cb) ret += bucketWater(G, rb, cb, sr, er, sc, ec);
    if (srb != erb)    for (int rb = erb, cb = scb + 1; cb < ecb; ++cb) ret += bucketWater(G, rb, cb, sr, er, sc, ec);
 
 
    return ret;
}
 
 
 
 
bool isHarvestable(int mTime, int L[3], int rb, int cb, int sr, int er, int sc, int ec) {
    for (int pid : buc[rb][cb]) {
        if (er < plants[pid].r || plants[pid].r < sr || ec < plants[pid].c || plants[pid].c < sc) continue;
        if ((mTime - plants[pid].time + (wt[rb][cb] * GrouwthTime[plants[pid].category])) < L[plants[pid].category]) return false;
    }
    return true;
}
 
 
 
 
int bucketHarvest(int rb, int cb, int sr, int er, int sc, int ec) {
    int ret = 0;
    for (int c = 0; c < 3; ++c) mt[rb][cb][c] = INF;
 
 
    for(auto it = buc[rb][cb].begin(); it!= buc[rb][cb].end();) {
        if (er < plants[*it].r || plants[*it].r < sr || ec < plants[*it].c || plants[*it].c < sc) {
            mt[rb][cb][plants[*it].category] = max(mt[rb][cb][plants[*it].category], plants[*it].time);
            ++it;
            continue;
        }
        it = buc[rb][cb].erase(it);
        ret++;
    }
    return ret;
}
 
 
 
 
int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth) {
    int ret = 0, Lg[3] = { L * GrouwthTime[0], L * GrouwthTime[1], L * GrouwthTime[2] };
    int sr = mRow, sc = mCol, er = mRow + mHeight - 1, ec = mCol + mWidth - 1;
    int srb = sr / BUC_SIZE, erb = er / BUC_SIZE, scb = sc / BUC_SIZE, ecb = ec / BUC_SIZE;
 
 
    for (int rb = srb + 1; rb < erb; ++rb)
        for (int cb = scb + 1; cb < ecb; ++cb)
            for (int ca = 0; ca < 3; ++ca)
                if (mTime - mt[rb][cb][ca] + wt[rb][cb] * GrouwthTime[ca] < Lg[ca])
                    return 0;
 
 
    for (int rb = srb, cb = scb; rb <= erb; ++rb) if(!isHarvestable(mTime, Lg, rb, cb, sr, er, sc, ec)) return 0;
    if (scb != ecb) for (int rb = srb, cb = ecb; rb <= erb; ++rb) if(!isHarvestable(mTime, Lg, rb, cb, sr, er, sc, ec)) return 0;
    for (int rb = srb, cb = scb + 1; cb < ecb; ++cb) if(!isHarvestable(mTime, Lg, rb, cb, sr, er, sc, ec)) return 0;
    if (srb != erb) for (int rb = erb, cb = scb + 1; cb < ecb; ++cb) if(!isHarvestable(mTime, Lg, rb, cb, sr, er, sc, ec)) return 0;
 
 
    for (int rb = srb + 1; rb < erb; ++rb)
        for (int cb = scb + 1; cb < ecb; ++cb)
            ret += purgeBucket(rb, cb);
 
 
    for (int rb = srb, cb = scb; rb <= erb; ++rb) ret += bucketHarvest(rb, cb, sr, er, sc, ec);
    if (scb != ecb) for (int rb = srb, cb = ecb; rb <= erb; ++rb) ret += bucketHarvest(rb, cb, sr, er, sc, ec);
    for (int rb = srb, cb = scb + 1; cb < ecb; ++cb) ret += bucketHarvest(rb, cb, sr, er, sc, ec);
    if (srb != erb)    for (int rb = erb, cb = scb + 1; cb < ecb; ++cb) ret += bucketHarvest(rb, cb, sr, er, sc, ec);
 
 
    return ret;
}