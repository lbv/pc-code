#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 40
#define MAXLEN 1000
#define MAXALPH 26
#define NCRIT 3
#endif

#if 0
#define MAXT 20
#define MAXLEN 8
#define MAXALPH 10
#define NCRIT 3
#endif


int T;
char str[MAXLEN + 1];


void gen(bool crit = false)
{
	int len = crit ? MAXLEN : rand() % MAXLEN + 1;
	int alpha = crit ? MAXALPH : rand() % MAXALPH + 1;

	for (int i = 0; i < len; ++i)
		str[i] = 'A' + (rand() % alpha);

	str[len] = 0;
	puts(str);
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
