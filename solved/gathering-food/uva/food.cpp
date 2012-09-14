#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAXN 10
#define MOD  20437

#define Zero(v) memset((v), 0, sizeof(v))


struct Node {
    int r, c;  // row, column
    int s;     // number of steps taken
    char n;    // next letter to visit
    int l;     // letters visited
    Node(int R, int C, int S, char N) : r(R), c(C), s(S), n(N) {
        l = n - 'A';
    }
};
typedef queue<Node> NQ;


int N;
char maze[MAXN][MAXN + 1];
bool vis[27][MAXN][MAXN];
int ways[27][MAXN][MAXN];

// Used to store the final answer
int steps, nways;

const int dd[4][2] = {
    {  0,  1 },
    {  0, -1 },
    {  1,  0 },
    { -1,  0 }
};


bool is_valid(int r, int c)
{
    return r >= 0 && r < N && c >= 0 && c < N && maze[r][c] != '#';
}

bool solve()
{
    char last = 'A';  // highest letter in the maze

    int r, c;
    r = c = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (! isupper(maze[i][j])) continue;
            if (maze[i][j] == 'A')
                r = i, c = j;
            if (maze[i][j] > last)
                last = maze[i][j];
        }

    NQ q;
    q.push(Node(r, c, 0, 'A'));

    Zero(ways);
    ways[0][r][c] = 1;
    Zero(vis);
    vis[0][r][c] = true;

    while (! q.empty()) {
        Node nd = q.front(); q.pop();

        int iways = ways[nd.l][nd.r][nd.c];

        if (maze[nd.r][nd.c] == last) {
            steps = nd.s;
            nways = iways;
            return true;
        }

        if (maze[nd.r][nd.c] == nd.n) ++nd.n;

        for (int i = 0; i < 4; ++i) {
            r = nd.r + dd[i][0];
            c = nd.c + dd[i][1];

            if (! is_valid(r, c)) continue;
            if (isupper(maze[r][c]) && maze[r][c] > nd.n) continue;

            int letters = nd.n - 'A';
            ways[letters][r][c] += iways;
            ways[letters][r][c] %= MOD;

            if (vis[letters][r][c]) continue;

            q.push(Node(r, c, nd.s + 1, nd.n));
            vis[letters][r][c] = true;
        }
    }

    return false;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        for (int i = 0; i < N; ++i) scanf("%s", maze[i]);

        printf("Case %d: ", ++ncase);

        if (solve())
            printf("%d %d\n", steps, nways);
        else
            puts("Impossible");
    }

    return 0;
}
