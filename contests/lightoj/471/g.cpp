/**
 * LightOJ Contest #471: AIUB Practice Contest
 *
 * Problem G: Grand Sort
 *
 * Keywords:
 *   - sorting
 *   - beginner
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 1000
#define MAXLEN 100


struct Player {
	char name[MAXLEN + 1];
	int t;

	bool operator<(const Player &p) const {
		if (t != p.t) return t > p.t;
		return strcmp(name, p.name) < 0;
	}
};


int N;

Player ps[MAXN];


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);

		for (int i = 0; i < N; ++i)
			scanf("%s%d", ps[i].name, &ps[i].t);

		sort(ps, ps + N);

		if (ncase > 0) putchar('\n');
		printf("Case %d:\n", ++ncase);

		for (int i = 0; i < N; ++i)
			printf("%s\n", ps[i].name);
	}

	return 0;
}
