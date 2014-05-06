#include <cstdio>


int w;


bool solve()
{
	return w > 2 && w % 2 == 0;
}

int main()
{
	scanf("%d", &w);
	if (solve())
		puts("YES");
	else
		puts("NO");

	return 0;
}
