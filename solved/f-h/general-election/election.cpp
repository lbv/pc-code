#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 5

#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))


int n, m;
int vs[MAXN];


int solve()
{
	return max_element(vs, vs + n) - vs + 1;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d", &n, &m);
		ClrN(vs, n, int);

		while (m--) {
			for (int i = 0; i < n; ++i) {
				int x;
				scanf("%d", &x);
				vs[i] += x;
			}
		}

		printf("%d\n", solve());
	}

	return 0;
}
