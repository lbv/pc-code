#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 100
#define MAXB 16
#define MAXK 20
#endif

#if 1
#define MAXT 20
#define MAXB 16
#define MAXK 20
#endif


#define Clr(m) memset(m, 0, sizeof(m))
#define Rand(lo,hi) (rand() % ((hi)-(lo)+1) + (lo))


const char dig[] = "0123456789ABCDEF";


int T;
char num[MAXB+1];
bool used[MAXB];


void gen(bool crit = false)
{
	int base = Rand(2, MAXB);
	int K = Rand(1, MAXK);
	int len = Rand(1, base);

	Clr(used);
	for (int i = 0; i < len; ++i) {
		int d;
		do {
			d = Rand(0, base-1);
		} while (used[d]);
		used[d] = true;
		num[i] = dig[d];
	}
	num[len] = 0;

	printf("\n%d %d\n%s\n", base, K, num);
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
