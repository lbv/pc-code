#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 1
#define MAXT 4000
#define MAXC 200
#endif

#if 0
#define MAXT 100
#define MAXC 15
#endif


int T;


void test_case()
{
	int x = rand() % (MAXC + 1);
	int y = rand() % (MAXC + 1);
	int r = rand() % (MAXC + 1);

	printf("%d %d %d\n", x, y, r);

	int x1, y1, x2, y2;
	do {
		x1 = rand() % (MAXC + 1);
		y1 = rand() % (MAXC + 1);
		x2 = rand() % (MAXC + 1);
		y2 = rand() % (MAXC + 1);
	} while(x1 == x2 || y1 == y2);

	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);

	printf("%d %d %d %d\n", x1, y1, x2, y2);

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
