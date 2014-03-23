#include <cstdio>


#define MAXK 10
#define MAXN 1000000

#define MAXFAC (MAXN + MAXK)
#define MOD 100000007LL

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


typedef long long i64;
typedef unsigned int u32;


int K, N;

i64 fact[MAXFAC + 1];

int lim[MAXK];


u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }

template<typename T>
void ext_euclid(T a, T b, T &x, T &y, T &g) {
	x = 0; y = 1; g = b;
	T m, n, q, r;
	for (T u=1, v=0; a != 0; g=a, a=r) {
		q = g / a; r = g % a;
		m = x-u*q; n = y-v*q;
		x=u; y=v; u=m; v=n;
	}
}

template<typename T>
T mod_inv(T n, T m) {
	T x, y, gcd;
	ext_euclid(n, m, x, y, gcd);
	if (gcd == 1) return x % m;
	return 0;
}


i64 choose(int n, int k)
{
	if (n < k) return 0;
	if (n == k) return 1;

	i64 num = fact[n];
	i64 d1 = mod_inv(fact[k], MOD);
	i64 d2 = mod_inv(fact[n-k], MOD);
	i64 den = d1 * d2 % MOD;

	return num * den % MOD;
}

void prepare()
{
	// pre-compute factorials
	fact[0] = 1;
	for (int i = 1; i <= MAXFAC; ++i)
		fact[i] = (fact[i-1] * i) % MOD;
}

int solve()
{
	if (N < 0) return 0;
	if (N == 0) return 1;

	i64 ans = choose(N + K - 1, K - 1);

	u32 top = 1 << K;

	for (int i = 1; i <= K; ++i) {
		int sgn = i % 2 == 0 ? 1 : -1;

		for (u32 b = init_popcount(i); b < top; b = next_popcount(b)) {
			int n = N + K - 1;
			int k = K - 1;

			for (u32 x = b; x; ClrFS(x)) {
				int idx = Ctz(GetFS(x));
				n -= lim[idx] + 1;
			}

			ans += choose(n, k) * sgn;
			ans += MOD;
			ans %= MOD;
		}
	}

	return static_cast<int>(ans);
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &K, &N);

		for (int i = 0; i < K; ++i) {
			int lo, hi;
			scanf("%d%d", &lo, &hi);

			lim[i] = hi - lo;
			N -= lo;
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
