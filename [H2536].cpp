#include <vector>
#include <set>
#include <queue>
#include <cstdint>
using namespace std;

typedef pair<int, int> pii;

struct Student {
	int mID;
	uint16_t score[5];
	bool active = true;
} student_list[20001];

// descending order for set
struct setCompare {
	bool operator() (const pii& a, const pii& b) const {
		if (a.second == b.second) return a.first < b.first;
		else return a.second > b.second;
	}
};

// descending order for pq
struct queCompare {
	bool operator() (const pii& a, const pii& b) const {
		if (a.second == b.second) return a.first > b.first;
		else return a.second < b.second;
	}
};

struct Uni { // pii has mID, score
	set<pii, setCompare> accepted;
	priority_queue<pii, vector<pii>, queCompare> waitlist;
	int weights[5];
} uni_list[31];

vector<int> assigned;

int M;
int N;

void init(int N, int M, int mWeights[][5])
{
	// init const
	::M = M;
	::N = N;

	// unassign all students
	vector<int> new_assigned = vector<int>(20001, -1);
	assigned = new_assigned;

	// reset uni reg list
	for (int i = 1; i <= M; i++) {
		uni_list[i].accepted.clear();
		priority_queue<pii, vector<pii>, queCompare> new_queue;
		uni_list[i].waitlist = new_queue;

		for (int j = 0; j < 5; j++) {
			uni_list[i].weights[j] = mWeights[i-1][j];
		}
	}

	return;
}

void add(int mID, int mScores[5])
{
	Student* curr_student = &student_list[mID];
	curr_student->mID = mID;
	curr_student->active = true;
	for (int i = 0; i < 5; i++) {
		curr_student->score[i] = mScores[i];
	}

	for (int i = 1; i <= M; i++) {
		// 1. calculate score
		int score = 0;
		for (int j = 0; j < 5; j++) {
			score += curr_student->score[j] * uni_list[i].weights[j];
		}

		// 2. push into set
		uni_list[i].accepted.insert(pii(curr_student->mID, score));

		// 3-1. if overflow,put in waitlist
		// check if it can be assigned in the next school
		if (uni_list[i].accepted.size() > N) {
			auto it = prev(uni_list[i].accepted.end()); // last element
			pii new_student = *it;
			uni_list[i].accepted.erase(it);
			uni_list[i].waitlist.emplace(new_student);
			// if diff person overflow
			// save the assigned result
			// then set curr_student as the new student in interest of reassigning
			if (curr_student->mID != new_student.first) {
				assigned[curr_student->mID] = i;
				assigned[new_student.first] = -1;
				curr_student = &student_list[new_student.first];
			}
		}
		// no overflow
		// assignment confirmed
		else {
			assigned[curr_student->mID] = i;
			break;
		}
	}
	return;
}

void erase_help(int mID, int uni) {
	// 1. assign에서 해제
	for (pii curr_stu : uni_list[uni].accepted) {
		if (curr_stu.first == mID) {
			uni_list[uni].accepted.erase(curr_stu);
			break;
		}
	}
	// 2. waitlist에서 보충 시도(이때 유효한지, 또 더 좋은 대학에 assign되지 않았는지 확인)
	while (!uni_list[uni].waitlist.empty()) {
		pii new_stu = uni_list[uni].waitlist.top();
		uni_list[uni].waitlist.pop();
		if (!student_list[new_stu.first].active) continue;
		if ((assigned[new_stu.first] != -1) && assigned[new_stu.first] <= uni) continue;
		// 3. 보충에 성공하면, 보충된 애를 가지고,
		uni_list[uni].accepted.insert(new_stu);
		// 4-1. assign 안된 애면 완료
		if (assigned[new_stu.first] == -1) {
			assigned[new_stu.first] = uni;
		}
		// 4-2. assign 된 애면 거기로 erase_help 다시 부르기.
		else {
			int old_uni = assigned[new_stu.first];
			assigned[new_stu.first] = uni;
			erase_help(new_stu.first, old_uni);
		}
		break;
	}
}

void erase(int mID)
{
	student_list[mID].active = false;
	if (assigned[mID] != -1) {
		int uni = assigned[mID];
		assigned[mID] = -1;
		erase_help(mID, uni);
	}
	return;
}

int suggest(int mID)
{
	return assigned[mID];
}
