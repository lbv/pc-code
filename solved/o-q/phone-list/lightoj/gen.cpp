#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 50
#define MAXN 10000
#define MAXLEN 10
#define NCRIT 5
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXLEN 10
#define NCRIT 2
#define NL 1
#endif


int T;
char num[MAXLEN + 1];


void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int n = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", n);

	while (n--) {
		int len = rand() % MAXLEN + 1;
		for (int i = 0; i < len; ++i) num[i] = '0' + (rand() % 10);
		num[len] = 0;
		puts(num);
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
