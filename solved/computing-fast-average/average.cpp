#include <cstdio>
#include <cstring>


#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


#define MAXN 100000
#define MAXH 18  // 1 + ceil(log2(MAXN))
struct SegTree {
    struct Node {
        int v;
        bool u;
    };

    Node T[1 << MAXH];
    int n;

    void init(int N) { n = N; Zero(T); }

    void propagate(int x, int a, int b) {
        if (! T[x].u) return;
        int val = T[x].v * (b - a + 1);
        if (a != b) {
            int lt = 2*x, rt = lt + 1;
            T[lt].v = T[rt].v = T[x].v;
            T[lt].u = T[rt].u = true;
        }
        T[x].v = val;
        T[x].u = false;
    }

    void update(int i, int j, int v) { tree_update(i, j, v, 1, 0, n-1); }
    void tree_update(int i, int j, int v, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v = v; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x].v = v * (b - a + 1);
            T[lt].v = T[rt].v = v;
            T[lt].u = T[rt].u = true;
            return;
        }
        tree_update(i, j, v, lt, a, md);
        tree_update(i, j, v, rt, md + 1, b);
        T[x].v = T[rt].v + T[lt].v;
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


int n, q;
SegTree tree;


int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

void print_ans(int p, int q)
{
    int g = gcd(p, q);
    p /= g;
    q /= g;

    if (q == 1)
        printf("%d\n", p);
    else
        printf("%d/%d\n", p, q);
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        q = rr.next_u32();

        tree.init(n);
        printf("Case %d:\n", ++ncase);

        int op, i, j, v, sum;
        while (q--) {
            op = rr.next_u32();
            i  = rr.next_u32();
            j  = rr.next_u32();

            if (op == 1) {
                v = rr.next_u32();
                tree.update(i, j, v);
            }
            else {
                sum = tree.query(i, j);
                print_ans(sum, j - i + 1);
            }
        }
    }

    return 0;
}
