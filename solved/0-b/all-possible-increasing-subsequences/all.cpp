#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100000
#define MOD  1000000007

#define Back(b) ((b) & -(b))


typedef vector<int> IV;

struct Node {
    int v, i;  // value, index
    Node(int V, int I) : v(V), i(I) {}
    bool operator<(const Node &x) const {
        if (v != x.v) return v < x.v;
        return i > x.i;
    }
};
typedef vector<Node> NV;


//
// I/O
//
#define BUF 524288
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

//
// Binary Indexed Tree
//
struct Bit {
    IV f; int n;
    Bit(int N) : n(N) { f = IV(N + 1); }
    void add(int i, int v) {
        while (i <= n) {
            f[i] += v;
            f[i] %= MOD;
            i += Back(i);
        }
    }
    int query(int i) {
        int r = 0;
        while (i) {
            r += f[i];
            r %= MOD;
            i -= Back(i);
        }
        return r;
    }
};


int n;


int solve(NV &ns)
{
    sort(ns.begin(), ns.end());
    Bit tree(n);

    for (int i = 0; i < n; ++i) {
        int v = tree.query(ns[i].i - 1);
        tree.add(ns[i].i, v + 1);
    }

    return tree.query(n);
}

int main()
{
    Reader rr;
    int T = rr.next_int();

    int ncase = 0;
    while (T--) {
        n = rr.next_int();

        NV ns;
        for (int i = 1; i <= n; ++i)
            ns.push_back(Node(rr.next_int(), i));

        printf("Case %d: %d\n", ++ncase, solve(ns));
    }

    return 0;
}
