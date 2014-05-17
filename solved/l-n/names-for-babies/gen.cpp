#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXLEN 10000
#define NCRIT 5


int T;
char str[MAXLEN + 1];


void test_case(bool crit = false)
{
	int len = crit ? MAXLEN : rand() % (MAXLEN - 1) + 2;
	for (int i = 0; i < len; ++i)
		str[i] = 'a' + (rand() % 26);

	int p = crit ? 1 : rand() % len + 1;
	int q = crit ? len : rand() % len + 1;

	if (p > q) swap(p, q);
	printf("%s\n%d %d\n", str, p, q);

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
