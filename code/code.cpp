// Macros
#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define RFor(t,v,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)

// Typedefs
typedef unsigned int u32;
typedef long long i64;
typedef vector<int> IV;
typedef pair<int, int> II;
typedef set<II> IIS;

//
// I/O
//
struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    char next_char() { skip(); char c = b; read(); return c; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
    bool has_next() { skip(); return b > 0; }
    void skip_line() {
        for (; b != 10 && b != 13 && b != 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next_line(char *s) {
        for (; b != 10 && b != 13 && b != 0; read()) *s++ = b; *s = 0;
        while (b == 10 || b == 13) read(); }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};
struct LineReader {
    char b; LineReader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }
};

// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i=0; i < n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

//
// Graphs - Basic structures
//

// Adjacency lists
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};

// Weighted adjacency lists
typedef int w_t;
struct Graph {
    struct Edge { int v; w_t w; Edge(int V, w_t W) : v(V), w(W) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v, w_t w) { adj[u].push_back(Edge(v, w)); }
};

// List of edges
struct Graph {
    struct Edge {
        int u, v; w_t w;
        Edge(int U, int V, w_t W) : u(U), v(V), w(W) {}
        bool operator<(const Edge &e) const { return w < e.w; }
    };
    typedef vector<Edge> EV;
    EV edges;
    void add(int u, int v, w_t w) { edges.push_back(Edge(u, v, w)); }
};

//
// Graphs - Algorithms
//
struct Graph {
    int prim_mst(int src) {
        IIS q;
        IV dis(n, INF);
        BV flg(n);
        dis[src] = 0;
        q.insert(II(0, src));
        int mst = 0;
        while (! q.empty()) {
            int d = q.begin()->first;
            int v = q.begin()->second;
            q.erase(q.begin());
            if (flg[v]) continue;
            flg[v] = true;
            mst += d;
            For (EL, e, adj[v])
                if (!flg[e->v] && e->w < dis[e->v]) {
                    dis[e->v] = e->w;
                    q.insert(II(dis[e->v], e->v));
                }
        }
        return mst;
    }
    void dijkstra(int src, IV &dis) {
        set<II> q;
        dis = IV(n, INF);
        BV vis(n);
        q.insert(II(0, src));
        dis[src] = 0;
        while (! q.empty()) {
            II p = *(q.begin()); q.erase(q.begin());
            int d = p.first, v = p.second;
            if (vis[v]) continue;
            vis[v] = true;
            For (EL, e, adj[v]) {
                int d2 = d + e->w;
                if (d2 < dis[e->v]) {
                    dis[e->v] = d2;
                    q.insert(II(d2, e->v));
                }
            }
        }
    }
    void topo_sort(IV &in, IV &order) {
        IQ q;
        for (int i = 0; i < n; ++i) if (in[i] == 0) q.push(i);
        order.clear();
        while (! q.empty()) {
            int v = q.front(); q.pop();
            order.push_back(v);
            For (EL, e, adj[v])
                if (--in[e->v] == 0) q.push(e->v);
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
        dag = Graph(ndag);
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
            For (EL, e, g.adj[v]) {
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
    // Eulerian Trail
    struct Euler {
        ELV adj; IV t;
        Euler(ELV Adj) : adj(Adj) {}
        void build(int u) {
            while(! adj[u].empty()) {
                int v = adj[u].front().v;
                adj[u].erase(adj[u].begin());
                build(v);
            }
            t.push_back(u);
        }
    };
    bool eulerian_trail(IV &trail) {
        Euler e(adj);
        int odd = 0, s = 0;
        /*
        for (int v = 0; v < n; v++) {
            int diff = abs(in[v] - out[v]);
            if (diff > 1) return false;
            if (diff == 1) {
                if (++odd > 2) return false;
                if (out[v] > in[v]) start = v;
            }
        }
        */
        e.build(s);
        reverse(e.t.begin(), e.t.end());
        trail = e.t;
        return true;
    }

    // Minimum Spanning Tree
    void kruskal_mst(int n, int &ans) {
        sort(edges.begin(), edges.end());
        Set uf(n);
        int nedges = 0;
        ans = 0;
        EV mst;
        For (EV, e, edges) {
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
            For (EV, e, edges)
                if(dis[e->u] + e->w < dis[e->v])
                    dis[e->v] = dis[e->u] + e->w;
        For (EV, e, edges)
            if (dis[e->u] + e->w < dis[e->v])
                return true;
        return false;
    }

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
}

//
// 2-SAT
//
struct TwoSat {
    Graph g;
    int n;
    TwoSat(int N) : n(N) { g = Graph(2*N); }
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

//
// Number Theory
//
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
    bool is_prime(int n) {
        if (n < 2 || (n > 2 && n % 2 == 0)) return false;
        return ! IsComp(n);
    }
    // Finds prime numbers between a and b, using basic primes up to sqrt(b)
    // pre cond: a > 2 (handle that separately)
    void prime_seg_sieve(i64 a, i64 b, IV &seg_primes) {
        BV pmap(b - a + 1, true);
        i64 sqr_b = sqrt(b);
        For (IV, pp, primes) {
            int p = *pp;
            if (p > sqr_b) break;
            for (i64 j = (a+p-1)/p, v=(j==1?p+p:j*p); v <= b; v += p)
                pmap[v-a] = false;
        }
        seg_primes.clear();
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
    void divisors(int n, IV &ds)
    {
        ds.clear();
        ds.push_back(1);
        int sn = sqrt(n);
        For (IV, pp, primes) {
            int p = *pp;
            if (p > sn) break;
            if (n % p != 0) continue;
            IV aux(ds.begin(), ds.end());
            int q = 1;
            while (n % p == 0) {
                q *= p; n /= p;
                cFor(IV, v, ds) aux.push_back(*v * q);
            }
            sn = sqrt(n); ds = aux;
        }
        if (n > 1) {
            IV aux(ds.begin(), ds.end());
            For (IV, v, ds) aux.push_back(*v * n);
            ds = aux;
        }
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

//
// Big Integer
//
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
    bool is_zero() const { return len() == 1 && d[0] == 0; }
    void flip() { sgn = !sgn; }
    Bigint neg() const { Bigint x = *this; x.flip(); return x; }
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
    bool operator==(const Bigint &b) const {
        return sgn == b.sgn && d == b.d;
    }
    bool operator<(const Bigint &b) const {
        if (sgn != b.sgn) return sgn;
        if (len() != b.len()) return sgn ^ (len() < b.len());
        for (int i = len() - 1; i >= 0; --i)
            if (d[i] != b.d[i]) return sgn ^ (d[i] < b.d[i]);
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
    Bigint &short_div(int b) {
        for (int r = 0, i = len() - 1; i >= 0; --i)
            r = r*BIBAS + d[i], d[i] = r / b, r %= b;
        clean(); return *this;
    }
    Bigint &operator/=(const Bigint &b) {
        if (b.is_zero()) { int x=0; return *this=Bigint(x/x); }
        sgn ^= b.sgn; size_t l = len(), n = b.len();
        if (n == 1) return short_div(b.d[0]);
        if (l < n || (l == n && d.back() < b.d.back()))
            return *this = Bigint(0);
        Bigint r(0); IV res(l);
        for (int i = l - 1; i >= 0; --i) {
            r.d.insert(r.d.begin(), d[i]); r.clean();
            int x = r.len() >= n ? r.d[n-1] : 0;
            if (r.len() > n) x += BIBAS * r.d[n];
            int q = x / b.d[n-1];
            Bigint g = b; g *= Bigint(q);
            while (r < g) g -= b, --q;
            res[i] = q, r -= g;
        }
        d = res; clean(); return *this;
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
    void println() {
        if (sgn) putchar('-');
        bool flg = true;
        RFor (IV, i, d) {
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
        RFor (IV, i, d) {
            if (flg) { sprintf(buf, "%d", *i); flg=false; }
            else sprintf(buf, BIFMT, *i);
            str.append(buf);
        }
        return str;
    }
};

//
// Fraction
//
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

//
// Matrix Exponentiation
//
typedef int m_t;
const int MRows = MAXN;
const int MCols = MAXN;
struct Matrix {
    int r, c;
    m_t m[MRows][MCols];
    void init(int R, int C) { Zero(m); r=R; c=C; }
    void iden() {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = i == j ? 1 : 0;
    }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) printf("%4d  ", m[i][j]);
            printf("\n");
        }
    }

    void mul(const Matrix &y, Matrix &z) const {
        z.r = r, z.c = y.c; m_t v;
        for (int i = 0; i < z.r; ++i)
            for (int j = 0; j < z.c; ++j) {
                v = 0;
                for (int k = 0; k < c; ++k)
                    v += m[i][k] * y.m[k][j];
                z.m[i][j] = v % 10;
            }
    }

    void exp(int e, Matrix &z) {
        z.init(r, c); z.iden();
        Matrix x, b = *this;
        while (true) {
            if (e & 1) { z.mul(b, x); z = x; }
            e >>= 1;
            if (e == 0) break;
            b.mul(b, x);
            b = x;
        }
    }
};

//
// Geometry
//
double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }
bool eps_less(double a, double b) { return b - a > EPS; }
bool eps_equal(double a, double b) { return fabs(a - b) < EPS; }

typedef double p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    p_t distance(const Point &p) {
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
    double x, y;
    Vector(double X, double Y) : x(X), y(Y) {}
    Vector(const Point &p) : x(p.x), y(p.y) {}
    double norm() { return sqrt(x*x + y*y); }
    double cross(const Vector &v) const { return x * v.y  - y * v.x; }
    double angle(const Vector &p) const {
        return circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
    void rotate(double a) {
        double px = x, py = y;
        x = px*cos(a) - py*sin(a);
        y = px*sin(a) + py*cos(a);
    }
    double distance_line_point(Point a, Point p) {
        return fabs((p.x-a.x)*y - (p.y-a.y)*x) / sqrt(x*x + y*y);
    }
};
typedef vector<Point> PV;
struct Circle {
    double x, y, r;
    Circle() {}
    Circle(double X, double Y, double R) : x(X), y(Y), r(R) {}
    bool perimeters_touch(const Circle &c) const {
        double dx = x - c.x;
        double dy = y - c.y;
        double dist = sqrt(dx*dx + dy*dy);
        return ! (eps_less(r + c.r, dist) ||
                  eps_less(dist, fabs(r - c.r)));
    }
};

p_t cross(const Point &o, const Point &a, const Point &b)
{
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
// Finds the circle formed by three points
void find_circle(Point &p1, Point &p2, Point &p3, Point &c, double &r)
{
    Point m, a, b;
    if (! eps_equal(p1.x, p2.x) && ! eps_equal(p1.x, p3.x))
        m = p1, a = p2, b = p3;
    else if (! eps_equal(p2.x, p1.x) && ! eps_equal(p2.x, p3.x))
        m = p2, a = p1, b = p3;
    else
        m = p3, a = p1, b = p2;

    double ma = (m.y - a.y) / (m.x - a.x);
    double mb = (b.y - m.y) / (b.x - m.x);

    c.x = ma*mb*(a.y - b.y) + mb*(a.x + m.x) - ma*(m.x + b.x);
    c.x /= (mb - ma)*2.0;

    if (eps_equal(0.0, ma))
        c.y = (m.y + b.y) / 2.0 - (c.x - (m.x + b.x)/2.0) / mb;
    else
        c.y = (a.y + m.y) / 2.0 - (c.x - (a.x + m.x)/2.0) / ma;

    r = c.distance(p1);
}

//
// Trie
//
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

        for (; *s; ++s) {
            idx = *s - 'A';
            if (! nodes[cur].ch[idx]) {
                nodes[cur].ch[idx] = sz++;
                nodes.resize(sz);
            }

            cur = nodes[cur].ch[idx];
        }
    }
};

//
// Hash Map
//
#define HASHB 4096
const size_t KeySz = sizeof(int) * 5;
struct HM {
    struct Key {
        int n[5];
        Key(int *N) { memcpy(n, N, KeySz); sort(n, n + 5); }
        bool operator==(const Key &x) const {
            return memcmp(n, x.n, KeySz) == 0; }
    };
    struct KV {
        Key k; int v;
        KV(Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(k.n));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    bool add(const Key &k, u64 &id) {
        int i = fnv_hash(k, KeySz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) { id = i; id <<= 32; id |= j; return false; }
        b[i].push_back(KV(k, 1));
        id = i; id <<= 32; id |= (b[i].size() - 1);
        return true;
    }
    KV get(u64 id) const { return b[id>>32][id&0xFFFFFFFF]; }
};

//
// Binary Indexed Tree
//
struct Bit {
    int f[MAXBIT + 1]; int n;
    void init(int N) { n=N; Zero(f); }
    void add(int i, int v) { while (i <= n) { f[i] += v; i += GetFS(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= GetFS(i); } return r; }
};

//
// Segment Tree
//
#define MAXN 1024000
#define MAXH 21  // 1 + ceil(log2(MAXN))
struct SegTree {
    struct Node {
        int v;   // tree value
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

    void update(int i, int j, int v) { tree_update(i, j, v, 1, 0, n-1); }
    void tree_update(int i, int j, int v, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v += v; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x].v += v * (b - a + 1);
            T[lt].u += v;
            T[rt].u += v;
            return;
        }
        tree_update(i, j, v, lt, a, md);
        tree_update(i, j, v, rt, md + 1, b);
        T[x].v = T[rt].v + T[lt].v;
    }

    int query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
    int tree_query(int i, int j, int x, int a, int b) {
        if (j < a || i > b) return -1;
        propagate(x, a, b);
        if (a >= i && b <= j) return T[x].v;
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        int q1 = tree_query(i, j, lt, a, md);
        int q2 = tree_query(i, j, rt, md + 1, b);
        if (q1 < 0) return q2;
        if (q2 < 0) return q1;
        return A[q1] <= A[q2] ? q1 : q2;
    }
};

//
// Sparse Table
//
struct SpTable {
    IV A; IIV M; int n;
    SpTable(int N) : n(N) {
        A.resize(n); int l = 1 + ceil(log2(n));
        M = IIV(n, IV(l));
    }
    void init() {
        for (int i = 0; i < n; ++i) M[i][0] = i;
        for (int j = 1, p = 2, q = 1; p <= n; ++j, p <<= 1, q <<= 1)
            for (int i = 0; i + p - 1 < n; ++i) {
                int a = M[i][j - 1], b = M[i + q][j - 1];
                M[i][j] = A[a] <= A[b] ? a : b;
            }
    }
    int query_val(int i, int j) { return A[query_idx(i, j)]; }
    int query_idx(int i, int j) {
        int k = log2(j - i + 1);
        int a = M[i][k], b = M[j + 1 - (1<<k)][k];
        return A[a] <= A[b] ? a : b;
    }
};

//
// Binary Search Tree
//
const int Nil = 0;
#define LT(t)  (T[T[t].l])
#define RT(t)  (T[T[t].r])
#define PAR(t) (T[T[t].p])
struct Bst {
    struct Node {
        int p, l, r, s, k;  // parent, left, right, size, key
        void init(int K) { k = K; p = l = r = Nil; s = 1; }
        void clear() { p = l = r = s = k = 0; }
    };
    int K[MAXK];
    Node T[MAXK + 1];
    int root, sz;
    int get(int t) { return K[T[t].k]; }
    int size() { return T[root].s; }
    void init(int n) { T[0].clear(); sz = 0; root = init_tree(0, n - 1); }
    int init_tree(int a, int b) {
        if (a > b) return Nil;
        int t = ++sz;
        if (a == b) { T[t].init(a); return t; }
        int m = (a + b) / 2;
        T[t].l = init_tree(a, m - 1);
        T[t].r = init_tree(m + 1, b);
        T[t].p = Nil, T[t].k = m, T[t].s = 1 + LT(t).s + RT(t).s;
        LT(t).p = t; RT(t).p = t;
        return t;
    }
    int find_kth(int k) { return find_kth_tree(k, root); }
    int find_kth_tree(int k, int t) {
        if (LT(t).s > k) return find_kth_tree(k, T[t].l);
        k -= LT(t).s;
        if (k == 0) return t;
        if (--k >= RT(t).s) return Nil;
        return find_kth_tree(k, T[t].r);
    }
    void remove(int t) {
        int x;
        if (T[t].l != Nil && T[t].r != Nil) {
            if (RT(t).s >= LT(t).s) for (x=T[t].r; T[x].l != Nil; x=T[x].l) ;
            else                    for (x=T[t].l; T[x].r != Nil; x=T[x].r) ;
            T[t].k = T[x].k;
            t = x;
        }
        if (T[t].l == Nil && T[t].r == Nil) {
            if (T[t].p == Nil) { root = Nil; return; }
            if (PAR(t).l == t) PAR(t).l = Nil;
            else               PAR(t).r = Nil;
        }
        else {
            x = T[t].l != Nil ? T[t].l : T[t].r;
            if (T[t].p == Nil) { T[root = x].p = Nil; return; }
            if (PAR(t).l == t) PAR(t).l = x;
            else               PAR(t).r = x;
            T[x].p = T[t].p;
        }
        for (x = T[t].p; x != Nil; x = T[x].p) --T[x].s;
    }
};

//
// Time - Leap years
//
// A[i] has the accumulated number of days from months previous to i
const int A[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
// same as A, but for a leap year
const int B[13] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
// returns number of leap years up to, and including, y
int leap_years(int y) { return y / 4 - y / 100 + y / 400; }
bool is_leap(int y) { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }
// number of days in blocks of years
const int p400 = 400*365 + leap_years(400);
const int p100 = 100*365 + leap_years(100);
const int p4   = 4*365 + 1;
const int p1   = 365;
int date_to_days(int d, int m, int y)
{
    return (y - 1) * 365 + leap_years(y - 1) + (is_leap(y) ? B[m] : A[m]) + d;
}
void days_to_date(int days, int &d, int &m, int &y)
{
    bool top100;  // are we in the top 100 years of a 400 block?
    bool top4;    // are we in the top 4 years of a 100 block?
    bool top1;    // are we in the top year of a 4 block?

    y = 1;
    top100 = top4 = top1 = false;

    y += ((days-1) / p400) * 400;
    d = (days-1) % p400 + 1;

    if (d > p100*3) top100 = true, d -= 3*p100, y += 300;
    else y += ((d-1) / p100) * 100, d = (d-1) % p100 + 1;

    if (d > p4*24) top4 = true, d -= 24*p4, y += 24*4;
    else y += ((d-1) / p4) * 4, d = (d-1) % p4 + 1;

    if (d > p1*3) top1 = true, d -= p1*3, y += 3;
    else y += (d-1) / p1, d = (d-1) % p1 + 1;

    const int *ac = top1 && (!top4 || top100) ? B : A;
    for (m = 1; m < 12; ++m) if (d <=  ac[m + 1]) break;
    d -= ac[m];
}

//
// Quickselect - for locating the median
//
struct Data {
    int v;  // value
    int n;  // occurrences
    int p;  // original position of data, to break ties
    Data(int V, int N, int P) : v(V), n(N), p(P) {}
    bool operator<(const Data &x) const {
        if (v != x.v) return v < x.v;
        if (n != x.n) return n < x.n;
        return p < x.p;
    }
};
typedef vector<Data> DV;
typedef DV::iterator DVi;
int select_kth(DVi lo, DVi hi, int k)
{
    if (hi == lo + 1) return lo->v;
    swap(*(lo + (rand() % (hi - lo))), *(hi - 1));
    Data piv = *(hi - 1);
    DVi x = lo;
    int lt = 0;
    for (DVi i = lo, I = hi - 1; i != I; ++i)
        if (*i < piv) { swap(*i, *x); lt += x->n, ++x; }
    swap(*x, *(hi - 1));
    if (k < lt) return select_kth(lo, x, k);
    if (k >= lt + x->n) return select_kth(x + 1, hi, k - lt - x->n);
    return x->v;
}

//
// Merge sort - useful for adapting it to sorting-related problems
//
void merge(IVi lo, IVi hi, IVi mid)
{
    IV x;
    for (IVi a = lo, b = mid; a < mid || b < hi; ) {
        if (a >= mid) { x.push_back(*b++); continue; }
        if (b >= hi) { x.push_back(*a++); continue; }
        if (*a < *b) { x.push_back(*a++); continue; }
        x.push_back(*b++);
    }
    for (IVi a = lo, b = x.begin(); a < hi; ++a, ++b) *a = *b;
}
void merge_sort(IVi lo, IVi hi)
{
    if (hi <= lo + 1) return;
    IVi mid = lo + ((hi - lo) / 2);
    merge_sort(lo, mid); merge_sort(mid, hi); merge(lo, hi, mid);
}

//
// Classic DP routines
//

// Calculates LIS, returns the length of the LIS and store lengths for each
// element of seq in ls
int lis(IV &seq, IV &ls)
{
    IV I(n + 1);
    ls = IV(n);
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (I[m] < seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        I[lo] = seq[i], ls[i] = lo;
        if (len < lo) len = lo;
    }
    return len;
}

// Coin change
//   W:  answer
//   C:  coin values
//   n:  number of coins
//   k:  maximum amount of money
//   pre-cond: W is cleared
void cc(int *W, const int *C, int n, int k)
{
    W[0] = 1;
    for (int i = n - 1; i >= 0; --i)
        for (int a = 0, b = C[i]; b <= k; ++a, ++b)
            W[b] = (W[b] + W[a]) % MOD;
}

//
// Misc functions
//
// next higher number with same number of 1's in binary
u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
// Returns first integer with exactly n bits set
u32 init_popcount(int n) { return (1 << n) - 1; }
// values of (1 << x) for x<32 are unique modulo 37
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])
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
