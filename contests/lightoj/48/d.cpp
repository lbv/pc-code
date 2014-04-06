/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem D: I <3 U Q
 *
 * Keywords:
 *   - beginner
 *   - strings
 */

#include <cstdio>
#include <cstring>


char str[32];


void solve()
{
	int cnt = 0;
	bool happy = false;

	int len = strlen(str);
	for (int i = 0; i < len; ++i)
		if (str[i] == 'q') {
			++cnt;
			if (i + 1 < len && str[i+1] == 'u')
				happy = true;
		}

	if (cnt == 0)
		puts("Ordinary Word");
	else if (happy)
		puts("I <3 U Q");
	else
		puts(":(");
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%s", str);
		printf("Case %d: ", ++ncase);
		solve();
	}

	return 0;
}
