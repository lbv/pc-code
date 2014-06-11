#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXLEN 100
#define NCRIT 10
#endif

#if 1
#define MAXT 20
#define MAXLEN 33
#define NCRIT 3
#endif


int T;


void test_case(bool crit = false)
{
	int len1 = crit ? MAXLEN : rand() % MAXLEN + 1;
	int len2 = crit ? MAXLEN : rand() % MAXLEN + 1;

	int alpha = rand() % 26 + 1;
	putchar('\n');
	for (int i = 0; i < len1; ++i)
		printf("%c", 'a' + (rand() % alpha));
	putchar('\n');
	for (int i = 0; i < len2; ++i)
		printf("%c", 'a' + (rand() % alpha));
	putchar('\n');
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	return 0;
}
