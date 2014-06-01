#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 10
#define MAXN 500
#define MAXLS 1000000
#define MAXLP 500
#define NCRIT 2
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXLS 20
#define MAXLP 10
#define NCRIT 2
#endif


int T;

char S[MAXLS + 1];
char P[MAXLP + 1];


void fill(char *s, int n, int alpha)
{
	for (int i = 0; i < n; ++i)
		s[i] = 'a' + (rand() % alpha);
	s[n] = 0;
}

void gen(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;
	int alpha = rand() % 26 + 1;

	int ls = crit ? MAXLS : rand() % MAXLS + 1;
	fill(S, ls, alpha);
	printf("%d\n%s\n", n, S);

	while (n--) {
		if (rand() % 4 == 0) {
			int a = rand() % ls;
			int b = rand() % ls;

			if (a > b) swap(a, b);
			for (int i = a; i <= b; ++i) putchar(S[i]);
			putchar('\n');
		}
		else {
			fill(P, crit ? MAXLP : rand() % MAXLP + 1, alpha);
			puts(P);
		}
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
