#include <algorithm>
#include <cstdio>
using namespace std;


int p1[3];
int p2[2];


int next_free(int from)
{
	int i = 0, j = 0;

	int ans = from;
	while ((i < 3 && p1[i] <= ans) || (j < 2 && p2[j] <= ans)) {
		if (i < 3) {
			if (p1[i] < ans) ++i;
			else if (p1[i] == ans) ++ans;
		}
		if (j < 2) {
			if (p2[j] < ans) ++j;
			else if (p2[j] == ans) ++ans;
		}
	}
	return ans <= 52 ? ans : -1;
}

int solve()
{
	sort(p1, p1 + 3);
	sort(p2, p2 + 2);

	if (p1[2] > p2[1]) {
		// 1 2 1 2 1
		if (p1[1] > p2[0]) return -1;

		// 1 1 2 2 1
		return next_free(p1[1] + 1);
	}

	// 1 2 1 1 2
	if (p1[1] > p2[0]) return next_free(p1[2] + 1);

	// 1 1 2 1 2
	if (p1[2] > p2[0]) return next_free(p1[1] + 1);

	// 1 1 1 2 2
	return next_free(1);
}

int main()
{
	while (true) {
		scanf("%d%d%d%d%d", &p1[0], &p1[1], &p1[2], &p2[0], &p2[1]);
		if (p1[0] == 0) break;

		printf("%d\n", solve());
	}

	return 0;
}
