#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT	 100
#define MAXN	 100
#define MAXW	 10000
#define MAXK	 100
#define MINCOORD -1000000000
#define MAXCOORD 1000000000
#define USE_X	 1
#define NCRIT 8
#endif

#if 1
#define MAXT	 20
#define MAXN	 15
#define MAXW	 200
#define MAXK	 12
#define MINCOORD -1000
#define MAXCOORD 1000
#define USE_X	 1
#define NCRIT 2
#endif


const int CoordRange = MAXCOORD - MINCOORD + 1;
const int INF = MAXCOORD + 10;


typedef pair<int, int> II;

typedef set<II> IIS;

II pts[MAXN];
int T;


void gen(bool crit = false)
{
	int N = crit ? MAXN : rand() % MAXN + 1;
	int w = rand() % MAXW + 1;
	int k = rand() % MAXK + 1;

	if (crit) N = MAXN;

	if (rand() % 5 != 0) k = rand() % N + 1;

	printf("\n%d %d %d\n", N, w, k);

	IIS s;
	for (int i = 0; i < N; ++i) {
		int x, y;
		do {
#if USE_X
			x = rand() % CoordRange + MINCOORD;
#else
			x = 0;
#endif
			y = rand() % CoordRange + MINCOORD;

			if (rand() % 3 != 0 && i > 0) {
				int idx = rand() % i;
				int delta = rand() % (w + 2) + 1;
				int r = rand() % 3;
				if (r == 0) delta = -delta;
				else if (r == 1) delta = 0;

				y = pts[idx].second + delta;
			}
		} while (y >= MINCOORD && y <= MAXCOORD && s.find(II(x, y)) != s.end());

		s.insert(II(x, y));
		pts[i] = II(x, y);
		printf("%d %d\n", x, y);
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
