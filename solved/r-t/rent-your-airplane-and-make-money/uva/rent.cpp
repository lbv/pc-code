#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;


#define MAXN 3000


typedef unsigned int u32;
typedef long long i64;


struct State {
	int t, p, d;  // time, price, duration (-1 if is an ending time)

	bool operator<(const State &x) const {
		if (t != x.t) return t < x.t;
		return d < 0 && x.d >= 0;
	}
};


int n;
map<int, i64> dp;

State ss[MAXN*2];
int nss;


i64 solve()
{
	dp.clear();
	sort(ss, ss + nss);

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
	bool first = true;
	while (scanf("%d", &n) == 1) {
		nss = 0;
		while (n--) {
			int s, d, p;
			scanf("%*s%d%d%d", &s, &d, &p);

			ss[nss++] = (State) { s, p, d };
			ss[nss++] = (State) { s+d, p, -1 };
		}

		if (first) first = false;
		else putchar('\n');

		printf("%lld\n", solve());
	}

	return 0;
}
