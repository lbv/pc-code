#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


typedef vector<int> IV;


struct Pair {
    int a, b;
    Pair() {}
    Pair(int A, int B) : a(A), b(B) {}
};
typedef vector<Pair> PV;


//
// Segment Tree
//
struct SegTree {
    IV A;int n, R, C;
    PV T;
    SegTree(int N, int _R, int _C) : n(N), R(_R), C(_C) {
        A.resize(n); int h = 1 + ceil(log2(n)); T.resize(1 << h); }
    void init() { tree_init(1, 0, n - 1); }
    Pair query(int r1, int c1, int r2, int c2) {
        int i = r1*C + c1;
        int j = r2*C + c2;
        return tree_query(1, 0, n - 1, r1, c1, r2, c2, i, j); }
    void update(int r, int c, int v) {
        int i = r*C + c;
        tree_update(1, 0, n - 1, i, v); }

    void tree_init(int x, int a, int b) {
        if (a == b) { T[x] = Pair(A[a], A[a]); return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        tree_init(lt, a, md);
        tree_init(rt, md + 1, b);
        T[x] = Pair(max(T[lt].a, T[rt].a), min(T[lt].b, T[rt].b));
    }
    Pair tree_query(int x, int a, int b, int r1, int c1, int r2, int c2,
                    int i, int j) {
        int ra = a / C, ca = a % C;
        int rb = b / C, cb = b % C;
        if (j < a || i > b || (ra == rb && (c2 < ca || c1 > cb)))
            return Pair(-1, -1);
        if (ra == rb && ca >= c1 && cb <= c2)
            return T[x];

        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        Pair q1 = tree_query(lt, a, md, r1, c1, r2, c2, i, j);
        Pair q2 = tree_query(rt, md + 1, b, r1, c1, r2, c2, i, j);
        if (q1.a < 0) return q2;
        if (q2.a < 0) return q1;
        return Pair(max(q1.a, q2.a), min(q1.b, q2.b));
    }
    void tree_update(int x, int a, int b, int i, int v) {
        if (a == b) {
            T[x] = Pair(v, v);
            return;
        }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;

        if (i <= md) tree_update(lt, a, md, i, v);
        else         tree_update(rt, md + 1, b, i, v);

        T[x] = Pair(max(T[lt].a, T[rt].a), min(T[lt].b, T[rt].b));
    }
};



int N, M, Q;


int safe_row(int r)
{
    if (r < 1) r = 1;
    if (r > N) r = N;
    return r - 1;
}

int safe_col(int c)
{
    if (c < 1) c = 1;
    if (c > M) c = M;
    return c - 1;
}

int main()
{
    while (true) {
        if (scanf("%d%d", &N, &M) != 2) break;

        SegTree tree(N*M, N, M);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                scanf("%d", &tree.A[i*M + j]);

        tree.init();

        scanf("%d", &Q);
        while (Q--) {
            char type;
            scanf(" %c", &type);

            if (type == 'q') {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

                int r1 = safe_row(x1);
                int c1 = safe_col(y1);
                int r2 = safe_row(x2);
                int c2 = safe_col(y2);

                Pair ans = tree.query(r1, c1, r2, c2);
                printf("%d %d\n", ans.a, ans.b);
            }
            else {
                int x, y, v;
                scanf("%d%d%d", &x, &y, &v);

                if (x < 1 || x > N || y < 1 || y > M) continue;
                int r = x - 1;
                int c = y - 1;

                tree.update(r, c, v);
            }
        }
    }

    return 0;
}
