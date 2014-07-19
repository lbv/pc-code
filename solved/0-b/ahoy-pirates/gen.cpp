#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 10
#define MAXM   100
#define MAXTM  200
#define MAXLEN 50
#define MAXQ   1000
#define NCRIT 2
#endif

#if 0
#define MAXT 20
#define MAXM   5
#define MAXTM  20
#define MAXLEN 20
#define MAXQ   30
#define NCRIT 4
#endif


const char ops[] = "FEIS";
int T;


void gen(bool crit = false)
{
	int M = crit ? MAXM : rand() % MAXM + 1;

	printf("%d\n", M);
	int n = 0;

	while (M--) {
		int TM = rand() % MAXTM + 1;
		printf("%d\n", TM);
		int len = rand() % MAXLEN + 1;
		n += len*TM;
		for (int i = 0; i < len; ++i)
			putchar(rand() % 2 == 0 ? '0' : '1');
		putchar('\n');
	}

	int Q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", Q);

	for (int i = 1; i < Q; ++i) {
		char op = ops[rand() % 4];
		int b = rand() % n;
		int a = rand() % (b + 1);
		printf("%c %d %d\n", op, a, b);
	}
	printf("S 0 %d\n", n - 1);

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
