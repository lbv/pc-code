// Includes
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <utility>
#include <vector>
using namespace std;

// Macros
#define Sc(t,v) static_cast<t>(v)
#define Zero(v) memset(v, 0, sizeof(v))
#define cIter(t,v) t::const_iterator v
#define For(t,v,c)   for(t::iterator v=c.begin(); v != c.end(); ++v)
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)
#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); ++v)

// Typedefs
typedef unsigned int u32;
typedef long long i64;
typedef vector<int> IV;
typedef pair<int, int> II;
typedef set<II> IIS;

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
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
    bool has_next() { skip(); return b > 0; }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    void next_line(char *s) {
        for (; b != 10 && b != 13 && b != 0; read()) *s++ = b; *s = 0;
        while (b == 10 || b == 13) read(); }
    void next_real_line(char *s) {
        for (; b != 10 && b != 13 && b != 0; read()) *s++ = b; *s = 0;
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

// Union-Find disjoint set
struct Set {
    IV s;
    void init(int n) { s.clear(); for (int i=0; i <= n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

// Graphs
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    void init(int N) { n=N; adj.clear(); adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }

    void prim_min(ELV &g, int src) {
        IIS q;
        IV dis(n, INF);
        BV flg(n);
        dis[src] = 0;
        q.insert(II(0, src));
        while (! q.empty()) {
            int d = q.begin()->first;
            int v = q.begin()->second;
            q.erase(q.begin());
            if (flg[v]) continue;
            flg[v] = true;
            cFor (EL, e, g[v])
                if (!flg[e->v] && e->w < dis[e->v]) {
                    if (dis[e->v] != INF) q.erase(II(dis[e->v], e->v));
                    dis[e->v] = e->w;
                    q.insert(II(dis[e->v], e->v));
                }
        }
    }
    void dijkstra(int src, IV &dis) {
        IIS q;
        dis = IV(n, INF);
        BV flg(n);
        dis[src] = 0;
        q.insert(II(0, src));
        while (! q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());
            if (flg[v]) continue;
            flg[v] = true;
            cFor (EL, e, adj[v]) {
                int d = dis[v] + e->w;
                if (!flg[e->v] && d < dis[e->v]) {
                    if (dis[e->v] != INF) q.erase(II(dis[e->v], e->v));
                    dis[e->v] = d;
                    q.insert(II(dis[e->v], e->v));
                }
            }
        }
    }

    // Kosaraju's algorithm
    struct Kos {
        IVV sccs; IV scc; IK vs; BV vis; ELV radj;
        Kos(int n) { vis = BV(n); radj.resize(n); }
    };
    void kosaraju_scc(IVV &sccs) {
        Kos k(n);
        for (int v=0; v<n; ++v) if (! k.vis[v]) kosaraju_dfs(v, k);
        k.vis = BV(n);
        while (! k.vs.empty()) {
            int v = k.vs.top(); k.vs.pop();
            if (k.vis[v]) continue;
            k.scc = IV();
            kosaraju_dfs2(v, k);
            k.sccs.push_back(k.scc);
        }
        sccs = k.sccs;
    }
    void kosaraju_dfs(int v, Kos &k) {
        k.vis[v] = true;
        cFor (EL, ep, adj[v]) {
            Edge e = *ep;
            int u = e.v; e.v = v;
            k.radj[u].push_back(e);
            if (! k.vis[u]) kosaraju_dfs(u, k);
        }
        k.vs.push(v);
    }
    void kosaraju_dfs2(int v, Kos &k) {
        k.vis[v] = true;
        k.scc.push_back(v);
        cFor (EL, e, k.radj[v])
            if (! k.vis[e->v]) kosaraju_dfs2(e->v, k);
    }
    // Tarjan
    struct Tarjan {
        IVV sccs; IS s; BV flg; IV low, idx; int cnt;
        Tarjan(int n) {
            flg = BV(n);
            low = IV(n);
            idx = IV(n);
            cnt = 1;
        }
    };
    void tarjan_scc(IVV &sccs) {
        Tarjan t(n);
        for (int i = 0; i < n; ++i)
            if (t.low[i] == 0) tarjan_visit(i, t);
        sccs = t.sccs;
    }
    void tarjan_visit(int v, Tarjan &t) {
        t.idx[v] = t.low[v] = t.cnt++;
        t.s.push(v); t.flg[v] = true;
        cFor (EL, e, adj[v]) {
            if (t.low[e->v] == 0) {
                tarjan_visit(e->v, t);
                t.low[v] = min(t.low[v], t.low[e->v]);
            }
            else if (t.flg[e->v])
                t.low[v] = min(t.low[v], t.idx[e->v]);
        }
        if (t.low[v] != t.idx[v]) return;
        IV scc;
        for (int u=-1; u != v;) {
            u=t.s.top(); t.s.pop();
            t.flg[u]=false;
            scc.push_back(u);
        }
        t.sccs.push_back(scc);
    }
    void scc_to_dag(const IVV &sccs, Graph &dag) {
        int ndag = sccs.size();
        IV vcomp(n);
        for (int i=0; i < ndag; ++i)
            for (int j=0, lim=sccs[i].size(); j < lim; ++j)
                vcomp[sccs[i][j]] = i;
        dag.init(ndag);
        for (int u=0; u < n; u++)
            cFor (EL, e, adj[u])
                if (vcomp[u] != vcomp[e->v])
                    dag.add(vcomp[u], vcomp[e->v], 0);
    }
    // Hopcroft-Karp for bipartite matching. Receives the vertices in G1,
    // and depends on vertex #0 being reserved as the NIL vertex
    struct HK {
        IV pair_g1, pair_g2, dist;
        Graph &g;
        IV &g1;
        HK(Graph &G, IV &G1) : g(G), g1(G1) {
            pair_g1 = IV(g.n); pair_g2 = IV(g.n); dist = IV(g.n); }
        bool bfs() {
            IQ q;
            cFor (IV, v, g1) {
                if (pair_g1[*v] == 0) {
                    dist[*v] = 0;
                    q.push(*v);
                }
                else
                    dist[*v] = INF;
            }
            dist[0] = INF;
            while (! q.empty()) {
                int v = q.front(); q.pop();
                cFor (EL, e, g.adj[v]) {
                    int p = pair_g2[e->v];
                    if (dist[p] != INF) continue;
                    dist[p] = dist[v] + 1;
                    q.push(p);
                }
            }
            return dist[0] != INF;
        }
        bool dfs(int v) {
            if (v == 0) return true;
            cFor (EL, e, g.adj[v]) {
                int p = pair_g2[e->v];
                if (dist[p] == dist[v] + 1 && dfs(p)) {
                    pair_g2[e->v] = v;
                    pair_g1[v] = e->v;
                    return true;
                }
            }
            dist[v] = INF;
            return false;
        }
    };
    int hopcroft(IV &g1) {
        HK hk(*this, g1);
        int m = 0;
        while (hk.bfs())
            cFor (IV, v, g1)
                if (hk.pair_g1[*v] == 0 && hk.dfs(*v))
                    ++m;
        return m;
    }
    // Articulations/bridges
    struct Artic {
        IV low, idx;
        BV is_art;
        IIV bridges;
        int cnt;
        Graph &g;
        Artic(Graph &G) : g(G) {
            low = IV(g.n);
            idx = IV(g.n);
            is_art = BV(g.n);
            cnt = 1;
        }
        void dfs(int u, int v) {
            int children = 0;
            low[v] = idx[v] = cnt++;
            cFor(EL, e, g.adj[v]) {
                if (idx[e->v] == 0) {
                    ++children;
                    dfs(v, e->v);
                    low[v] = min(low[v], low[e->v]);
                    if (low[e->v] >= idx[v] && u != v)
                        is_art[v] = true;
                    if (low[e->v] == idx[e->v])
                        bridges.push_back(II(v, e->v));
                }
                else if (e->v != u)
                    low[v] = min(low[v], idx[e->v]);
            }
            if (u == v && children > 1)
                is_art[v] = true;
        }
    };
    void articulations(IIV &bridges) {
        Artic a(*this);
        for (int i = 0; i < n; ++i)
            if (a.idx[i] == 0) a.dfs(i, i);
        bridges = a.bridges;
    }
};
struct Graph {
    struct Edge {
        int u, v, w;
        Edge(int U, int V, int W) : u(U), v(V), w(W) {}
        bool operator<(const Edge &e) const { return w < e.w; }
    };
    typedef vector<Edge> EV;
    EV edges;
    void init(size_t m=16) { edges.clear(); edges.reserve(m); }
    void add(int u, int v, int w) { edges.push_back(Edge(u, v, w)); }

    // Minimum Spanning Tree
    void kruskalMST(int n, int &ans) {
        sort(edges.begin(), edges.end());
        Set uf; uf.init(n);
        int nedges = 0;
        ans = 0;
        EV mst;
        cFor (EV, e, edges) {
            if (uf.find(e->u) == uf.find(e->v)) continue;
            mst.push_back(*e);
            uf.merge(e->u, e->v);
            ans += e->w;
            if (++nedges == n - 1) break;
        }
        if (nedges < n - 1) ans = -1;
        else edges = mst;
    }

    // Bellman-Ford
    bool bellman_ford_neg_cycle(int n) {
        IV dis(n);
        for (int i = 0; i < n-1; i++)
            cFor (EV, e, edges)
                if(dis[e->u] + e->w < dis[e->v])
                    dis[e->v] = dis[e->u] + e->w;
        cFor (EV, e, edges)
            if (dis[e->u] + e->w < dis[e->v])
                return true;
        return false;
    }
};

struct Graph {
    // Shortest paths
    void floyd(int **g, int N)
    {
        for (int k = 0; k < N; k++)
            for(int i = 0; i < N; i++)
                for (int j = 0; j < N; j++) {
                    int t = g[i][k] + g[k][j];
                    if (t < g[i][j]) g[i][j] = t;
                }
    }
};

// 2-SAT
struct TwoSat {
    Graph g;
    int n;
    TwoSat(int N) : n(N) { g.init(2*N); }
    void add_cons(int a, bool ta, int b, bool tb) {
        int p = val(a, ta), q = val(b, tb);
        g.add(neg(p), q); g.add(neg(q), p);
    }
    int val(int v, bool t) { return 2*v + (t ? 0 : 1); }
    int neg(int p) { return p ^ 1; }
    bool solve(IV &sol) {
        IVV sccs;
        g.kosaraju_scc(sccs);
        IV vscc(n);
        sol.clear();
        for (int i = 0, I = sccs.size(); i < I; ++i) {
            for (int j=0, J=sccs[i].size(); j < J; ++j) {
                int p = sccs[i][j];
                int v = p/2;
                if (vscc[v] == i+1) return false;
                if (vscc[v] != 0) break;
                vscc[v] = i+1;
                if (p & 1) sol.push_back(v);
            }
        }
        return true;
    }
};

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000000;  // 10^6
    const int LMT =    1000;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void prime_sieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
    // Finds prime numbers between a and b, using basic primes up to sqrt(b)
    void prime_seg_sieve(i64 a, i64 b, IV &seg_primes) {
        BV pmap(b - a + 1, true);
        i64 sqr_b = sqrt(b);
        cFor (IV, pp, primes) {
            int p = *pp;
            if (p > sqr_b) break;
            for (i64 j = (a+p-1)/p, v=(j==1?p+p:j*p); v <= b; v += p)
                pmap[v-a] = false;
        }
        seg_primes.clear();
        if (a == 1) pmap[0] = false;
        for (int i = a%2 ? 0 : 1, I = b - a + 1; i < I; i += 2)
            if (pmap[i])
                seg_primes.push_back(a + i);
    }
    void prime_factorize(int n, IIV &f) {
        int sn = sqrt(n);
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            f.push_back(II(prime, e));
            sn = sqrt(n);
        }
        if (n > 1) f.push_back(II(n, 1));
    }
    void euler_phi(int a[], int N) {
        for (int i = 1; i <= N; i++) a[i] = i;
        for (int i = 2; i <= N; i += 2) a[i] = i/2;
        for (int i = 3; i <= N; i += 2)
            if (a[i] == i) {
                a[i]--; for (int j = i+i; j <= N; j += i) a[j] -= a[j]/i;
            }
    }
    int mod_pow(int _b, i64 e, int m) {
        i64 res = 1;
        for (i64 b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
        return res;
    }
    int ipow(int b, int e) {
        int res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
        return res;
    }
    int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }
    void ext_euclid(int a, int b, int &x, int &y, int &gcd) {
        x = 0; y = 1; gcd = b;
        int m, n, q, r;
        for (int u=1, v=0; a != 0; gcd=a, a=r) {
            q = gcd / a; r = gcd % a;
            m = x-u*q; n = y-v*q;
            x=u; y=v; u=m; v=n;
        }
    }
    int mod_inv(int n, int m) {
        int x, y, gcd;
        ext_euclid(n, m, x, y, gcd);
        if (gcd == 1) return x % m;
        return 0;
    }
    // Calculates the highest exponent of prime p that divides n!
    int pow_div_fact(int n, int p) {
        int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
    }

    // Binomial coefficients
#define BCSIZE 1000
    int bc[BCSIZE + 1][BCSIZE + 1];
    void choose_table() {
        for (int n = 1; n <= BCSIZE; n++) { bc[n][n] = 1; bc[n][1] = n; }
        for (int n = 3; n <= BCSIZE; n++)
            for (int k = 2; k < n; k++)
                bc[n][k] = (bc[n-1][k-1] + bc[n-1][k]) % MOD;
    }
    int choose(int n, int k) {
        if (k > n) return 0;
        i64 r=1;
        for (int d = 1; d <= k; d++) {
            r *= n--;
            r /= d;
        }
        return r;
    }
}

// Big Integer
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct Bigint {
    IV d; bool sgn;
    Bigint(i64 n=0) {
        if (n < 0) sgn = true, n = -n; else sgn = false;
        if (n < BIBAS) d.push_back(n);
        else while (n != 0) { d.push_back(n % BIBAS); n /= BIBAS; }
    }
    Bigint(const char *s) {
        if (*s == '-') sgn = true, s++; else sgn = false;
        for (int end = strlen(s), i = max(0, end-BIDIG); true;) {
            int n = 0; for (int j=i; j != end; j++) n = n*10 + s[j] - '0';
            d.push_back(n); if (i == 0) break;
            end = i, i = max(0, i-BIDIG);
        } clean();
    }
    size_t len() const { return d.size(); }
    Bigint neg() const { Bigint x = *this; x.sgn = !x.sgn; return x; }
    void flip() { sgn = !sgn; }
    bool operator==(const Bigint &b) const {
        return sgn == b.sgn && d == b.d;
    }
    bool operator<(const Bigint &b) const {
        if (sgn && !b.sgn) return true;
        if ((!sgn) && b.sgn) return false;
        if (d.size() < b.d.size()) return true;
        if (d.size() > b.d.size()) return false;
        for (int i = d.size() - 1; i >= 0; --i) {
            if (d[i] < b.d[i]) return true;
            else if (d[i] > b.d[i]) return false;
        }
        return false;
    }
    Bigint &operator*=(const Bigint &b) {
        int s1 = len(), s2 = b.len(), s3 = s1+s2;
        IV res(s3); int c = 0;
        for (int k=0; k < s3; ++k) {
            int sum = c;
            for (int i=max(0,k-s2+1), I=min(k+1, s1), j=k-i; i < I; ++i, --j)
                sum += d[i] * b.d[j];
            if (sum >= BIBAS) { c = sum / BIBAS; sum %= BIBAS; } else c = 0;
            res[k] = sum;
        }
        d = res; sgn ^= b.sgn; clean();
        return *this;
    }
    Bigint &operator+=(const Bigint &b) {
        if (sgn != b.sgn) { (*this) -= b.neg(); return *this; }
        int s1 = len(), s2 = b.len(), s3 = max(s1, s2) + 1;
        IV res(s3); int c = 0;
        for (int i = 0; i < s3; ++i) {
            int sum = c;
            sum += i < s1 ? d[i] : 0;
            sum += i < s2 ? b.d[i] : 0;
            if (sum >= BIBAS) { c = sum / BIBAS; sum %= BIBAS; } else c = 0;
            res[i] = sum;
        }
        d = res; clean();
        return *this;
    }
    Bigint &operator-=(const Bigint &b) {
        if (sgn != b.sgn) { (*this) += b.neg(); return *this; }
        if (*this < b) { Bigint x = b; x -= *this; return *this = x.neg(); }
        int s1 = len(), s2 = b.len(), s3 = s1;
        IV res(s3); int c = 0;
        for (int i = 0; i < s3; ++i) {
            int sum = d[i] - (i < s2 ? b.d[i] : 0) - c;
            if (sum < 0) { sum += BIBAS; c = 1; } else c = 0;
            res[i] = sum;
        }
        d = res; clean();
        return *this;
    }
    Bigint pow(int e) {
        if (e == 0) return Bigint(1);
        if (e == 1) return *this;
        if (e % 2 == 0) {
            Bigint tmp = this->pow(e/2);
            tmp *= tmp;
            return tmp;
        }
        Bigint tmp = this->pow(e-1);
        tmp *= *this;
        return tmp;
    }
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
    void println() {
        if (sgn) putchar('-');
        bool flg = true;
        crFor (IV, i, d) {
            if (flg) { printf("%d", *i); flg=false; }
            else printf(BIFMT, *i);
        } putchar('\n');
    }
    int to_int() {
        int res = 0, p = 1;
        for (int i=0, I=len(); i < I; i++) { res += d[i] * p; p *= BIBAS; }
        return sgn ? -res : res;
    }
    string to_string() {
        char buf[BIDIG+1]; string str;
        if (sgn) str.push_back('-');
        bool flg = true;
        crFor (IV, i, d) {
            if (flg) { sprintf(buf, "%d", *i); flg=false; }
            else sprintf(buf, BIFMT, *i);
            str.append(buf);
        }
        return str;
    }
};

// Fraction
struct Fraction {
    int p, q;

    Fraction(int P, int Q) : p(P), q(Q) { simplify(); }
    Fraction(int P) : p(P), q(1) {}
    void simplify() {
        int g = gcd(p, q);
        p /= g;
        q /= g;
    }
    Fraction operator+(const Fraction &f) const {
        return Fraction(p * f.q + q * f.p, q * f.q);
    }
    Fraction operator-(const Fraction &f) const {
        return Fraction(p * f.q - q * f.p, q * f.q);
    }
    Fraction operator*(const Fraction &f) const {
        return Fraction(p * f.p, q * f.q);
    }
    Fraction operator/(const Fraction &f) const {
        return Fraction(p * f.q, q * f.p);
    }
    Fraction operator%(int m) const {
        return Fraction(p % (m*q), q);
    }
};

// Matrix Exponentiation
typedef u32 t_m;
#define MAXR (MAXK + 2)
#define MAXC (MAXK + 2)
struct Matrix {
    int r, c;
    t_m m[MAXR][MAXC];
    void init(int R, int C) { Zero(m); r=R; c=C; }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j)
                printf("%4d  ", m[i][j]);
            printf("\n");
        }
    }
};

void matrix_mul(const Matrix &a, const Matrix &b, Matrix &c)
{
    c.r = a.r, c.c = b.c;
    t_m x;
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j) {
            x = 0;
            for (int k = 0; k < a.c; ++k)
                x += a.m[i][k] * b.m[k][j];
            c.m[i][j] = x;
        }
}

void matrix_exp(const Matrix &m, u64 e, Matrix &r)
{
    if (e == 1) { r = m; return; }

    Matrix x;
    if (e % 2 == 0) {
        matrix_exp(m, e / 2, x);
        matrix_mul(x, x, r);
        return;
    }

    matrix_exp(m, e-1, x);
    matrix_mul(x, m, r);
}


// Geometry
namespace Geometry {
    const double Eps = 1e-6;
    double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }
    bool eps_eq(double a, double b) { return abs(a-b) <= Eps; }
}

typedef double p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    p_t distance(Point p) {
        p_t dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    bool collinear(const Point &b, const Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
    }
};
struct Vector {
    p_t x, y;
    Vector(p_t X, p_t Y) : x(X), y(Y) {}
    Vector(const Point &p) : x(p.x), y(p.y) {}
    double norm() { return sqrt(x*x + y*y); }
    double angle(const Vector &p) const {
        return Geometry::circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
    void rotate(double a) {
        p_t px = x, py = y;
        x = px*cos(a) - py*sin(a);
        y = px*sin(a) + py*cos(a);
    }
    double distance_line_point(Point a, Point p) {
        return fabs((p.x-a.x)*y - (p.y-a.y)*x) / sqrt(x*x + y*y);
    }
};
typedef vector<Point> PV;
namespace Geometry {
    p_t cross(const Point &o, const Point &a, const Point &b) {
        return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
    }
    void convex_hull(PV &p, PV &h) {
        // Post-cond: p.size() > 1 => h.front() == h.back()
        int n = p.size(), k = 0;
        h.resize(2*n);
        sort(p.begin(), p.end());
        for (int i = 0; i < n; ++i) {
            while (k >= 2 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
            h[k++] = p[i];
        }
        for (int i = n-2, t=k+1; i >= 0; --i) {
            while (k >= t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
            h[k++] = p[i];
        }
        h.resize(k);
    }
}

// Trie
struct Trie {
    struct Node {
        int ch[26];
        int n;
        Node() { n=0; Zero(ch); }
    };
    int sz;
    vector<Node> nodes;
    void init() { nodes.clear(); nodes.resize(1); sz = 1; }
    void insert(const char *s) {
        int idx, cur = 0;

        while (*s) {
            idx = *s - 'A';
            if (! nodes[cur].ch[idx]) {
                nodes[cur].ch[idx] = sz++;
                nodes.resize(sz);
            }

            cur = nodes[cur].ch[idx];
            ++s;
        }
    }
};

// Misc functions

// next higher number with same number of 1's in binary
u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
// Returns first integer with exactly n bits set
u32 init_popcount(int n) { return (1 << n) - 1; }
// Finds the most significant bit set on n. The bit is left in b, and its
// zero-indexed position in p
void msb(i64 n, i64 &b, int &p)
{
    for (b = 1, p = 0, n >>= 1; n; b <<= 1, n >>= 1, ++p);
}

// returns the position of the last visited in range [0, n-1]
int josephus(int n, int k)
{
    if (n == 1) return 0;
    return (josephus(n-1, k) + k) % n;
}
