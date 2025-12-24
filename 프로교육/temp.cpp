#include <set>
#include <vector>
#include <unordered_map>

#define MAX_ITEMS 100000
using namespace std;

struct Item {
	int ID;
	int price;
	bool alive;
	int category;
	int company;
}items[MAX_ITEMS];

struct comp
{
	bool operator() (Item* const& a, Item* const& b) const
	{
		return a->price != b->price ? a->price < b->price : a->ID < b->ID;
	}
};


struct Section {
	set<Item*, comp> itemSet;
	int discount;
	int closeCnt;
};

unordered_map<int, Item*> IDItemMap;

Section sections[6][6]; // category , company
int itemCnt;

struct RESULT
{
	int cnt;
	int IDs[5];
};

void init()
{
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			sections[i][j].itemSet.clear();
			sections[i][j].discount = 0;
			sections[i][j].closeCnt = 0;
		}
	}
	itemCnt = 0;
	return;
}

int sell(int mID, int mCategory, int mCompany, int mPrice)
{
	Item* item = &items[itemCnt++];
	item->ID = mID;
	item->price = mPrice + sections[mCategory][mCompany].discount;
	item->alive = true;
	item->category = mCategory;
	item->company = mCompany;
	sections[mCategory][mCompany].itemSet.insert(item);
	IDItemMap[mID] = item;
	return sections[mCategory][mCompany].itemSet.size() - sections[mCategory][mCompany].closeCnt;
}

int closeSale(int mID)
{
	// 1. does not exist
	if (IDItemMap.find(mID) == IDItemMap.end()) return -1;
	// 2. Item not alive
	else if (IDItemMap[mID]->alive == false) return -1;
	else {
		IDItemMap[mID]->alive = false;
		sections[IDItemMap[mID]->category][IDItemMap[mID]->company].closeCnt++; // item 없어짐 표시
	}
	return IDItemMap[mID]->price - sections[IDItemMap[mID]->category][IDItemMap[mID]->company].discount;
}

int discount(int mCategory, int mCompany, int mAmount)
{
	sections[mCategory][mCompany].discount += mAmount;
	for (Item* item : sections[mCategory][mCompany].itemSet) {
		if (item->alive) {
			if (item->price <= sections[mCategory][mCompany].discount) {
				item->alive = false;
				sections[mCategory][mCompany].closeCnt++;
			}
			else break;
		}
	}
	return sections[mCategory][mCompany].itemSet.size() - sections[mCategory][mCompany].closeCnt;
}

RESULT show(int mHow, int mCode)
{
	RESULT res;

	set<Item*, comp> result_set;
	if (mHow == 0) {
		for (int i = 1; i <= 5; i++) {
			for (int j = 1; j <= 5; j++) {
				int cnt = 0;
				for (Item* item : sections[i][j].itemSet) {
					if (item->alive) {
						Item* cpy_item = &items[itemCnt++];
						cpy_item->ID = item->ID;
						cpy_item->price = item->price - sections[i][j].discount;
						result_set.insert(cpy_item);
						if (result_set.size() > 5) result_set.erase(--result_set.end());
						cnt++;
						if (cnt >= 5) break;
					}
				}
			}
		}
	}
	else if (mHow == 1) { // mCode is Category
		for (int j = 1; j <= 5; j++) {
			int cnt = 0;
			for (Item* item : sections[mCode][j].itemSet) {
				if (item->alive) {
					Item* cpy_item = &items[itemCnt++];
					cpy_item->ID = item->ID;
					cpy_item->price = item->price - sections[mCode][j].discount;
					result_set.insert(cpy_item);
					if (result_set.size() > 5) result_set.erase(--result_set.end());
					cnt++;
					if (cnt >= 5) break;
				}
			}
		}
	}
	else { // mCode is Compnay
		for (int i = 1; i <= 5; i++) {
			int cnt = 0;
			for (Item* item : sections[i][mCode].itemSet) {
				if (item->alive) {
					Item* cpy_item = &items[itemCnt++];
					cpy_item->ID = item->ID;
					cpy_item->price = item->price - sections[i][mCode].discount;
					result_set.insert(cpy_item);
					if (result_set.size() > 5) result_set.erase(--result_set.end());
					cnt++;
					if (cnt >= 5) break;
				}
			}
		}
	}

	int idx = 0;
	for (Item* item : result_set) {
		res.IDs[idx++] = item->ID;
	}
	res.cnt = idx;
	return res;
}

/*
      
* @file: [H2506][Pro] 온라인마트
      
* @brief: 모범 답안 
     
* @copyright: All rights reserved (c) 2025 Samsung Electronics, Inc. 
     
*/
 
 
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
 
 
using namespace std;
 
 
struct RESULT
{
    int cnt;
    int IDs[5];
};
 
 
struct Item
{
    int id, ca, co, pr;
 
 
    set<Item*>::iterator it;
 
 
    bool alive;
 
 
    void init(int _id, int _ca, int _co, int _pr)
    {
        id = _id; ca = _ca; co = _co; pr = _pr;
         
        alive = true;
    }
};
 
 
int nn;
Item items[50'000];
 
 
Item* getItem()
{
    return &items[nn++];
}
 
 
struct comp
{
    bool operator() (Item* const &a, Item* const &b)
    {
        return a->pr != b->pr ? a->pr < b->pr : a->id < b->id;
    }
};
 
 
struct Bucket
{
    int ca, co;
    set<Item*, comp> itemlist;
     
    int base;
     
    void init(int _ca, int _co)
    {
        ca = _ca; co = _co;
        itemlist.clear();
 
 
        base = 0;
    }
     
    void add(Item* p)
    {
        p->it = itemlist.insert(p).first;
    }
     
    void erase(Item* p)
    {
        itemlist.erase(p->it);
    }
     
    void update()
    {
        auto it = itemlist.begin();
        while (it != itemlist.end() && (*it)->pr + base <= 0)
        {
            (*it)->alive = false;
            it = itemlist.erase(it);
        }
    }
     
    int size()
    {
        return itemlist.size();
    }
};
 
 
Bucket buc[6][6];
 
 
unordered_map<int, Item*> cdb;
 
 
void init()
{
    nn = 0;
     
    for (int i = 1; i <= 5; ++i)
    for (int j = 1; j <= 5; ++j)
        buc[i][j].init(i, j);
     
    cdb.clear();
}
 
 
int sell(int mID, int mCategory, int mCompany, int mPrice)
{
    Item* p = getItem();
    p->init(mID, mCategory, mCompany, mPrice - buc[mCategory][mCompany].base);
    buc[mCategory][mCompany].add(p);
     
    cdb[mID] = p;
     
    return buc[mCategory][mCompany].size();
}
 
 
int closeSale(int mID)
{
    Item* p = cdb[mID];
     
    if (!p || !p->alive) return -1;
    p->alive = false;
 
 
    buc[p->ca][p->co].erase(p);
     
    return p->pr + buc[p->ca][p->co].base;
}
 
 
int discount(int mCategory, int mCompany, int mAmount)
{
    buc[mCategory][mCompany].base -= mAmount;
    buc[mCategory][mCompany].update();
     
    return buc[mCategory][mCompany].size();
}
 
 
RESULT show(int mHow, int mCode)
{
    RESULT res;
 
 
    vector<pair<int, int>> con;
 
 
    if (mHow == 0)
    {
        for (int i = 1; i <= 5; ++i)
        for (int j = 1; j <= 5; ++j)
        {
            int c = 0;
            for (auto it = buc[i][j].itemlist.begin(); it != buc[i][j].itemlist.end() && c < 5; ++c, ++it)
            {
                Item* p = (*it);
                con.push_back({p->pr + buc[i][j].base, p->id});
            }
        }
    }
    else if (mHow == 1)
    {
        for (int i = 1; i <= 5; ++i)
        {
            int c = 0;
            for (auto it = buc[mCode][i].itemlist.begin(); it != buc[mCode][i].itemlist.end() && c < 5; ++c, ++it)
            {
                Item* p = (*it);
                con.push_back({p->pr + buc[mCode][i].base, p->id});
            }
        }
    }
    else
    {
        for (int i = 1; i <= 5; ++i)
        {
            int c = 0;
            for (auto it = buc[i][mCode].itemlist.begin(); it != buc[i][mCode].itemlist.end() && c < 5; ++c, ++it)
            {
                Item* p = (*it);
                con.push_back({p->pr + buc[i][mCode].base, p->id});
            }
        }
    }
 
 
    sort(con.begin(), con.end());
     
    res.cnt = min(5, (int)con.size());
    for (int i = 0; i < res.cnt; ++i)
        res.IDs[i] = con[i].second;
 
 
    return res;
}