#include <cstdio>
#include <queue>
using namespace std;


#define MAXN 100000

#define PosMSB(x) (63 - __builtin_clzll(x))
#define GetMSB(x) (1ULL << PosMSB(x))


typedef unsigned long long u64;


int N;
u64 a[MAXN];
u64 mat[65];
int n;


u64 solve()
{
	u64 latest = 0;
	priority_queue<u64> q(a, a + N);

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
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%llu", &a[i]);
	printf("%llu\n", solve());

	return 0;
}
