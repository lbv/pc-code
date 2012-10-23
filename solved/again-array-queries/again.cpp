#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;


#define MAXI 1000
#define MAXQ 10000
#define MAXN 100000

const int INF = MAXI + 10;

#define Neg(v)  memset((v), -1, sizeof(v))


typedef unsigned int u32;

typedef pair<int, int> II;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};


struct Query {
    int i, j, q;
    Query() {}
    Query(int I, int J, int Q) : i(I), j(J), q(Q) {}
    bool operator<(const Query &x) const { return j < x.j; }
};


int n, q;
int A[MAXN + 1];

// last[n]: the index of the last occurrence of n
int last[MAXI + 1];

// nlst[n]: the index of the next-to-last occurrence of n
int nlst[MAXI + 1];

Query qs[MAXQ];
II sol[MAXQ];


int mindiff(int from)
{
    int best = INF;

    int prev = -INF;
    for (int i = 0; i <= MAXI; ++i) {
        if (nlst[i] >= from) return 0;
        if (last[i] >= from) {
            int curr = i - prev;
            if (curr < best) best = curr;

            prev = i;
        }
    }
    return best;
}

void solve()
{
    sort(qs, qs + q);

    Neg(last);
    Neg(nlst);
    int idx = -1;
    for (int i = 0; i < q; ++i) {
        while (idx < qs[i].j) {
            int num = A[++idx];
            nlst[num] = last[num];
            last[num] = idx;
        }

        sol[i] = II(qs[i].q, mindiff(qs[i].i));
    }

    sort(sol, sol + q);
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        q = rr.next_u32();

        for (int i = 0; i < n; ++i)
            A[i] = rr.next_u32();

        for (int k = 0; k < q; ++k) {
            int i = rr.next_u32();
            int j = rr.next_u32();
            qs[k] = Query(i, j, k);
        }

        solve();

        printf("Case %d:\n", ++ncase);
        for (int i = 0; i < q; ++i)
            printf("%d\n", sol[i].second);
    }

    return 0;
}
