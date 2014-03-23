#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 100000
#define MAXI 100000

#define Zero(v) memset((v), 0, sizeof(v))
#define Neg(v)  memset((v), -1, sizeof(v))
#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define GetFS(b) ((b) & -(b))


typedef unsigned int u32;

typedef pair<int, int> II;

typedef vector<II> IIV;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct Bit {
    int f[MAXN + 1]; int n;
    void init(int N) { n=N; Zero(f); }
    void add(int i, int v) { while (i <= n) { f[i] += v; i += GetFS(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= GetFS(i); } return r; }
};

struct Query {
    int i, j, q;
    Query(int I, int J, int Q) : i(I), j(J), q(Q) {}
    bool operator<(const Query &x) const { return j < x.j; }
};
typedef vector<Query> QV;


int N, q;
int last[MAXI + 1];
int ns[MAXN + 1];
Bit tree;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        q = rr.next_u32();

        for (int i = 1; i <= N; ++i)
            ns[i] = rr.next_u32();

        QV qs;
        for (int k = 0; k < q; ++k) {
            int i = rr.next_u32();
            int j = rr.next_u32();

            qs.push_back(Query(i, j, k));
        }
        sort(qs.begin(), qs.end());

        tree.init(N);

        IIV ans;

        int idx = 0;
        Neg(last);
        For (QV, q, qs) {
            while (idx < q->j) {
                int num = ns[++idx];
                if (last[num] != -1)
                    tree.add(last[num], -1);
                tree.add(idx, 1);
                last[num] = idx;
            }
            int distinct = tree.query(idx) - tree.query(q->i - 1);
            ans.push_back(II(q->q, distinct));
        }

        printf("Case %d:\n", ++ncase);
        sort(ans.begin(), ans.end());
        For (IIV, a, ans)
            printf("%d\n", a->second);
    }

    return 0;
}
