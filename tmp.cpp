#define MAX_M    4
#define MAX_N     100
#define MAX_Q     10000
#define INF     100000
 
int N, M, grd[MAX_N][MAX_N], visited[MAX_N][MAX_N], scnt;
int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, 1, 0, -1 };
struct Loc { int r, c, d; };
 
 
int convert(char grade[MAX_M]) {
    int n = 0, i = 0;
    while (i < M && grade[i] != 0) n = (n * 27) + (grade[i++] - 'A' + 1);
    while (i++ < M) n *= 27;
    return n;
}
 
 
void init(int N, int M, char mGrade[][MAX_N][MAX_M]) {
    ::N = N, ::M = M, scnt = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            grd[i][j] = convert(mGrade[i][j]);
            visited[i][j] = 0;
        }
    }
}
 
 
void change(int mRow, int mCol, int mDir, int mLength, char mChgGrade[MAX_M]) {
    for (int i = 0; i < mLength; i++) {
        int r = mRow + dr[mDir] * i;
        int c = mCol + dc[mDir] * i;
        grd[r][c] = convert(mChgGrade);
    }
}
 
 
Loc que[MAX_Q];
bool BFS(int L, int sRow, int sCol, int eRow, int eCol, int grade) {
    int sp = 0, ep = 0;
    que[ep++] = { sRow, sCol, 0 };
    visited[sRow][sCol] = scnt;
 
    while (sp != ep) {
        Loc cur = que[sp++];
        if (cur.r == eRow && cur.c == eCol) return true;
 
        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d], nc = cur.c + dc[d], nd = cur.d + 1;
            if (nr < 0 || N <= nr || nc < 0 || N <= nc) continue;
            if (grd[nr][nc] < grade) continue;
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
    int l = 0, h = 27 * 27 * 27;
    while (l < h) {
        scnt++;
        int m = (l + h) / 2 + 1;
        if (BFS(L, sRow, sCol, eRow, eCol, m)) l = m;
        else h = m - 1;
    }
 
    for (int i = M - 1; i >= 0; i--) {
        ret[i] = l % 27 == 0 ? 0 : l % 27 - 1 + 'A';
        l /= 27;
    }
    ret[M] = 0;
 
    return ret;
}