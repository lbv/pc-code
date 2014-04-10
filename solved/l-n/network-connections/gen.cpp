#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXN 100
#define MAXC 200
#define MAXQ 100
#define NCRIT 10

#define Clr(m) memset(m, 0, sizeof(m))


struct Comm {
	char c;
	int u, v;

	Comm() {}
	Comm(char C, int U, int V): c(C), u(U), v(V) {}
};


int T;

bool used[MAXN + 1][MAXN + 1];
Comm comm[MAXC + MAXQ];


void test_case(bool crit = false)
{
	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
	printf("\n%d\n", n);

	int maxc = min(MAXC, n * (n-1)/2);

	int c = crit ? maxc : rand() % (maxc + 1);
	int q = crit ? MAXQ : rand() % (MAXQ + 1);

	int ncomm = 0;
	Clr(used);
	while (c--) {
		int u, v;
		do {
			u = rand() % n + 1;
			v = rand() % n + 1;
		} while (u == v || used[u][v]);
		used[u][v] = used[v][u] = true;

		comm[ncomm++] = Comm('c', u, v);
	}

	while (q--) {
		int u, v;
		do {
			u = rand() % n + 1;
			v = rand() % n + 1;
		} while (u == v);

		comm[ncomm++] = Comm('q', u, v);
	}

	random_shuffle(comm, comm + ncomm);

	for (int i = 0; i < ncomm; ++i)
		printf("%c %d %d\n", comm[i].c, comm[i].u, comm[i].v);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	return 0;
}
