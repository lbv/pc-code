#include <algorithm>
#include <cstdio>
using namespace std;


int n;
int cnt[5];


int solve()
{
	int ans = 0;

	ans += cnt[4];

	ans += cnt[3];
	cnt[1] = max(0, cnt[1] - cnt[3]);

	ans += cnt[2] / 2;

	if (cnt[2] % 2 != 0) {
		++ans;
		cnt[1] = max(0, cnt[1] - 2);
	}

	ans += (cnt[1] +  3) / 4;

	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int s;
		scanf("%d", &s);
		++cnt[s];
	}

	printf("%d\n", solve());

	return 0;
}
