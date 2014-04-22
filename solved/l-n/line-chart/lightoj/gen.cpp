#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 1
#define MAXT 12
#define MAXN 10000
#define MAXK 50
#define MAXSRT 1000000000
#define MAXRAT 1000000000
#define NCRIT 2
#endif

#if 0
#define MAXT 12
#define MAXN 20
#define MAXK 8
#define MAXSRT 1000000000
#define MAXRAT 1000000000
#define NCRIT 2
#endif


int T;


void test_case(bool crit = false)
{
	int N = crit ? MAXN : rand() % MAXN + 1;
	int K = crit ? MAXK : rand() % (MAXK + 1);
	printf("\n%d %d\n", N, K);

	set<int> srts;
	while (N--) {
		int srt, rat;
		do {
			srt = rand() % MAXSRT + 1;
		} while (srts.find(srt) != srts.end());
		srts.insert(srt);

		rat = rand() % MAXRAT + 1;
		printf("%d %d\n", srt, rat);
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
