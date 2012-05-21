#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAXM 10
#define MAXN 10
#define INF  10010

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

struct Node {
    int t, r, c;
    Node(int T, int R, int C) : t(T), r(R), c(C) {}
};

typedef queue<Node> NQ;

int M, N;

char board[MAXM][MAXN + 1];
bool vis[MAXM][MAXN];

int totalmoves[MAXM][MAXN];
int totalriders[MAXM][MAXN];

const int ndeltas = 8;
const int deltas[8][2] = {
    {  1,  2 },
    {  1, -2 },
    { -1,  2 },
    { -1, -2 },
    {  2,  1 },
    {  2, -1 },
    { -2,  1 },
    { -2, -1 },
};

bool isValid(int r, int c)
{
    return r >= 0 && r < M && c >= 0 && c < N;
}

void bfs(int k, int row, int col)
{
    Zero(vis);
    NQ q;
    q.push(Node(0, row, col));
    vis[row][col] = true;

    while (! q.empty()) {
        Node n = q.front(); q.pop();
        int mv = n.t == 0 ? 0 : (n.t - 1)/k + 1;

        totalmoves[n.r][n.c] += mv;
        ++totalriders[n.r][n.c];

        int t2 = n.t + 1;
        for (int i = 0; i < ndeltas; ++i) {
            int r2 = n.r + deltas[i][0];
            int c2 = n.c + deltas[i][1];

            if (! isValid(r2, c2) || vis[r2][c2]) continue;
            vis[r2][c2] = true;
            q.push(Node(t2, r2, c2));
        }
    }
}

int solve()
{
    Zero(totalmoves);
    Zero(totalriders);

    int nriders = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                bfs(board[i][j] - '0', i, j);
                ++nriders;
            }

    int ans = INF;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (totalriders[i][j] == nriders && totalmoves[i][j] < ans)
                ans = totalmoves[i][j];

    return ans == INF ? -1 : ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &N);

        for (int i = 0; i < M; ++i)
            scanf("%s", board[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
