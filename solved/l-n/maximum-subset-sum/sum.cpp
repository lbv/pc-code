#include <cstdio>
#include <queue>
using namespace std;


#define MAXN 100

#define PosMSB(x) (63 - __builtin_clzll(x))
#define GetMSB(x) (1ULL << PosMSB(x))


typedef unsigned long long u64;


int n;
u64 ns[MAXN];
u64 mat[65];


u64 solve()
{
	u64 latest = 0;
	priority_queue<u64> q(ns, ns + n);
	n = 0;

	u64 t = q.top(); q.pop();
	u64 msb = GetMSB(t);
	mat[n++] = t;

	while (! q.empty()) {
		u64 num = q.top(); q.pop();
		if (num == latest) continue;

		if (num & msb)
			q.push(num ^ mat[n-1]);
		else {
			msb = GetMSB(num);
			mat[n++] = num;
		}

		latest = num;
	}

	u64 ans = 0;

	for (int i = 0; i < n; ++i)
		if ((ans & GetMSB(mat[i])) == 0)
			ans ^= mat[i];

	return ans;
}


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%llu", &ns[i]);
		printf("Case %d: %llu\n", ++ncase, solve());
	}

	return 0;
}
