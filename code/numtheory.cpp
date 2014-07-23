//
// Number Theory
//

// Prime sieve
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = 46341;  // sqrt(2^31)
const int SQRP	 = 216;    // sqrt(MAX)
const int MAX_NP = 5435;   // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
	for (int i = 3; i <= SQRP; i += 2)
		if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
	primes[nprimes++] = 2;
	for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
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
	For (IV, p, primes) {
		int prime = *p;
		if (prime > sn) break; if (n % prime) continue;
		int e = 0; for (; n % prime == 0; e++, n /= prime);
		f.push_back(II(prime, e));
		sn = sqrt(n);
	}
	if (n > 1) f.push_back(II(n, 1));
}

template <typename T>
void divisors(T n, T *ds, int &s)
{
	s = 0;
	ds[s++] = 1;
	int sn = sqrt(n);
	for (int i = 0; i < nprimes; ++i) {
		int &p = primes[i];
		if (p > sn) break;
		if (n % p != 0) continue;
		T q = 1; int t = s;
		while (n % p == 0) {
			q *= p, n /= p;
			for (int j = 0; j < t; ++j) ds[s++] = ds[j] * q;
		}
		sn = sqrt(n);
	}
	if (n > 1) {
		int t = s;
		for (int j = 0; j < t; ++j) ds[s++] = ds[j] * n;
	}
}

void euler_phi(int a[], int N) {
	for (int i = 1; i <= N; i++) a[i] = i;
	for (int i = 2; i <= N; i += 2) a[i] = i/2;
	for (int i = 3; i <= N; i += 2)
		if (a[i] == i) {
			--a[i]; for (int j = i+i; j <= N; j += i) a[j] -= a[j]/i; }
}

template <typename TB, typename TE>
TB mod_pow(TB b, TE e, TB m) {
	TB res = 1; for (; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
	return res;
}

template<typename TB, typename TE>
TB sq_pow(TB b, TE e) {
	TB res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
	return res;
}

template<typename TB, typename TE>
void sq_pow(TB b, TE e, TB &r) {
	for (; e; e >>= 1, b *= b) if (e & 1) r *= b;
}

template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }

template<typename T>
void ext_euclid(T a, T b, T &x, T &y, T &g) {
	x = 0, y = 1, g = b;
	T m, n, q, r;
	for (T u=1, v=0; a != 0; g=a, a=r) {
		q = g / a, r = g % a;
		m = x-u*q, n = y-v*q;
		x=u, y=v, u=m, v=n;
	}
}

template<typename T>
T mod_inv(T n, T m) {
	T x, y, gcd;
	ext_euclid(n, m, x, y, gcd);
	if (gcd != 1) return 0;
	if (x < 0) x += m;
	else if (x >= m) x %= m;
	return x;
}

//
// ceil(x/y) and floor(x/y) for integer types; assumes positive y
//
template<typename T>
T int_ceil(T x, T y) { return x > 0 ? (x-1)/y + 1 : x/y; }
template<typename T>
T int_floor(T x, T y) { return x >= 0 ? x/y : (x+1)/y - 1; }

int fact[MAXFACT];
template<typename T>
T catalan_mod(T n)
{
	T f1 = fact[2*n];
	T f2 = mod_inv<T>(fact[n], MOD);
	T f3 = mod_inv<T>(n+1, MOD);

	T ans = f1*f2;
	if (ans >= MOD) ans %= MOD;
	ans *= f2;
	if (ans >= MOD) ans %= MOD;
	ans *= f3;
	if (ans >= MOD) ans %= MOD;
	return ans;
}

template <typename T>
T chinese_rem(int k, T *ns, T *as)
{
	T N = 1, x = 0, r, s, g;
	for (int i = 0; i < k; ++i) N *= ns[i];
	for (int i = 0; i < k; ++i) {
		ext_euclid(ns[i], N/ns[i], r, s, g);
		x += as[i]*s*(N/ns[i]);
		x %= N;
	}
	if (x < 0) x += N;
	return x;
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

template <typename T>
T choose(T n, T k) {
	if (k > n) return 0;
	if (n-k < k) k = n-k;
	T r=1;
	for (T d = 1; d <= k; d++)
		r *= n--, r /= d;
	return r;
}
