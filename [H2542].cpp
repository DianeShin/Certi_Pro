#define MAX_M 4
#define MAX_N 100
#define MAX_Q     10000
#include <cstdint>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_set>
using namespace std;

uint32_t board[MAX_N][MAX_N];
uint32_t visited[MAX_N][MAX_N];
int N, M, scnt;
int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, 1, 0, -1 };
struct Loc { int r, c, d; };

uint32_t encrypt(char* grade) {
	uint32_t result = 0;
	for (int i = 0; i < M; i++) {
		char digit = grade[i];
		result = result << 8 | digit;
	}
	return result;
}

void decrypt(uint32_t target, char* result) {
	uint8_t mask = 0b11111111;
	for (int i = 0; i <= M; i++) {
		if (i != M) {
			char digit = target & mask;
			result[M - i - 1] = digit;
			target = target >> 8;
		}
		else {
			result[i] = '\0';
		}
	}
}

void init(int N, int M, char mGrade[][MAX_N][MAX_M]) {
	::N = N;
	::M = M;
	::scnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = encrypt(mGrade[i][j]);
			visited[i][j] = 0;
		}
	}

	return;
}


void change(int mRow, int mCol, int mDir, int mLength, char mGrade[MAX_M]) {
	uint32_t new_grade = encrypt(mGrade);
	if (mDir == 0) {
		for (int i = 0; i < mLength; i++) {
			board[mRow + i][mCol] = new_grade;
		}
	}
	else {
		for (int j = 0; j < mLength; j++) {
			board[mRow][mCol + j] = new_grade;
		}
	}
}
Loc que[MAX_Q];
bool BFS(int L, int sRow, int sCol, int eRow, int eCol, uint32_t grade) {
	int sp = 0, ep = 0;
	que[ep++] = { sRow, sCol, 0 };
	visited[sRow][sCol] = scnt;

	while (sp != ep) {
		Loc cur = que[sp++];
		if (cur.r == eRow && cur.c == eCol) return true;

		for (int d = 0; d < 4; d++) {
			int nr = cur.r + dr[d], nc = cur.c + dc[d], nd = cur.d + 1;
			if (nr < 0 || N <= nr || nc < 0 || N <= nc) continue;
			if (board[nr][nc] < grade) continue;
			if (nd > L) continue;
			if (visited[nr][nc] == scnt) continue;

			visited[nr][nc] = scnt;
			que[ep++] = { nr, nc, nd };
		}
	}

	return false;
}


char ret[MAX_M];
char* calculate(int L, int sRow, int sCol, int eRow, int eCol) {
	char low[3] = { 'A', 'A', 'A' };
	char high[3] = { 'Z', 'Z', 'Z' };

	uint32_t l = encrypt(low);
	uint32_t h = encrypt(high);
	while (l < h) {
		scnt++;
		uint32_t m = (l + h) / 2 + 1;
		if (BFS(L, sRow, sCol, eRow, eCol, m)) l = m;
		else h = m - 1;
	}

	decrypt(l, ret);
	return ret;
}