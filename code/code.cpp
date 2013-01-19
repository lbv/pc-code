// Macros
#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))

#define Neg(v)  memset((v), -1, sizeof(v))
#define Zero(v) memset((v), 0, sizeof(v))

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define RFor(t,v,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)

//
// Fraction
//
template<typename T>
struct Fraction {
    T p, q;

    Fraction() { p = 0, q = 1; }
    Fraction(T P, T Q) : p(P), q(Q) { simplify(); }
    void simplify() {
        T g = gcd(p, q);
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
double heron(double a, double b, double c)
{
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

template <typename T>
struct Point {
    T x, y;
    Point() { x=y=0; }
    Point(T X, T Y) : x(X), y(Y) {}
    T distance(const Point &p) {
        T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
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

// area of a polygon, times two
template <typename T>
T poly_area2(Point<T> *p, int n)
{
    T a = 0;
    for (int i = 0, j = n - 1; i < n; j = i++)
        a += (p[j].x + p[i].x) * (p[j].y - p[i].y);
    if (a < 0) a *= -1;
    return a;
}

template <typename T>
T lattice_pts(Point<T> &a, Point<T> &b)
{
    if (a.x == b.x) return llabs(a.y - b.y) + 1;
    return gcd(llabs(a.y - b.y), llabs(a.x - b.x)) + 1;
}
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
        KV(const Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(k.n));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U) ^ p[i];
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
// IDA*
//
template <typename NT, typename DT>
bool ida_dls(NT &node, int depth, int g, int &nxt, stack<DT> &st)
{
    if (g == depth) return node.is_solution();

    NT child;
    int dist;
    DT delta;
    for (node.reset(); node.next(child, dist, delta);) {
        int f = g + dist + child.h();
        if (f > depth && f < nxt) nxt = f;
        if (f <= depth  && ida_dls(child, depth, g + 1, nxt, st)) {
            st.push(delta);
            return true;
        }
    }
    return false;
}

template <typename NT, typename DT>
bool ida_star(NT &root, int limit, stack<DT> &st)
{

    for (int depth = root.h(); depth <= limit;) {
        int next_depth = INF;
        if (ida_dls(root, depth, 0, next_depth, st)) return true;
        if (next_depth == INF) return false;
        depth = next_depth;
    }
    return false;
}

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
// Knuth-Morris-Pratt
//
#define MAXS MAXLEN
#define MAXW MAXLEN
struct KMP {
    char S[MAXS + 1], W[MAXW + 1]; int ls, lw; int T[MAXW + 1];
    void init() {
        T[0] = -1, T[1] = 0;
        for (int p = 2, c = 0; p < lw;) {
            if (W[p-1] == W[c]) T[p++] = ++c;
            else if (c > 0) c = T[c];
            else T[p++] = 0;
        }
    }
    int search() {
        for (int m=0, i=0; m + i < ls;) {
            if (W[i] == S[m + i]) { if (++i == lw) return m; }
            else { m += i - T[i]; i = T[i] >= 0 ? T[i] : 0; }
        }
        return -1;
    }
};

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
