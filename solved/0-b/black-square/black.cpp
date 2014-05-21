#include <cstdio>


#define MAXLEN 100000


int a[5];
char s[MAXLEN + 1];


int solve()
{
	int ans = 0;
	for (char *p = s; *p; ++p) ans += a[*p - '0'];
	return ans;
}

int main()
{
	for (int i = 1; i <= 4; ++i) scanf("%d", &a[i]);
	scanf("%s", s);
	printf("%d\n", solve());

	return 0;
}
