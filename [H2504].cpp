// Check if storing all information is necessary!
// Sometimes you do not need all information

#include <unordered_map>
#include <algorithm>
#include <vector>
#define MAX_L 100;
#define MAX_N MAX_L * 50;
#define MAX_RECT 15000
using namespace std;

struct Rect {
    int row;
    int col;
    int height;
    int width;
    int index;
    int id;
} rect_list[MAX_RECT];

// mID to Rect pointer
unordered_map<int, Rect*> hash_map;
// index to mID
vector<Rect*> rect_map[50][50];

// parent finder
int P[MAX_RECT];
int cnt[MAX_RECT];

int rect_cnt = 0;
int group_cnt = 0;
int L;


void init(int L, int N) {
    ::L = L;

    for (int i = 0; i < N / L; i++) {
        for (int j = 0; j < N / L; j++) {
            rect_map[i][j].clear();
        }
    }

    for (int i = 0; i < MAX_RECT; i++) {
        P[i] = 0;
        cnt[i] = 0;
    }

    rect_cnt = 0;
    group_cnt = 0;
    hash_map.clear();
}

// a 기준으로 b가 overlap 하는가?
bool check_overlap(Rect* a, Rect* b) {
    return !(a->col + a->width - 1 < b->col || b->col + b->width - 1 < a->col || a->row + a->height - 1 < b->row || b->row + b->height - 1 < a->row);
}

// find mID's parent index
int findParent(int mID) {
    int curr_rect_index = hash_map[mID]->index;

    while (true) {
        if (P[curr_rect_index] == curr_rect_index) return curr_rect_index;
        else curr_rect_index = P[curr_rect_index];
    }
}

int getRectCount(int mID) {
    // not found
    unordered_map<int, Rect*>::iterator it = hash_map.find(mID);
    if (it == hash_map.end()) return 0;
    // found -> return group size
    return cnt[findParent(mID)];
}

// instead of maintaining the actual chain, just maintain the number of rects in groups.
int draw(int mID, int mRow, int mCol, int mHeight, int mWidth) {
    Rect* new_rect = &rect_list[rect_cnt];
    new_rect->row = mRow;
    new_rect->col = mCol;
    new_rect->height = mHeight;
    new_rect->width = mWidth;
    new_rect->index = rect_cnt;
    new_rect->id = mID;
    group_cnt++;
    // mID - new_rect pair
    hash_map[mID] = new_rect;
    cnt[rect_cnt] = 1;
    P[rect_cnt] = rect_cnt;

    for (int i = max(0, mRow / L - 1); i <= min(49, mRow / L + 1); i++) {
        for (int j = max(0, mCol / L - 1); j <= min(49, mCol / L + 1); j++) {
            for (Rect* curr_rect : rect_map[i][j]) {
                bool overlap = check_overlap(new_rect, curr_rect);
                if (overlap) {
                    int new_index = findParent(mID);
                    int curr_index = findParent(curr_rect->id);

                    if (new_index == curr_index) continue;
                    else {
                        P[new_index] = curr_index;
                        cnt[curr_index] += cnt[new_index];
                        group_cnt--;
                    }
                }
            }
        }
    }

    rect_cnt++;
    rect_map[mRow / L][mCol / L].push_back(new_rect);
    return getRectCount(mID);
}



int countGroup() {
    return group_cnt;
}