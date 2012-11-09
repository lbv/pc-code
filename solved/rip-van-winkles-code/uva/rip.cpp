#include <cstdio>
#include <cstring>


#define ARRAYSZ 250001

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;
typedef long long    i64;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    char next_char() { skip(); char c = b; read(); return c; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

i64 memosum[ARRAYSZ];
i64 sum(int n)
{
    if (n == 0) return 0;
    if (memosum[n] != 0) return memosum[n];

    i64 s = n;
    s *= n + 1;
    s /= 2;

    return memosum[n] = s;
}

struct Node {
    i64 v;   // sum of all numbers in range

    int a, b, x;
    i64 d;
    bool c;
};

#define MAXH 19  // 1 + ceil(log2(ARRAYSZ))
struct SegTree {
    Node T[1 << MAXH];
    int n;

    void init(int N) { n = N; Zero(T); }

    void propagate(int x, int a, int b) {
        if (! T[x].c && T[x].a == 0 && T[x].b == 0) return;

        if (T[x].c) {
            i64 val = T[x].x;
            val *= (b - a + 1);
            T[x].v = val;
        }

        T[x].v += (b - a + 1) * T[x].d;
        T[x].v += sum(b - a + 1) * (T[x].a + T[x].b);

        if (a != b) {
            int lt = 2*x, rt = lt + 1, md = (a+b)/2;

            if (T[x].c) {
                T[lt].c = T[rt].c = true;
                T[lt].a = T[rt].a = T[lt].b = T[rt].b = 0;
                T[lt].d = T[rt].d = 0;
                T[lt].x = T[rt].x = T[x].x;
            }

            T[lt].a += T[x].a;
            T[lt].b += T[x].b;

            T[rt].a += T[x].a;
            T[rt].b += T[x].b;

            i64 delta = md + 1 - a;
            delta *= T[x].a;
            T[rt].d += T[x].d + delta;

            delta = b - md;
            delta *= T[x].b;
            T[lt].d += T[x].d + delta;
        }

        T[x].d = 0;
        T[x].a = T[x].b = T[x].x = 0;
        T[x].c = false;
    }

    void inc_left(int i, int j) { tree_inc_left(i, j, 1, 0, n-1); }
    void tree_inc_left(int i, int j, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v += a - i + 1; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x].v += sum(b - i + 1) - sum(a - i);

            T[lt].d += a - i;
            ++T[lt].a;

            T[rt].d += md + 1 - i;
            ++T[rt].a;

            return;
        }
        tree_inc_left(i, j, lt, a, md);
        tree_inc_left(i, j, rt, md + 1, b);
        T[x].v = T[rt].v + T[lt].v;
    }

    void inc_right(int i, int j) { tree_inc_right(i, j, 1, 0, n-1); }
    void tree_inc_right(int i, int j, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v += j - b + 1; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x].v += sum(j - a + 1) - sum(j - b);

            T[lt].d += j - md;
            ++T[lt].b;

            T[rt].d += j - b;
            ++T[rt].b;

            return;
        }
        tree_inc_right(i, j, lt, a, md);
        tree_inc_right(i, j, rt, md + 1, b);
        T[x].v = T[rt].v + T[lt].v;
    }

    void set(int i, int j, int v) { tree_set(i, j, v, 1, 0, n-1); }
    void tree_set(int i, int j, int v, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v = v; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            i64 val = v;
            val *= (b - a + 1);
            T[x].v = val;

            T[lt].x = T[rt].x = v;
            T[lt].c = T[rt].c = true;

            T[lt].a = T[lt].b = 0;
            T[rt].a = T[rt].b = 0;

            T[lt].d = T[rt].d = 0;
            return;
        }
        tree_set(i, j, v, lt, a, md);
        tree_set(i, j, v, rt, md + 1, b);
        T[x].v = T[rt].v + T[lt].v;
    }

    i64 query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
    i64 tree_query(int i, int j, int x, int a, int b) {
        if (j < a || i > b) return 0;
        propagate(x, a, b);
        if (a >= i && b <= j) return T[x].v;
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        i64 q1 = tree_query(i, j, lt, a, md);
        i64 q2 = tree_query(i, j, rt, md + 1, b);
        return q1 + q2;
    }
};


int N;
SegTree tree;


int main()
{
    Reader rr;

    N = rr.next_u32();
    tree.init(ARRAYSZ);

    char op;
    int i, j, x;
    while (N--) {
        op = rr.next_char();
        i = rr.next_u32();
        j = rr.next_u32();

        switch (op) {
        case 'A':
            tree.inc_left(i, j);
            break;

        case 'B':
            tree.inc_right(i, j);
            break;

        case 'C':
            x = rr.next_int();
            tree.set(i, j, x);
            break;

        case 'S':
            printf("%lld\n", tree.query(i, j));
            break;
        }
    }

    return 0;
}
