#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100000
#define INF  100000010


typedef unsigned int u32;

typedef vector<int> IV;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};


#define MAXH 18  // 1 + ceil(log2(MAXN))
struct SegTree {
    IV H, L;
    int n;
    SegTree() {
        H.resize(1 << MAXH);
        L.resize(1 << MAXH);
    }

    void init(int N) { n = N; tree_init(1, 0, n-1); }
    void tree_init(int x, int a, int b) {
        H[x] = -1; L[x] = INF;
        if (a == b) { return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        tree_init(lt, a, md);
        tree_init(rt, md + 1, b);
    }

    int update(int i, int v) {
        tree_update(i, v, 1, 0, n-1);
        return H[1] - L[1];
    }
    void tree_update(int i, int v, int x, int a, int b) {
        if (i < a || i > b) return;
        if (a == b) { H[x] = L[x] = v; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        tree_update(i, v, lt, a, md);
        tree_update(i, v, rt, md + 1, b);
        H[x] = max(H[lt], H[rt]);
        L[x] = min(L[lt], L[rt]);
    }
};


int n, d;
SegTree tree;


int main()
{
    Reader rr;

    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        d = rr.next_u32();

        tree.init(d);

        int best = 0;
        for (int i = 0; i < n; ++i) {
            int v = rr.next_u32();

            int diff = tree.update(i % d, v);
            if (diff > best) best = diff;
        }
        printf("Case %d: %d\n", ++ncase, best);
    }

    return 0;
}
