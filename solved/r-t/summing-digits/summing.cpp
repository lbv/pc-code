#include <cstdio>


int n;


int solve()
{
	int x = n;
	while (x >= 10) {
		int y = x;
		x = 0;
		for (; y; y /= 10) x += (y % 10);
	}
	return x;
}

int main()
{
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		printf("%d\n", solve());
	}

	return 0;
}
