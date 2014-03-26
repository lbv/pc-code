#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


char s[16];


void solve()
{
	int len = strlen(s);
	sort(s, s + len);

	do {
		printf("%s\n", s);
	} while (next_permutation(s, s + len));
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%s", s);
		printf("Case %d:\n", ++ncase);
		solve();
	}

	return 0;
}
