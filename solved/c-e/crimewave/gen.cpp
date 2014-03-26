#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXT 100
#define MAXS 50
#define MAXA 50

#define Clr(m) memset(m, 0, sizeof(m))


int T;

bool vis[MAXS + 1][MAXA + 1];


void test_case(bool crit = false)
{
	int s = crit ? MAXS : rand() % MAXS + 1;
	int a = crit ? MAXA : rand() % MAXA + 1;

	int maxb = s*a;
	int b = rand() % maxb + 1;
	printf("%d %d %d\n", s, a, b);

	Clr(vis);
	while (b--) {
		int x, y;
		do {
			x = rand() % s + 1;
			y = rand() % a + 1;
		} while (vis[x][y]);
		vis[x][y] = true;
		printf("%d %d\n", x, y);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < 5; ++i) test_case(true);

	while (T) test_case();

	return 0;
}
