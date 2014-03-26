#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 200
#define MAXLEN 10
#define MAXD 1001


int T;
char s[MAXLEN + 1];


void test_case(bool crit = false)
{
	int len = crit ? MAXLEN : rand() % MAXLEN + 1;
	for (int i = 0; i < len; ++i)
		s[i] = '0' + rand() % 10;
	s[len] = 0;

	int d = rand() % MAXD + 1;
	if (rand() % 3 != 0) d = rand() % 10 + 1;
	printf("%s %d\n", s, d);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < 10; ++i) test_case(true);

	while (T) test_case();

	return 0;
}
