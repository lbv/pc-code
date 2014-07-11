#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 10000
#define MAXTIME 2000000


typedef unsigned int u32;
typedef long long i64;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};


struct State {
	int t, p, d;  // time, price, duration (-1 if is an ending time)

	bool operator<(const State &x) const {
		if (t != x.t) return t < x.t;
		return d < 0 && x.d >= 0;
	}
};


int n;
i64 dp[MAXTIME + 1];

State ss[MAXN*2];
int nss;


i64 solve()
{
	sort(ss, ss + nss);
	for (int i = 0; i < nss; ++i)
		dp[ss[i].t] = 0;

	i64 ans = 0;
	for (int i = 0; i < nss; ++i) {
		State &s = ss[i];
		if (s.d >= 0)
			dp[s.t + s.d] = max(dp[s.t + s.d], ans + s.p);
		else
			ans = dp[s.t] = max(dp[s.t], ans);
	}

	return ans;
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	while (T--) {
		n = rr.next_u32();

		nss = 0;
		for (int i = 0; i < n; ++i) {
			int s = rr.next_u32();
			int d = rr.next_u32();
			int p = rr.next_u32();

			ss[nss++] = (State) { s, p, d };
			ss[nss++] = (State) { s+d, p, -1 };
		}

		printf("%lld\n", solve());
	}

	return 0;
}
