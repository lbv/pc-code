#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 50
#define MAXN 1000
#define MAXM 10000
#define MAXLEN 10
#define ALPHA 26
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXM 20
#define MAXLEN 5
#define NCRIT 4
#define ALPHA 6
#define NL 1
#endif

#define Clr(m) memset(m, 0, sizeof(m))


struct Drink {
	char name[MAXLEN + 1];

	bool operator<(const Drink &x) const { return strcmp(name, x.name) < 0; }
	bool operator==(const Drink &x) const { return strcmp(name, x.name) == 0; }
};


int T;
Drink drinks[MAXN];
bool g[MAXN][MAXN];


void gen_drink(int i)
{
	Drink &d = drinks[i];

	int len = rand() % MAXLEN + 1;
	for (int i = 0; i < len; ++i)
		d.name[i] = 'a' + (rand() % ALPHA);
	d.name[len] = 0;
}

void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;

	for (int i = 0; i < n; ++i) gen_drink(i);
	while (drinks[0] == drinks[1]) gen_drink(0);
	sort(drinks, drinks + n);
	n = unique(drinks, drinks + n) - drinks;

	int maxm = min(n*(n-1)/2, MAXM);
	int m = crit ? maxm : rand() % maxm + 1;

	printf("%d\n", m);
	Clr(g);
	while (m--) {
		int u, v;
		do {
			u = rand() % n;
			v = rand() % n;
		} while (u == v || g[u][v]);
		g[u][v] = g[v][u] = true;

		printf("%s %s\n", drinks[u].name, drinks[v].name);
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
