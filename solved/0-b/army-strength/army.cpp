#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000000


int g[MAXN];
int m[MAXN];

int NG, NM;


bool solve()
{
	sort(g, g + NG);
	sort(m, m + NM);

	int ig = 0, im = 0;
	for (; ig < NG && im < NM;)
		if (m[im] <= g[ig]) ++im;
		else ++ig;

	return ig < NG;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d", &NG, &NM);

		for (int i = 0; i < NG; ++i) scanf("%d", &g[i]);
		for (int i = 0; i < NM; ++i) scanf("%d", &m[i]);

		puts(solve() ? "Godzilla" : "MechaGodzilla");
	}

	return 0;
}
