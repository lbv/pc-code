#include <algorithm>
#include <cstdio>
using namespace std;


typedef long long i64;


int n, m, q;

int players[11][2];


void rotate()
{
	for (int i = 0; i < 11; ++i) {
		int &r = players[i][0];
		int &c = players[i][1];

		int rp = c;
		int cp = n - r + 1;

		r = rp, c = cp;
	}

	swap(n, m);
}

void flip()
{
	for (int i = 0; i < 11; ++i) {
		int &c = players[i][1];
		c = m - c + 1;
	}
}

void query()
{
	int type;
	scanf("%d", &type);

	if (type == 1) {
		int c, a, h, v;
		scanf("%d%d%d%d", &c, &a, &h, &v);

		i64 r = (c + 3LL*a) % 4;
		if (r)
			for (int i = 0; i < r; ++i) rotate();

		h %= 2;
		if (h) {
			flip();
			rotate();
			rotate();
		}

		v %= 2;
		if (v) flip();
	}
	else {
		int p;
		scanf("%d", &p);

		printf("%d %d\n", players[p-1][0], players[p-1][1]);
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &n, &m, &q);

		for (int i = 0; i < 11; ++i)
			scanf("%d%d", &players[i][0], &players[i][1]);

		printf("Case %d:\n", ++ncase);

		while (q--)
			query();
	}

	return 0;
}
