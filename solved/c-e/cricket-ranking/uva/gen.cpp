#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 5000
#define MAXK 7
#define MAXN 2000000000


int T;


void test_case(int maxn = MAXN)
{
	int K = rand() % MAXK + 1;
	int N = rand() % maxn + 1;

	printf("\n%d %d\n", K, N);

	for (int i = 0; i < K; ++i) {
		int lo = rand() % N;
		int hi = rand() % N;

		if (hi < lo) swap(lo, hi);

		if (N - lo < lo && rand() % 2 == 0) lo = N - lo;
		printf("%d %d\n", lo, hi);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < 10; ++i) test_case(100);
	for (int i = 0; i < 10; ++i) test_case(1000);
	for (int i = 0; i < 10; ++i) test_case(10000);
	for (int i = 0; i < 10; ++i) test_case(1000000);

	while (T) test_case();

	return 0;
}
