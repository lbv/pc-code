#include <cstdio>


#define MAXN 100


int n, n1, n2, n3;
int a1[MAXN];
int a2[MAXN];
int a3[MAXN];


void print_group(const int *p, int n)
{
	printf("%d", n);
	for (int i = 0; i < n; ++i) printf(" %d", p[i]);
	putchar('\n');
}

void solve()
{
	if (n1 % 2 == 0)
		a3[n3++] = a1[--n1];

	if (n2 == 0) {
		a2[n2++] = a1[--n1];
		a2[n2++] = a1[--n1];
	}

	print_group(a1, n1);
	print_group(a2, n2);
	print_group(a3, n3);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);

		if (x < 0) a1[n1++] = x;
		else if (x > 0) a2[n2++] = x;
		else a3[n3++] = x;
	}

	solve();

	return 0;
}
