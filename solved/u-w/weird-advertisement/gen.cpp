#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 1
#define MAXT 13
#define MAXN 30000
#define MAXK 10
#define MAXX 1000000000
#define NCRIT 2
#endif

#if 0
#define MAXT 20
#define MAXN 3
#define MAXK 3
#define MAXX 20
#define NCRIT 4
#define NL 1
#endif


int T;


int gen_coord()
{
	int x = rand() % (MAXX + 1);
	int r = rand() % 3;
	
	if (r == 0 && x > 1000) x = rand() % 1000;
	if (r == 1 && x > 1000000) x = rand() % 1000000;
	
	return x;
}

void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	int k = rand() % MAXK + 1;
	printf("%d %d\n", n, k);

	while (n--) {
		int x1, y1, x2, y2;

		do {
			x1 = gen_coord();
			y1 = gen_coord();
			x2 = gen_coord();
			y2 = gen_coord();
		} while (x1 == x2 || y1 == y2);

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		printf("%d %d %d %d\n", x1, y1, x2, y2);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
