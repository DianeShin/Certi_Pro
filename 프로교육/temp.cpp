/*
* @file: [H2526][Pro] 기계식 주차장
  
* @brief: 모범 답안
  
* @copyright: All rights reserved (c) 2025 Samsung Electronics, Inc.
*/
 
 
 
 
#include <bits/stdc++.h>
 
 
using namespace std;
 
 
struct RESULT_E
{
    int success;
    char locname[5];
};
 
 
struct RESULT_S
{
    int cnt;
    char carlist[5][8];
};
 
 
int N, M, L;
 
 
int getIdx(char s[])
{
    return (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + s[3] - '0';
}
 
 
#define TOWING            (-2)
#define OUT_OF_LOT        (-1)    
 
 
struct Car
{
    char regNo[8];
    int d4idx;
     
    int timestamp;
    int zone, slot;
     
    set<Car*>::iterator it;
 
 
    void init(char c[])
    {
        strcpy(regNo, c);
        d4idx = getIdx(regNo + 3);
 
 
        zone = -1;
    }
};
 
 
int carCnt;
Car cars[70000];
 
 
Car* getCar()
{
    return &cars[carCnt++];
}
 
 
queue<pair<int, Car*>> events;
unordered_map<string, Car*> cdb;
 
 
struct comp
{
    bool operator() (Car* const &a, Car* const &b)
    {
        return strcmp(a->regNo, b->regNo) < 0;
    }
};
 
 
set<Car*, comp> parking[10000];
set<Car*, comp> towing[10000];
 
 
struct Zone
{
    int zoneID;
     
    int parkingNum;
    set<int> emptySlot;
 
 
    void init(int id)
    { 
        zoneID = id;
 
 
        emptySlot.clear();
        for (int i = 0; i < M; ++i)
            emptySlot.insert(i);
         
        parkingNum = 0;
    }
     
    void pullout(int slot)
    {
        --parkingNum;    
        emptySlot.insert(slot);
    }
     
    void enter(Car* p)
    {
        auto it = emptySlot.begin();
         
        p->zone = zoneID;
        p->slot = *it;
         
        emptySlot.erase(it);
        ++parkingNum;
    }
};
 
 
Zone zone[26];
 
 
void process(int cur)
{
    while (!events.empty())
    {
        int timestamp = events.front().first;
        Car* p = events.front().second;
 
 
        if (timestamp + L > cur)
            return;
 
 
        events.pop();
 
 
        if (p->timestamp == timestamp && p->zone >= 0)
        {
            zone[p->zone].pullout(p->slot);
            p->zone = TOWING;
            parking[p->d4idx].erase(p->it);
            p->it = towing[p->d4idx].insert(p).first;
        }
    }
}
 
 
void copyLoc(char s[], int zoneID, int d4idx)
{
    s[0] = 'A' + zoneID;
    s[1] = d4idx / 100 + '0';
    s[2] = d4idx / 10 % 10 + '0';
    s[3] = d4idx % 10 + '0';
    s[4] = '\0';
}
 
 
void init(int N, int M, int L)
{
    ::N = N; ::M = M; ::L = L;
 
 
    for (int i = 0; i < N; ++i)
        zone[i].init(i);
 
 
    carCnt = 0;
    for (int i = 0; i < 10000; ++i)
    {
        parking[i].clear();
        towing[i].clear();
    }
     
    while (!events.empty()) events.pop();
    cdb.clear();
}
 
 
RESULT_E enter(int mTime, char mCarNo[])
{
    process(mTime);
     
    Car* p = cdb[mCarNo];
    if (p == nullptr)
    {
        p = getCar();
        p->init(mCarNo);
        cdb[mCarNo] = p;
    }
    else if (p->zone == TOWING)
    {
        towing[p->d4idx].erase(p->it);
        p->zone = OUT_OF_LOT;
    }
 
 
    int mm = M, i0 = -1;
    for (int i = 0; i < N; ++i)
        if (zone[i].parkingNum < mm)
        {
            mm = zone[i].parkingNum;
            i0 = i;
        }
     
    p->timestamp = mTime;
     
    RESULT_E res_e;
 
 
    if (i0 == -1)
    {
        res_e.success = 0;
        return res_e;
    }
 
 
    zone[i0].enter(p);
 
 
    p->it = parking[p->d4idx].insert(p).first;
     
    events.push({mTime, p});
    res_e.success = 1;
    copyLoc(res_e.locname, p->zone, p->slot);
 
 
    return res_e;
}
 
 
int pullout(int mTime, char mCarNo[])
{
    process(mTime);
     
    Car* p = cdb[mCarNo];
 
 
    if (p == nullptr || p->zone == OUT_OF_LOT)
        return -1;
     
    int ret;
    if (p->zone != TOWING)
    {
        zone[p->zone].pullout(p->slot);
        parking[p->d4idx].erase(p->it);
        ret = mTime - p->timestamp;
    }
    else
    {
        towing[p->d4idx].erase(p->it);
        ret = -L - (mTime - p->timestamp - L) * 5;
    }
 
 
    p->zone = OUT_OF_LOT;
 
 
    return ret;
}
 
 
RESULT_S search(int mTime, char mStr[])
{
    process(mTime);
     
    RESULT_S res_s;
     
    res_s.cnt = 0;
 
 
    int d4idx = getIdx(mStr);
    for (auto p : parking[d4idx])
    {
        if (res_s.cnt == 5)
            break;
        strcpy(res_s.carlist[res_s.cnt++], p->regNo);
    }
 
 
    for (auto p : towing[d4idx])
    {
        if (res_s.cnt == 5)
            break;
        strcpy(res_s.carlist[res_s.cnt++], p->regNo);
    }
 
 
    return res_s;
}