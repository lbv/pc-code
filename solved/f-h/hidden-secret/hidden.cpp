#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;


char name1[128];
char name2[128];
char aux[128];


void normalize(char *s)
{
	int len = 0;

	for (char *p = s; *p; ++p)
		if (! isspace(*p))
			aux[len++] = tolower(*p);

	sort(aux, aux + len);
	strncpy(s, aux, len);
	s[len] = 0;
}

bool solve()
{
	normalize(name1);
	normalize(name2);
	return strcmp(name1, name2) == 0;
}

int main()
{
	int T;
	scanf("%d", &T);
	gets(name1);

	int ncase = 0;
	while (T--) {
		gets(name1);
		gets(name2);
		printf("Case %d: ", ++ncase);
		if (solve())
			puts("Yes");
		else
			puts("No");
	}

	return 0;
}
