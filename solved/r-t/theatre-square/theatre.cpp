#include <cstdio>


typedef long long i64;


int n, m, a;


i64 solve()
{
	i64 s1 = (n-1) / a + 1;
	i64 s2 = (m-1) / a + 1;
	return s1*s2;
}

int main()
{
	scanf("%d%d%d", &n, &m, &a);
	printf("%lld\n", solve());

	return 0;
}
