/*
* @file: [H2531][Pro] 보석 맞추기
  
* @brief: 모범 답안
  
* @copyright: All rights reserved (c) 2025 Samsung Electronics, Inc.
*/
 
 
 
 
#define WIDTH (8)
 
 
#include<string.h>
#include<queue>
#include<algorithm>
 
 
using namespace std;
 
 
queue<int> q[8];
int board[8][8];
 
 
void init(int N, int mJewels[][WIDTH])
{
    for (int y = 0; y < 8; y++)
    {
        while (q[y].empty() == false)
            q[y].pop();
 
 
        for (int x = 0; x < 8; x++)
        {
            board[y][x] = mJewels[y][x];
 
 
        }
    }
    for (int y = 8; y < N; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            q[x].push(mJewels[y][x]);
        }
 
 
    }
}
 
 
struct pt
{
    int score, y1, x1, y2, x2;
    pt()
    {
        score = y1 = x1 = y2 = x2 = 0;
    }
    pt(int _score, int _y1, int _x1, int _y2, int _x2)
    {
        score = _score;
        y1 = _y1;
        x1 = _x1;
        y2 = _y2;
        x2 = _x2;
    }
    bool operator<(pt tar)
    {
        if (score != tar.score)
            return score < tar.score;
 
 
        if (y1 != tar.y1)
            return y1 > tar.y1;
 
 
        if (x1 != tar.x1)
            return x1 > tar.x1;
 
 
        if (y2 != tar.y2)
            return y2 > tar.y2;
 
 
        return x2 > tar.x2;
    }
 
 
};
 
 
int ret[5];
 
 
void fill_board()
{
    for (int x = 0; x < 8; x++)
    {
        int yy = 0;
        int y = 0;
        for (int y = 0; y < 8; y++)
        {
            if (board[y][x] > 0)
                board[yy++][x] = board[y][x];
        }
        while (yy < 8)
        {
            board[yy++][x] = q[x].front();
            q[x].pop();
        }
    }
}
 
 
int check_score_swap(int y1, int x1, int y2, int x2)
{
    int ret = 0;
    int score[9] = { 0, 0, 0, 1, 4, 9, 9, 9, 9 };
 
 
    int dy[4] = { -1, 1, 0, 0 };
    int dx[4] = { 0, 0, -1, 1 };
    int pt[2][2] = { { y1,x1 }, { y2, x2 } };
 
 
    for (int i = 0; i < 2; i++)
    {
        for (int d = 0; d < 4; d += 2)
        {
            int ly = pt[i][0];
            int lx = pt[i][1];
            int ry = pt[i][0];
            int rx = pt[i][1];
 
 
            while (ly >= 0 && lx >= 0 && board[ly][lx] == board[pt[i][0]][pt[i][1]])
            {
                ly += dy[d];
                lx += dx[d];
            }
            while (ry < 8 && rx < 8 && board[ry][rx] == board[pt[i][0]][pt[i][1]])
            {
                ry += dy[d + 1];
                rx += dx[d + 1];
            }
            ret += score[abs(ry - ly - 1)] + score[abs(rx - lx - 1)];
        }
    }
 
 
    return ret;
}
 
 
int check_score()
{
    int ret = 0;
    int score[9] = { 0, 0, 0, 1, 4, 9, 9, 9, 9 };
 
 
    for (int y = 0; y < 8; y++)
    {
        int x1 = 0, x2 = 0;
 
 
        while (x2 < 8)
        {
            while (x2 < 8 && board[y][x1] == board[y][x2])
            {
                x2++;
            }
            ret += score[x2 - x1];
            x1 = x2;
        }
    }
    for (int x = 0; x < 8; x++)
    {
        int y1 = 0, y2 = 0;
 
 
        while (y2 < 8)
        {
            while (y2 < 8 && board[y1][x] == board[y2][x])
            {
                y2++;
            }
            ret += score[y2 - y1];
            y1 = y2;
        }
    }
    return ret;
}
 
 
int erase()
{
    int ret = 0;
    int score[9] = { 0, 0, 0, 1, 4, 9, 9, 9, 9 };
    int chk[8][8];
    memset(chk, 0, sizeof(chk));
 
 
    for (int y = 0; y < 8; y++)
    {
        int x1 = 0, x2 = 0;
 
 
        while (x2 < 8)
        {
            while (x2 < 8 && board[y][x1] == board[y][x2])
            {
                x2++;
            }
            ret += score[x2 - x1];
            if (x2 - x1 >= 3)
            {
                for (int x = x1; x < x2; x++)
                {
                    chk[y][x] = 1;
                }
            }
            x1 = x2;
        }
    }
    for (int x = 0; x < 8; x++)
    {
        int y1 = 0, y2 = 0;
 
 
        while (y2 < 8)
        {
            while (y2 < 8 && board[y1][x] == board[y2][x])
            {
                y2++;
            }
            ret += score[y2 - y1];
            if (y2 - y1 >= 3)
            {
                for (int y = y1; y < y2; y++)
                {
                    chk[y][x] = 1;
                }
            }
            y1 = y2;
        }
    }
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            if (chk[y][x] == 1)
                board[y][x] = 0;
 
 
    return ret;
}
 
 
int* takeTurn()
{
    pt cand = pt(0, -1, -1, -1, -1);
    while (1)
    {
        fill_board();
 
 
        while (check_score())
        {
            erase();
            fill_board();
        }
 
 
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (x < 7)
                {
                    swap(board[y][x], board[y][x + 1]);
 
 
                    pt tmp = pt(check_score_swap(y, x, y, x + 1), y, x, y, x + 1);
                    if (cand < tmp)
                        cand = tmp;
                    swap(board[y][x], board[y][x + 1]);
                }
                if (y < 7)
                {
                    swap(board[y][x], board[y + 1][x]);
 
 
                    pt tmp = pt(check_score_swap(y, x, y + 1, x), y, x, y + 1, x);
                    if (cand < tmp)
                        cand = tmp;
 
 
                    swap(board[y][x], board[y + 1][x]);
                }
            }
        }
        if (cand.score == 0)
        {
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    board[y][x] = q[x].front();
                    q[x].pop();
                }
            }
        }
        else
        {
            break;
        }
    }
 
 
    swap(board[cand.y1][cand.x1], board[cand.y2][cand.x2]);
 
 
    int ret_score = 0;
    while (check_score())
    {
        ret_score += erase();
        fill_board();
    }
 
 
    ret[0] = ret_score;
    ret[1] = cand.y1;
    ret[2] = cand.x1;
    ret[3] = cand.y2;
    ret[4] = cand.x2;
 
 
    return ret;
}