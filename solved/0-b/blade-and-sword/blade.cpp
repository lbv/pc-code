#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> II;
typedef vector<II>     IIV;

#define MAXM 200
#define MAXN 200

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// There will be 2 "states", used when visiting teleportation cells. State
// "0" means that we came from an adjacent cell, state "1" means we
// teleported to the current cell
struct Node {
    int t, s, r, c;
    Node (int T, int S, int R, int C) : t(T), s(S), r(R), c(C) {}
};

typedef queue<Node> NQ;

int M, N;
char map[MAXM][MAXN + 1];
bool vis[2][MAXM][MAXN];

const int ndeltas = 4;
const int deltas[4][2] = {
    { -1,  0 },
    {  1,  0 },
    {  0,  1 },
    {  0, -1 },
};

void findElements(IIV &tele, II &player)
{
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            if (map[i][j] == '*')
                tele.push_back(II(i, j));
            else if (map[i][j] == 'P')
                player.first = i, player.second = j;
        }
}

bool isValid(int r, int c)
{
    return r >= 0 && r < M && c >= 0 && c < N;
}

int solve()
{
    IIV tele;
    II player;
    findElements(tele, player);

    NQ q;
    q.push(Node(0, 0, player.first, player.second));

    Zero(vis);
    vis[0][player.first][player.second] = true;

    while (! q.empty()) {
        Node n = q.front(); q.pop();

        if (map[n.r][n.c] == 'D') return n.t;

        int t2 = n.t + 1;

        if (map[n.r][n.c] == '*') {
            bool goback = false;
            cFor (IIV, t, tele) {
                if (t->first == n.r && t->second == n.c) {
                    goback = true;
                    continue;
                }
                if (! vis[1][t->first][t->second]) {
                    q.push(Node(t2, 1, t->first, t->second));
                    vis[1][t->first][t->second] = true;
                }
            }
            tele.clear();
            if (goback) tele.push_back(II(n.r, n.c));

            if (n.s == 0) continue;
        }

        for (int i = 0; i < ndeltas; ++i) {
            int r2 = n.r + deltas[i][0];
            int c2 = n.c + deltas[i][1];

            if (!isValid(r2, c2) || vis[0][r2][c2]) continue;
            if (map[r2][c2] != '#') {
                q.push(Node(t2, 0, r2, c2));
                vis[0][r2][c2] = true;
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
        scanf("%d%d", &M, &N);

        for (int i = 0; i < M; ++i) scanf("%s", map[i]);

        int ans = solve();
        if (ans < 0)
            printf("Case %d: impossible\n", ++ncase);
        else
            printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
