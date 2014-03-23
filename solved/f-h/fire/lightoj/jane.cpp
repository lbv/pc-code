#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAXR 200
#define MAXC 200

#define Zero(v) memset(v, 0, sizeof(v))

int R, C;
char map[MAXR][MAXC + 1];
char flg[MAXR][MAXC];

// Represents a state
struct Node {
    char w;       // who is there (J or F)
    int r, c, t;  // row, column and time
    Node(char W, int R, int C, int T) : w(W), r(R), c(C), t(T) {}
};

const int deltas[4][2] = {
    {  0, -1 },
    {  0,  1 },
    {  1,  0 },
    { -1,  0 }
};

void locateJane(int &r, int &c)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (map[i][j] == 'J') {
                r = i;
                c = j;
                return;
            }
}

bool isvalid(int r, int c)
{
    return r >= 0 && r < R && c >= 0 && c < C;
}

int solve()
{
    queue<Node> q;
    Zero(flg);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (map[i][j] == 'F') q.push(Node('F', i, j, 0));

    int r, c;
    locateJane(r, c);
    q.push(Node('J', r, c, 0));
    flg[r][c] = 1;

    while (! q.empty()) {
        Node n = q.front(); q.pop();
        int t2 = n.t + 1;

        for (int i = 0; i < 4; i++) {
            int r2 = n.r + deltas[i][0];
            int c2 = n.c + deltas[i][1];
            bool valid = isvalid(r2, c2);

            if (n.w == 'F') {
                if (valid && map[r2][c2] != '#' && map[r2][c2] != 'F') {
                    map[r2][c2] = 'F';
                    q.push(Node('F', r2, c2, t2));
                }
            }
            else {  // n.w == 'J'
                if (! valid) return t2;
                if (flg[r2][c2]) continue;
                if (map[r2][c2] != '#' && map[r2][c2] != 'F') {
                    // map[r2][c2] = 'J';
                    q.push(Node('J', r2, c2, t2));
                    flg[r2][c2] = 1;
                }
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
        scanf("%d%d", &R, &C);
        for (int i = 0; i < R; i++) scanf("%s", map[i]);

        int ans = solve();
        if (ans < 0)
            printf("Case %d: IMPOSSIBLE\n", ncase++);
        else
            printf("Case %d: %d\n", ncase++, ans);
    }

    return 0;
}
