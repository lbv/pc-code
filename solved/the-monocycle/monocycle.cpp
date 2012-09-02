#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXM 25
#define MAXN 25

#define Zero(v) memset((v), 0, sizeof(v))


struct Node {
    int r, c;  // row, column
    int k, d;  // color, direction
    int t;     // time
    Node(int R, int C, int K, int D, int T) : r(R), c(C), k(K), d(D), t(T) {}
};
typedef queue<Node> NQ;

int M, N;
char grid[MAXM][MAXN + 1];
bool vis[MAXM][MAXN][5][4];

const int dir[4][2] = {
    { -1,  0 },  // north
    {  0,  1 },  // east
    {  1,  0 },  // south
    {  0, -1 }   // west
};


bool valid_pos(int r, int c)
{
    return r >= 0 && r < M && c >= 0 && c < N && grid[r][c] != '#';
}

int solve()
{
    int r, c, end_r, end_c;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'S')
                r = i, c = j;
            else if (grid[i][j] == 'T')
                end_r = i, end_c = j;
        }

    NQ q;
    q.push(Node(r, c, 0, 0, 0));

    Zero(vis);
    vis[r][c][0][0] = true;

    while (! q.empty()) {
        Node nd = q.front(); q.pop();

        if (nd.r == end_r && nd.c == end_c && nd.k == 0)
            return nd.t;

        for (int i = 1; i < 4; i += 2) {
            int d = (nd.d + i) % 4;

            if (vis[nd.r][nd.c][nd.k][d]) continue;
            vis[nd.r][nd.c][nd.k][d] = true;

            q.push(Node(nd.r, nd.c, nd.k, d, nd.t + 1));
        }

        r = nd.r + dir[nd.d][0];
        c = nd.c + dir[nd.d][1];
        int k = (nd.k + 1) % 5;

        if (! valid_pos(r, c) || vis[r][c][k][nd.d]) continue;

        vis[r][c][k][nd.d] = true;
        q.push(Node(r, c, k, nd.d, nd.t + 1));
    }

    return -1;
}

int main()
{
    bool first = true;
    int ncase = 0;

    while (true) {
        scanf("%d%d", &M, &N);
        if (M == 0 && N == 0) break;

        gets(grid[0]);  // skip newline
        for (int i = 0; i < M; ++i)
            gets(grid[i]);

        if (first) first = false;
        else putchar('\n');

        printf("Case #%d\n", ++ncase);
        int ans = solve();
        if (ans >= 0)
            printf("minimum time = %d sec\n", ans);
        else
            puts("destination not reachable");
    }

    return 0;
}
