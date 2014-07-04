//
// Macros
//

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))

#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))
#define NegN(m,n,t) memset(m, -1, sizeof(t)*(n))
#define InfN(m,n,t) memset(m, 0x3f, sizeof(t)*(n))

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)
#define RFor(t,v,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)

//
// Fraction
//
template<typename T>
struct Fraction {
	T p, q;

	Fraction() : p(0), q(1) {}
	Fraction(T P) : p(P), q(1) {}
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
	Fraction operator-() const { return Fraction(-p, q); }
	bool operator<(const Fraction &f) const { return p*f.q < q*f.p; }
	bool operator>(const Fraction &f) const { return p*f.q > q*f.p; }
	bool operator<=(const Fraction &f) const { return p*f.q <= q*f.p; }
	bool operator>=(const Fraction &f) const { return p*f.q >= q*f.p; }
	bool operator==(const Fraction &f) const { return p == f.p && q == f.q; }
};

struct Mod2 {
	int v;
	Mod2() {}
	Mod2(int V) : v(V) {}
	bool operator!=(const Mod2 &x) const { return v != x.v; }
	Mod2 operator/(const Mod2 &x) const { return Mod2(v); }
	Mod2 operator*(const Mod2 &x) const { return Mod2(v & x.v); }
	Mod2 &operator-=(const Mod2 &x) { v ^= x.v; return *this; }
};


//
// IDA*
//
struct Board {
	// heuristics
	int h() { return 0; }

	bool is_solution() {
		return false;
	}

	// computes the next child
	bool next(Board &child, int &dist, int &delta) {
		return false;
	}

	// resets the loop to visit children
	void reset() { }
};
typedef Board NodeT;
typedef int DeltaT;  // represents a state change, useful to track the path

// Depth limited search
bool ida_dls(NodeT &node, int depth, int g, int &nxt, stack<DeltaT> &st)
{
	if (g == depth) return node.is_solution();

	NodeT child;
	int dist;
	DeltaT delta;
	for (node.reset(); node.next(child, dist, delta);) {
		int f = g + dist + child.h();
		if (f > depth && f < nxt) nxt = f;
		if (f <= depth	&& ida_dls(child, depth, g + 1, nxt, st)) {
			st.push(delta);
			return true;
		}
	}
	return false;
}

bool ida_star(NodeT &root, int limit, stack<DeltaT> &st)
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
// Quickselect - for locating the median
//
struct Data {
	int v;	// value
	int n;	// occurrences
	int p;	// original position of data, to break ties
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
// Basic binary search
//
template <typename T>
int binsearch(const T *a, int lo, int hi, T v)
{
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (a[mid] == v) return mid;
		if (a[mid] < v) lo = mid + 1;
		else			hi = mid;
	}
	return -1;
}

template <typename T>
int binsearch_upper(const T *a, int lo, int hi, T v)
{
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (a[mid] <= v) lo = mid + 1;
		else			 hi = mid;
	}
	return lo;
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
// Misc functions
//

// returns the position of the last visited in range [0, n-1]
int josephus(int n, int k)
{
	if (n == 1) return 0;
	return (josephus(n-1, k) + k) % n;
}

//
// Max Area Rectangle in an Histogram
//
typedef int AreaT;
AreaT areas[MAXN];
int stk[MAXN], stk_top;
AreaT histo_area(AreaT *h, int n)
{
	stk_top = 0;
	for (int i = 0; i < n; ++i) {
		while (stk_top > 0 && h[ stk[stk_top-1] ] >= h[i]) --stk_top;
		int bound = stk_top > 0 ? stk[stk_top - 1] : -1;
		areas[i] = i - bound;
		stk[stk_top++] = i;
	}

	stk_top = 0;
	for (int i = n-1; i >= 0; --i) {
		while (stk_top > 0 && h[ stk[stk_top-1] ] >= h[i]) --stk_top;
		int bound = stk_top > 0 ? stk[stk_top - 1] : n;
		areas[i] += bound - i - 1;
		stk[stk_top++] = i;
	}

	AreaT ans = 0;
	for (int i = 0; i < n; ++i)
		if (h[i] > 0 && areas[i]*h[i] > ans) ans = areas[i]*h[i];
	return ans;
}


//
// Stable Marriage Problem
//

// man[i][j]: woman with priority j for man i
int man[MAXN][MAXN];

// woman[i][j]: priority for man j given by woman i
int woman[MAXN][MAXN];

// next_for[i]: next priority to consider for man i
int next_for[MAXN];

struct Marriage {
	int w, m;
	Marriage() {}
	Marriage(int W, int M): w(W), m(M) {}

	bool operator<(const Marriage &x) const {
		return woman[w][m] > woman[x.w][x.m];
	}
};

// marriage[j]: current marriage for woman j
Marriage marriage[MAXN];

// Gale-Shapley algorithm.
// pre-cond: Clr(next_for) Neg(marriage)
void stable_match(int m)
{
	// if a solution is not guaranteed, add check here to see if maybe there
	// are no more matches

	int w = man[m][ next_for[m]++ ];

	Marriage cur(w, m);

	if (marriage[w].m < 0)
		marriage[w] = cur;
	else if (marriage[w] < cur) {
		int mp = marriage[w].m;
		marriage[w] = cur;
		stable_match(mp);
	}
	else
		stable_match(m);
}
