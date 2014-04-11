#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100000
#define MAXM 16
#define INF  0x3f3f3f3f3f3f3f3fLL

#define Clr(m) memset(m, 0, sizeof(m))

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

// Returns first integer with exactly n bits set
u32 popcnt_init(int n) { return (1 << n) - 1; }
// next higher number with same number of 1's in binary
u32 popcnt_next(u32 n)
{
	u32 c = (n & -n);
	u32 r = n+c;
	return (((r ^ n) >> 2) / c) | r;
}


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


int N, m;
int A[MAXN];

// cnt[i][j]: how many times j has occurred above some i
int cnt[MAXM][MAXM];

// inv[i][b]: # of times any number in bitmask b has occurred above some i
i64 inv[MAXM][1 << MAXM];

// tot[i]: total number of occurrences of i
int tot[MAXM];

// dp[b]: minimum number of swaps required to sort the numbers in bitmask b
i64 dp[1 << MAXM];


i64 solve()
{
	Clr(cnt);
	Clr(tot);
	for (int i = N - 1; i >= 0; --i) {
		int a = A[i];

		for (int j = 0; j < m; ++j)
			cnt[a][j] += tot[j];

		++tot[a];
	}

	Clr(inv);
	u32 all = (1 << m) - 1;
	for (int i = 0; i < m; ++i)
		for (u32 j = 1; j <= all; ++j) {
			u32 bit = GetFS(j);
			int idx = Ctz(bit);

			inv[i][j] = inv[i][j & ~bit] + cnt[i][idx];
		}

	Clr(dp);
	for (int j = 2; j <= m; ++j)
		for (u32 b = popcnt_init(j); b <= all; b = popcnt_next(b)) {
			i64 &best = dp[b];
			best = INF;

			for (u32 x = b; x; ClrFS(x)) {
				u32 bit = GetFS(x);
				int idx = Ctz(bit);

				best = min(best, dp[b & ~bit] + inv[idx][b & ~bit]);
			}
		}

	return dp[all];
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		m = rr.next_u32();

		for (int i = 0; i < N; ++i) A[i] = rr.next_u32() - 1;

		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}
