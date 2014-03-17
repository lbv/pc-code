//
// Macros
//
#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))

#define Memset(m,v) memset(m, v, sizeof(m))
#define Clr(m) Memset(m,0)
#define Inf(m) Memset(m,0x7f)
#define Neg(m) Memset(m,-1)

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
		if (f <= depth	&& ida_dls(child, depth, g + 1, nxt, st)) {
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
	bool top4;	  // are we in the top 4 years of a 100 block?
	bool top1;	  // are we in the top year of a 4 block?

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
//	 W:  answer
//	 C:  coin values
//	 n:  number of coins
//	 k:  maximum amount of money
//	 pre-cond: W is cleared
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



enum TType {
	NONE,
	Tok1,
	Tok2
};

struct Token {
	int v;
	TType t;
	Token(TType T) : v(0), t(T) {}
	Token(int V, TType T) : v(V), t(T) {}
};
typedef queue<Token> TQ;

struct AST {
	struct Node {
		int lt, rt;
		int c0, c1;  // coefficients: c1*x + c0
		TType op;
		Node(int C0, int C1) : lt(-1), rt(-1), c0(C0), c1(C1) {}
		Node(TType O, int L, int R) : lt(L), rt(R), op(O) {}
	};
	vector<Node> nodes;

	int add(int c0, int c1) {
		int idx = nodes.size();
		nodes.push_back(Node(c0, c1));
		return idx;
	}
	int add(TType op, int lt, int rt) {
		int idx = nodes.size();
		nodes.push_back(Node(op, lt, rt));
		return idx;
	}
};

struct Parser {
	TQ &in;
	bool err;
	Parser(TQ &In) : in(In) { err = false; }

	TType in_peek() {
		if (in.empty()) return NONE;
		return in.front().t;
	}
	Token in_pop() {
		if (in.empty()) return Token(NONE);
		Token t = in.front();
		in.pop();
		return t;
	}

	void main_rule() {
		if (in_peek() == CONJUNCTION) {
			in_pop();
			np();
			vp();
		}
		if (in_peek() != NONE) err = true;
	}
};
