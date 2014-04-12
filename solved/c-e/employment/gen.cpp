#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 30
#define MAXN 100
#define NCRIT 5
#endif

#if 1
#define MAXT 20
#define MAXN 4
#define NCRIT 1
#define NL 1
#endif


int T;
int prio[MAXN];


void test_case(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;
#if NL
	puts("");
#endif
	printf("%d\n", n);

	for (int i = 0; i < n; ++i) prio[i] = i + n + 1;

	for (int i = 0; i < n; ++i) {
		random_shuffle(prio, prio + n);
		for (int j = 0; j < n; ++j)
			printf("%s%d", j > 0 ? " " : "", prio[j]);
		puts("");
	}

	for (int i = 0; i < n; ++i) prio[i] = i + 1;

	for (int i = 0; i < n; ++i) {
		random_shuffle(prio, prio + n);
		for (int j = 0; j < n; ++j)
			printf("%s%d", j > 0 ? " " : "", prio[j]);
		puts("");
	}

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
