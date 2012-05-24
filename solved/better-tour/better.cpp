#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 50000

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef unsigned int u32;
typedef vector<int> IV;
typedef queue<int> IQ;

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

int n, first, last;
IV edges[MAXN + 1];
bool visit[MAXN + 1];
int parent[MAXN + 1];

void solve()
{
    IQ q;
    q.push(first);

    Zero(visit);
    Zero(parent);
    visit[first] = true;

    while (! q.empty()) {
        int u = q.front(); q.pop();

        if (u == last) return;

        sort(edges[u].begin(), edges[u].end());
        cFor (IV, pv, edges[u]) {
            int v = *pv;
            if (visit[v]) continue;

            q.push(v);
            visit[v] = true;
            parent[v] = u;
        }
    }
}

void dfs(int v)
{
    if (v == first) {
        printf("%d", v);
        return;
    }

    dfs(parent[v]);
    printf(" %d", v);
}

void print_sol()
{
    dfs(last);
    putchar('\n');
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();

        int curr, prev = 0;
        Zero(visit);

        for (int i = 1; i <= n; ++i) {
            curr = rr.next_u32();
            if (! visit[curr]) {
                edges[curr].clear();
                visit[curr] = true;
            }

            if (i == 1) {
                prev = first = curr;
                continue;
            }

            if (i == n)
                last = curr;

            edges[prev].push_back(curr);
            edges[curr].push_back(prev);

            prev = curr;
        }

        solve();

        printf("Case %d:\n", ++ncase);
        print_sol();
    }

    return 0;
}
