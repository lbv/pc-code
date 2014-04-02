#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
#include <utility>
using namespace std;


#if 0
#define MAXT 15
#define MAXN 50000
#define MAXW 10000

#define MINY -1000000000
#define MAXY 1000000000
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXW 10

#define MINY -100
#define MAXY 100
#endif


const int RangeY = MAXY - MINY + 1;


typedef pair<int, int> II;


int T;


void test_case(bool crit = false)
{
	int N = crit ? MAXN : rand() % MAXN + 1;
	int w = rand() % MAXW + 1;

	printf("\n%d %d\n", N, w);

	set<II> used;
	while (N--) {
		int x, y;
		do {
			x = rand() % RangeY + MINY;
			y = rand() % RangeY + MINY;
		} while (used.find(II(x, y)) != used.end());

		used.insert(II(x, y));
		printf("%d %d\n", x, y);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	test_case(true);
	while (T) test_case();

	return 0;
}
