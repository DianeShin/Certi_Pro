#include <set>
#include <unordered_map>
#include <vector>
#include <climits>
#include <cstdint>
#include <algorithm>

using namespace std;

struct Student {
	int ID;
	uint8_t grade;
	int score;
	uint8_t gender;

} Student_pool[20000];

struct Compare {
	bool operator() (const Student& a, const Student& b) const {
		if (a.score == b.score)
			return a.ID < b.ID;
		else
			return a.score < b.score;
	}
};

// order student
set<Student, Compare> set_list[3][2]; // grade -> gender
// find student with id
unordered_map<int, Student> hash_map;

int student_cnt = 0;

void init() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			set_list[i][j].clear();
		}
	}
	hash_map.clear();
	student_cnt = 0;
	return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
	Student curr = Student_pool[student_cnt];
	if (mGender[0] == 'm') {
		curr.gender = 0;
	}
	else {
		curr.gender = 1;
	}
	curr.grade = mGrade - 1;
	curr.ID = mId;
	curr.score = mScore;

	hash_map[mId] = curr;
	set_list[mGrade - 1][curr.gender].insert(curr);
	
	student_cnt++;
	return set_list[mGrade - 1][curr.gender].rbegin()->ID;
}

int remove(int mId) {
	unordered_map<int, Student>::iterator iter = hash_map.find(mId);
	if (iter == hash_map.end()) return 0;
	Student curr = iter->second;
	hash_map.erase(iter);  // if map, with key, O(logN), with iter, O(1)

	if (set_list[curr.grade][curr.gender].size() == 1) {
		set_list[curr.grade][curr.gender].clear();
		return 0;
	}
	else {
		set_list[curr.grade][curr.gender].erase(curr);
		return set_list[curr.grade][curr.gender].begin()->ID;
	}
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	int ID = 0;
	int score = INT_MAX;
	Student target = { 0,0, mScore,0 };
	for (int i = 0; i < mGradeCnt; i++) {
		for (int j = 0; j < mGenderCnt; j++) {
			int gender = 0;
			if (mGender[j][0] == 'f') gender = 1;
			set<Student, Compare>::iterator it = set_list[mGrade[i] - 1][gender].lower_bound(target);
			if (it != set_list[mGrade[i] - 1][gender].end()){
				if (score > it->score) {
					score = it->score;
					ID = it->ID;
				}
				else if (score == it->score) {
					if (ID > it->ID) {
						ID = it->ID;
					}
				}
			}
		}
	}
	
	return ID;
}