#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 50
#define MAXM 100
#define MAXC 10000


int T;


void test_case()
{
	int x1, y1, x2, y2;
	do {
		x1 = rand() % (MAXC + 1);
		y1 = rand() % (MAXC + 1);
		x2 = rand() % (MAXC + 1);
		y2 = rand() % (MAXC + 1);
	} while (x1 == x2 || y1 == y2);

	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);

	printf("%d %d %d %d\n", x1, y1, x2, y2);

	int M = rand() % MAXM + 1;
	printf("%d\n", M);

	while (M--) {
		int x, y;
		do {
			x = rand() % (MAXC + 1);
			y = rand() % (MAXC + 1);
		} while (x == x1 || x == x2 || y == y1 || y == y2);
		printf("%d %d\n", x, y);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) test_case();

	return 0;
}
