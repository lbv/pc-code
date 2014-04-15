#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 1
#define MAXT 100
#define MAXN 2000
#define MAXI 10000
#define NCRIT 10
#endif

#if 0
#define MAXT 10
#define MAXN 5
#define MAXI 100
#define NCRIT 1
#define NL 1
#endif


#define Clr(m) memset(m, 0, sizeof(m))


int T;

bool used[MAXI+1];

void test_case(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % (MAXN + 1);
	printf("%d\n", n);

	Clr(used);
	while (n--) {
		int w;
		do {
			w = rand() % (MAXI + 1);
		} while (used[w]);
		used[w] = true;
		printf("%d\n", w);
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
