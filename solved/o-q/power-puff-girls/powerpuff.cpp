#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAXM 20
#define MAXN 20

#define Zero(v) memset(v, 0, sizeof(v))

int M, N;
char map[MAXM][MAXN + 1];
char flg[3][MAXM][MAXN];

// Represents a state
struct Node {
    char w;       // who is there (a, b, or c)
    int r, c, t;  // row, column and time
    Node(char W, int R, int C, int T) : w(W), r(R), c(C), t(T) {}
};

const int deltas[4][2] = {
    {  0, -1 },
    {  0,  1 },
    {  1,  0 },
    { -1,  0 }
};

bool isvalid(int r, int c)
{
    return r >= 0 && r < M && c >= 0 && c < N;
}

int solve()
{
    queue<Node> q;
    char home[3] = { 0 };
    Zero(flg);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 'a') {
                q.push(Node('a', i, j, 0));
                flg[0][i][j] = 1;
            }
            else if (map[i][j] == 'b') {
                q.push(Node('b', i, j, 0));
                flg[1][i][j] = 1;
            }
            else if (map[i][j] == 'c') {
                q.push(Node('c', i, j, 0));
                flg[2][i][j] = 1;
            }
        }

    while (! q.empty()) {
        Node n = q.front(); q.pop();
        int t2 = n.t + 1;
        int idx = n.w - 'a';
        if (home[idx]) continue;

        if (map[n.r][n.c] == 'h') {
            home[idx] = 1;
            if (home[0] && home[1] && home[2]) return n.t;
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int r2 = n.r + deltas[i][0];
            int c2 = n.c + deltas[i][1];
            if (! isvalid(r2, c2)) continue;

            if (!flg[idx][r2][c2] && map[r2][c2] != '#'
                && map[r2][c2] != 'm') {
                q.push(Node(n.w, r2, c2, t2));
                flg[idx][r2][c2] = 1;
            }
        }
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d%d", &M, &N);
        for (int i = 0; i < M; i++) scanf("%s", map[i]);

        printf("Case %d: %d\n", ncase++, solve());
    }

    return 0;
}
