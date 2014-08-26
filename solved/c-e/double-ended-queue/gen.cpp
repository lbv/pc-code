#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 10
#define MAXM 100
#define MINX -100
#define MAXX 100
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXM 16
#define MINX -100
#define MAXX 100
#define NL	 1
#define NCRIT 2
#endif


const int XRange = MAXX - MINX + 1;
const char cmds[4][20] = {
	"pushLeft",
	"pushRight",
	"popLeft",
	"popRight"
};

int T;


void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	int m = crit ? MAXM : rand() % MAXM + 1;
	printf("%d %d\n", n, m);

	while (m--) {
		int cmd = rand() % 4;
		printf("%s", cmds[cmd]);
		if (cmd <= 1) {
			int x = rand() % XRange + MINX;
			printf(" %d", x);
		}
		putchar('\n');
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
