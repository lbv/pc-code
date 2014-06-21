#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


#if 0
#define MAXT 12
#define MAXN 100000
#define MAXR 1000000000
#define NCRIT 2
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXR 100000
#define NCRIT 5
#endif


int T;


void gen(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;

	vector<int> rs;
	for (int i = 0; i < n; ++i)
		rs.push_back(rand() % MAXR + 1);

	sort(rs.begin(), rs.end());
	vector<int>::iterator it = unique(rs.begin(), rs.end());
	rs.resize(it - rs.begin());

	n = rs.size();
	printf("%d\n%d", n, rs[0]);
	for (int i = 1; i < n; ++i)
		printf(" %d", rs[i]);
	putchar('\n');

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
