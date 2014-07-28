#include <cstdio>


int n;


int solve()
{
	n *= 567/9;
	n += 7492;
	n *= 235/47;
	n -= 498;

	if (n < 0) n *= -1;

	return (n / 10) % 10;
}

int main()
{
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		printf("%d\n", solve());
	}

	return 0;
}
