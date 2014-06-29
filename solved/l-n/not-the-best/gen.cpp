#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXN 5000
#define MAXR 100000
#define MAXW 5000
#endif

#if 1
#define MAXT 20
#define MAXN 6
#define MAXR 8
#define MAXW 100
#endif


int T;


void gen()
{
	int N = rand() % (MAXN - 1) + 2;
	int R = rand() % (MAXR - N + 1) + N;

	printf("%d %d\n", N, R);

	int u, v, w;
	for (int i = 1; i <= N - 1; ++i) {
		u = i;
		v = i + 1;
		w = rand() % MAXR + 1;
		printf("%d %d %d\n", u, v, w);
		R--;
	}

	while (R--) {
		do {
			u = rand() % N + 1;
			v = rand() % N + 1;
		} while (u == v);

		w = rand() % MAXR + 1;
		printf("%d %d %d\n", u, v, w);
	}

	--T;
}

int main()
{
	srand(time(NULL));
	T = MAXT;
	printf("%d\n", T);

	while (T) gen();
	return 0;
}
