#include <algorithm>
#include <cstdio>
using namespace std;


#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))


int n;
int a, b;


void solve()
{
	a = b = 0;
	int *p = &a;
	int *q = &b;

	for (; n; ClrFS(n)) {
		*p |= GetFS(n);
		swap(p, q);
	}
}

int main()
{
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;

		solve();
		printf("%d %d\n", a, b);
	}

	return 0;
}
