#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;


#define MAX_DEPTH 25
#define MAXN      20
#define INF       1000

#define Neg(v)  memset((v), -1, sizeof(v))


// moves[m][n]: n'th move for a position i such that i%4 == m
const int moves[4][4] = {
    { -4, -3, -1,  4 },
    { -4,  1,  3,  4 },
    { -4, -1,  1,  4 },
    { -4, -1,  1,  4 }
};

// approx[x][y]: approximated number of steps to move a number from x to y
int approx[MAXN + 1][MAXN + 1];


struct Game {
    int n;            // number of jaguars
    int p[MAXN + 1];  // permutation

    int td;       // total approx distances from all jaguars to their places
    int k;        // index of the king (number 1)
    int nxt;      // index of next child
    int last;     // last move (length of the jump)

    void init() {
        last = 0;
        td = 0;
        for (int i = 1; i <= n; ++i) {
            if (p[i] == 1)
                k = i;
            else
                td += approx[i][p[i]];
        }
    }

    int h() { return td; }

    bool is_solution() { return td == 0; }

    bool is_solvable()
    {
        int inv = 0;
        for (int i = 2; i <= n; ++i) {
            if (p[i] == 1) continue;

            for (int j = 1; j < i; ++j)
                if (p[j] != 1 && p[j] > p[i]) ++inv;
        }
        return (inv + ((k+3) / 4)) % 2 != 0;
    }

    void reset() { nxt = 0; }

    bool valid(int x) { return x >= 1 && x <= n; }

    bool next(Game &chl, int &dist, int &delta) {
        int t;  // target position
        for (; nxt < 4; ++nxt) {
            int jump = moves[k % 4][nxt];
            if (jump == -last) continue;
            t = k + jump;
            if (valid(t)) break;
        }
        if (nxt == 4) return false;

        chl = *this;

        chl.td += approx[k][p[t]] - approx[t][p[t]];

        chl.last = moves[k % 4][nxt];

        swap(chl.p[t], chl.p[k]);
        chl.k = t;

        dist = 1;
        delta = nxt++;
        return true;
    }

    void dbg() {
        printf("  :: game n(%d) h(%d): ", n, td);
        for (int i = 0; i < n; ++i)
            printf(" %d", p[i]);
        puts("");
    }
};


template <typename NT, typename DT>
bool ida_dls(NT &node, int depth, int g, int &nxt, stack<DT> &st)
{
    if (g == depth) return node.is_solution();

    NT child;
    int dist;
    DT delta;
    for (node.reset(); node.next(child, dist, delta);) {
        int f = g + dist + child.h();
        if (f > depth && f < nxt) nxt = f;
        if (f <= depth  && ida_dls(child, depth, g + 1, nxt, st)) {
            int pre = st.top();
            st.pop();
            st.push(pre + dist);
            return true;
        }
    }
    return false;
}

template <typename NT, typename DT>
bool ida_star(NT &root, int limit, stack<DT> &st)
{
    st.push(0);
    for (int depth = root.h(); depth <= limit;) {
        int next_depth = INF;
        if (ida_dls(root, depth, 0, next_depth, st)) return true;
        if (next_depth == INF) return false;
        depth = next_depth;
    }
    return false;
}

void bfs(int y)
{
    queue<int> q;
    q.push(y);
    approx[y][y] = 0;

    while (! q.empty()) {
        int x = q.front(); q.pop();

        for (int i = 0; i < 4; ++i) {
            int xp = x + moves[x % 4][i];
            if (xp >= 1 && xp <= MAXN && approx[xp][y] < 0) {
                approx[xp][y] = approx[x][y] + 1;
                q.push(xp);
            }
        }
    }
}

void prepare()
{
    Neg(approx);
    for (int y = 1; y <= MAXN; ++y)
        bfs(y);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        Game g;
        scanf("%d", &g.n);

        for (int i = 1; i <= g.n; ++i)
            scanf("%d", &g.p[i]);

        g.init();
        printf("Case %d: ", ++ncase);

        stack<int> ans;
        if (! g.is_solvable())
            puts("impossible");
        else if (ida_star(g, MAX_DEPTH, ans))
            printf("%d\n", ans.top());
        else
            puts("impossible in 25 jumps");
    }

    return 0;
}
