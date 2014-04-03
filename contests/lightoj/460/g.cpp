#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;


int N;


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);

		int ans = 0;
		for (int i = 0; i < N; ++i) {
			int n;
			scanf("%d", &n);
			ans = max(ans, abs(n));
		}

		printf("Case %d: %d\n", ++ncase, ans);
	}

	return 0;
}
