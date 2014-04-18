#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
using namespace std;


#define MAXSTR 100
#define STRLEN 1024

const int MAX_ANAG = MAXSTR * MAXSTR;


typedef pair<string, string> SS;


SS ss[MAXSTR];
int n;  // total number of strings

char input[STRLEN];
char aux[STRLEN];
string anag[MAX_ANAG];


string normalize()
{
	int len = 0;

	for (char *p = input; *p; ++p)
		if (isalpha(*p))
			aux[len++] = *p;
	aux[len] = 0;

	sort(aux, aux + len);
	return string(aux);
}

void solve()
{
	int na = 0;
	for (int i = 1; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (ss[i].second == ss[j].second) {
				string a = ss[i].first;
				string b = ss[j].first;
				if (b < a) swap(a, b);
				anag[na++] = a + " = " + b;
			}

	sort(anag, anag + na);
	for (int i = 0; i < na; ++i)
		printf("%s\n", anag[i].c_str());
}

int main()
{
	int T;
	scanf("%d", &T);
	gets(input);
	gets(input);

	int ncase = 0;
	while (T--) {
		n = 0;
		while (gets(input) != NULL && input[0] != 0)
			ss[n++] = SS(string(input), normalize());

		if (ncase++ > 0) putchar('\n');
		solve();
	}

	return 0;
}
