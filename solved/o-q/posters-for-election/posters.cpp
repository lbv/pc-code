#include <cstdio>
#include <cstring>


#define MAXN 100000

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


#define MAXH 19  // 1 + ceil(log2(2*MAXN))
struct SegTree {
    struct Node {
        int v;   // number of free sectors in the wall
        bool u;  // requires update
    };

    Node T[1 << MAXH];
    int n;

    void init(int N) { n = N; tree_init(1, 0, n-1); }
    void tree_init(int x, int a, int b) {
        T[x].u = false;
        if (a == b) { T[x].v = 1; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        tree_init(lt, a, md);
        tree_init(rt, md + 1, b);
        T[x].v = T[lt].v + T[rt].v;
    }

    void propagate(int x, int a, int b) {
        if (! T[x].u) return;
        T[x].v = 0;
        if (a != b) {
            int lt = 2*x, rt = lt + 1;
            T[lt].u = T[rt].u = true;
        }
        T[x].u = false;
    }

    void update(int i, int j) { tree_update(i, j, 1, 0, n-1); }
    void tree_update(int i, int j, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v = 0; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x].v = 0;
            T[lt].u = T[rt].u = true;
            return;
        }
        tree_update(i, j, lt, a, md);
        tree_update(i, j, rt, md + 1, b);
        T[x].v = T[lt].v + T[rt].v;
    }

    int query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
    int tree_query(int i, int j, int x, int a, int b) {
        if (j < a || i > b) return 0;
        propagate(x, a, b);
        if (a >= i && b <= j) return T[x].v;
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        int q1 = tree_query(i, j, lt, a, md);
        int q2 = tree_query(i, j, rt, md + 1, b);
        return q1 + q2;
    }
};


struct Range {
    int a, b;
    Range() {}
    Range(int A, int B) : a(A), b(B) {}
};

int n;
Range ranges[MAXN];
SegTree tree;


int solve()
{
    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int q = tree.query(ranges[i].a, ranges[i].b);

        if (q > 0) {
            ++ans;
            tree.update(ranges[i].a, ranges[i].b);
        }
    }

    return ans;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        tree.init(2*n + 1);

        for (int i = 0; i < n; ++i) {
            int lt = rr.next_u32();
            int rt = rr.next_u32();

            ranges[i] = Range(lt, rt);
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
