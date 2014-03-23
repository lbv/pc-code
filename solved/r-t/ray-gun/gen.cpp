#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXM 1000000000
#define MAXN 1000000


int T;


void test_case(int maxm = MAXM, int maxn = MAXN)
{
	int m = rand() % (maxm + 1);
	int n = rand() % (maxn + 1);

	if (rand() % 2 == 0) swap(m, n);
	printf("%d %d\n", m, n);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < 10; ++i) test_case(100, 20);

	while (T) test_case();

	return 0;
}
