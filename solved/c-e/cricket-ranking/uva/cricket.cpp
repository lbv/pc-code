#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;


#define MAXK 7

#define RFor(t,v,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)

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

typedef vector<int> IV;
typedef IV::iterator IVi;


//
// Big Integer
//
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct BigInt {
    IV d; bool sgn;
    BigInt(i64 n=0) {
        if (n < 0) sgn = true, n = -n; else sgn = false;
        if (n < BIBAS) d.push_back(n);
        else while (n != 0) { d.push_back(n % BIBAS); n /= BIBAS; }
    }
    BigInt(const char *s) {
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
    BigInt neg() const { BigInt x = *this; x.flip(); return x; }
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && is_zero()) sgn = false;
    }
    bool operator==(const BigInt &b) const {
        return sgn == b.sgn && d == b.d;
    }
    bool operator<(const BigInt &b) const {
        if (sgn != b.sgn) return sgn;
        if (len() != b.len()) return sgn ^ (len() < b.len());
        for (int i = len() - 1; i >= 0; --i)
            if (d[i] != b.d[i]) return sgn ^ (d[i] < b.d[i]);
        return false;
    }
    BigInt &operator*=(const BigInt &b) {
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
    BigInt &operator+=(const BigInt &b) {
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
    BigInt &operator-=(const BigInt &_b) {
        if (sgn != _b.sgn) { (*this) += _b.neg(); return *this; }
        bool sbk = sgn; sgn = false; BigInt b = _b.sgn ? _b.neg() : _b;
        if (*this < b) {
            b -= *this; *this = sbk ? b : b.neg(); return *this; }
        int s1 = len(), s2 = b.len(), s3 = s1;
        IV res(s3); int c = 0;
        for (int i = 0; i < s3; ++i) {
            int sum = d[i] - (i < s2 ? b.d[i] : 0) - c;
            if (sum < 0) { sum += BIBAS; c = 1; } else c = 0;
            res[i] = sum;
        }
        d = res; sgn = sbk; clean();
        return *this;
    }
    BigInt &short_div(int b) {
        for (int r = 0, i = len() - 1; i >= 0; --i)
            r = r*BIBAS + d[i], d[i] = r / b, r %= b;
        clean(); return *this;
    }
    void print(bool nl = true) {
        if (sgn) putchar('-');
        bool flg = true;
        RFor (IV, i, d) {
            if (flg) { printf("%d", *i); flg=false; }
            else printf(BIFMT, *i);
        }
        if (nl) putchar('\n');
    }
};


i64 N;
int K;

int lim[MAXK];
int fac[MAXK+1];


u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }


BigInt choose(i64 n, int k)
{
	if (n == k) return BigInt(1);

	i64 bottom, den;
	if (n-k > k)
		bottom = n-k, den = k;
	else
		bottom = k, den = n-k;

	BigInt ans(1);
	for (i64 i = n; i > bottom; --i)
		ans *= BigInt(i);

	ans.short_div(fac[den]);

	/*
	printf("  (%lld,%d): ", n, k);
	ans.print();*/
	return ans;
}

void solve()
{
	//printf("  N, K! %lld, %d\n", N, K);

	if (N < 0) { puts("0"); return; }
	if (N == 0) { puts("1"); return; }

	BigInt ans = choose(N + K - 1, K - 1);

	u32 top = 1 << K;

	for (int i = 1; i <= K; ++i) {
		bool even = i % 2 == 0;

		for (u32 b = init_popcount(i); b < top; b = next_popcount(b)) {
			i64 n = N + K - 1;
			int k = K - 1;

			for (u32 x = b; x; ClrFS(x)) {
				int idx = Ctz(GetFS(x));
				n -= lim[idx] + 1;
			}

			if (n < k) continue;
			if (even)
				ans += choose(n, k);
			else
				ans -= choose(n, k);
		}
	}

	ans.print();
}

int main()
{
	fac[0] = 1;
	for (int i = 1; i <= MAXK; ++i) fac[i] = fac[i-1]*i;

	while (true) {
		if (scanf("%d%lld", &K, &N) != 2) break;

		int lo, hi;

		for (int i = 0; i < K; ++i) {
			scanf("%d%d", &lo, &hi);

			if (lo > hi) swap(lo, hi);
			lim[i] = hi - lo;
			N -= lo;
		}

		solve();
	}

	return 0;
}
