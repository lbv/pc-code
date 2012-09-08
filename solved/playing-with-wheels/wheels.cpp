#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))


struct Node {
    int w[4];
    int s;
    Node(int *W, int S) : s(S) { memcpy(w, W, sizeof(int)*4); }
};


int S[4];
int T[4];
int n;

bool vis[10][10][10][10];
bool forb[10][10][10][10];


int solve()
{
    int w[4] = { S[0], S[1], S[2], S[3] };
    queue<Node> q;
    q.push(Node(w, 0));

    Zero(vis);
    vis[S[0]][S[1]][S[2]][S[3]] = true;

    while (! q.empty()) {
        Node nd = q.front(); q.pop();

        if (nd.w[0] == T[0] && nd.w[1] == T[1] &&
            nd.w[2] == T[2] && nd.w[3] == T[3])
            return nd.s;

        for (int i = 0; i < 4; ++i) {
            memcpy(w, nd.w, sizeof(int)*4);
            w[i] = w[i] == 0 ? 9 : w[i] - 1;

            if (!vis[w[0]][w[1]][w[2]][w[3]] &&
                !forb[w[0]][w[1]][w[2]][w[3]]) {
                vis[w[0]][w[1]][w[2]][w[3]] = true;
                q.push(Node(w, nd.s + 1));
            }

            memcpy(w, nd.w, sizeof(int)*4);
            w[i] = w[i] == 9 ? 0 : w[i] + 1;

            if (!vis[w[0]][w[1]][w[2]][w[3]] &&
                !forb[w[0]][w[1]][w[2]][w[3]]) {
                vis[w[0]][w[1]][w[2]][w[3]] = true;
                q.push(Node(w, nd.s + 1));
            }
        }
    }

    return -1;
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d%d%d%d%d%d%d%d",
              &S[0], &S[1], &S[2], &S[3],
              &T[0], &T[1], &T[2], &T[3], &n);

        Zero(forb);

        while (n--) {
            int f1, f2, f3, f4;
            scanf("%d%d%d%d", &f1, &f2, &f3, &f4);
            forb[f1][f2][f3][f4] = true;
        }

        printf("%d\n", solve());
    }

    return 0;
}
