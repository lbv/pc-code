#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 9

#define Zero(v) memset(v, 0, sizeof(v))

struct Pos {
    int r, c;
    Pos(int R, int C) : r(R), c(C) {}
    Pos() {}
    bool operator==(const Pos &x) const { return r == x.r && c == x.c; }
    bool operator!=(const Pos &x) const { return ! (*this == x); }
    bool operator<(const Pos &x) const {
        if (r != x.r) return r < x.r;
        return c < x.c;
    }
};

struct Node {
    int m;  // moves
    Pos robots[3];
    Node() { m = 0; }
    int r(int i) { return robots[i].r; }
    int c(int i) { return robots[i].c; }
    void sort() { std::sort(robots, robots + 3); }
};

typedef queue<Node> NQ;

int N;

char maze[MAXN][MAXN + 1];
bool visit[MAXN][MAXN][MAXN][MAXN][MAXN][MAXN];

const int moves[4][2] = {
    {  0,  1 },
    {  0, -1 },
    {  1,  0 },
    { -1,  0 }
};

#define Visit(n)   visit[n.r(0)][n.c(0)][n.r(1)][n.c(1)][n.r(2)][n.c(2)] = true
#define Visited(n) (visit[n.r(0)][n.c(0)][n.r(1)][n.c(1)][n.r(2)][n.c(2)])

bool valid_pos(int r, int c)
{
    return r >= 0 && r < N && c >= 0 && c < N && maze[r][c] != '#';
}

void move(Node &nd, int m)
{
    int dr = moves[m][0];
    int dc = moves[m][1];

    Pos a, b, c;

    if (valid_pos(nd.r(0) + dr, nd.c(0) + dc))
        a = Pos(nd.r(0) + dr, nd.c(0) + dc);
    else
        a = nd.robots[0];

    if (valid_pos(nd.r(1) + dr, nd.c(1) + dc))
        b = Pos(nd.r(1) + dr, nd.c(1) + dc);
    else
        b = nd.robots[1];

    if (valid_pos(nd.r(2) + dr, nd.c(2) + dc))
        c = Pos(nd.r(2) + dr, nd.c(2) + dc);
    else
        c = nd.robots[2];

    if (a != b && a != c)
        nd.robots[0] = a;
    if (b != a && b != c)
        nd.robots[1] = b;
    if (c != a && c != b)
        nd.robots[2] = c;

    nd.sort();
    ++nd.m;
}

bool robots_on_exits(Node &nd, Pos exits[])
{
    for (int i = 0; i < 3; ++i)
        if (nd.robots[0] != exits[i] &&
            nd.robots[1] != exits[i] &&
            nd.robots[2] != exits[i])
            return false;
    return true;
}

int solve()
{
    Pos exits[3];
    Node nd;

    int e = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (maze[i][j] == 'A')
                nd.robots[0] = Pos(i, j);
            else if (maze[i][j] == 'B')
                nd.robots[1] = Pos(i, j);
            else if (maze[i][j] == 'C')
                nd.robots[2] = Pos(i, j);
            else if (maze[i][j] == 'X')
                exits[e++] = Pos(i, j);
        }

    nd.sort();

    Zero(visit);

    NQ q;
    q.push(nd);
    Visit(nd);

    while (! q.empty()) {
        nd = q.front(); q.pop();

        if (robots_on_exits(nd, exits))
            return nd.m;

        for (int i = 0; i < 4; ++i) {
            Node nd2 = nd;

            move(nd2, i);

            if (! Visited(nd2)) {
                Visit(nd2);
                q.push(nd2);
            }
        }
    }

    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 0; i < N; ++i) scanf("%s", maze[i]);

        printf("Case %d: ", ++ncase);

        int ans = solve();
        if (ans < 0)
            puts("trapped");
        else
            printf("%d\n", ans);
    }

    return 0;
}
