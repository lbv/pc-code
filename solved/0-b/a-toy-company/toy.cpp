#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define Zero(v) memset(v, 0, sizeof(v))

struct Node {
    int s;        // steps
    int a, b, c;  // word formed
    Node(int S, int A, int B, int C) : s(S), a(A), b(B), c(C) {}
    Node() {}
};
typedef queue<Node> NQ;

char from[4];
char to[4];
int n;

char words[3][27];

bool visit[26][26][26];
bool forbid[26][26][26];

#define Valid(x) (! forbid[x.a][x.b][x.c] && ! visit[x.a][x.b][x.c])
#define Push(x)  do { q.push(x); visit[x.a][x.b][x.c] = true; } while (false)

int solve()
{
    NQ q;
    Node nd(0, from[0] - 'a', from[1] - 'a', from[2] - 'a');
    Node nd2;

    Zero(visit);
    if (Valid(nd)) Push(nd);

    int A = to[0] - 'a';
    int B = to[1] - 'a';
    int C = to[2] - 'a';


    while (! q.empty()) {
        nd = q.front(); q.pop();

        if (nd.a == A && nd.b == B && nd.c == C)
            return nd.s;

        nd2 = Node(nd.s + 1, nd.a == 0 ? 25 : nd.a - 1, nd.b, nd.c);
        if (Valid(nd2)) Push(nd2);

        nd2 = Node(nd.s + 1, (nd.a + 1) % 26, nd.b, nd.c);
        if (Valid(nd2)) Push(nd2);

        nd2 = Node(nd.s + 1, nd.a, nd.b == 0 ? 25 : nd.b - 1, nd.c);
        if (Valid(nd2)) Push(nd2);

        nd2 = Node(nd.s + 1, nd.a, (nd.b + 1) % 26, nd.c);
        if (Valid(nd2)) Push(nd2);

        nd2 = Node(nd.s + 1, nd.a, nd.b, nd.c == 0 ? 25 : nd.c - 1);
        if (Valid(nd2)) Push(nd2);

        nd2 = Node(nd.s + 1, nd.a, nd.b, (nd.c + 1) % 26);
        if (Valid(nd2)) Push(nd2);
    }

    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s%s%d", from, to, &n);

        Zero(forbid);
        while (n--) {
            scanf("%s%s%s", words[0], words[1], words[2]);

            for (int i = 0, I = strlen(words[0]); i < I; ++i)
                for (int j = 0, J = strlen(words[1]); j < J; ++j)
                    for (int k = 0, K = strlen(words[2]); k < K; ++k) {
                        int a = words[0][i] - 'a';
                        int b = words[1][j] - 'a';
                        int c = words[2][k] - 'a';
                        forbid[a][b][c] = true;
                    }
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
