#include <cstdio>


int n, k;


int main()
{
	scanf("%d%d", &n, &k);

	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		int y;
		scanf("%d", &y);

		if (y + k <= 5) ++cnt;
	}
	printf("%d\n", cnt/3);

	return 0;
}
