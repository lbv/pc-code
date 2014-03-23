#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;


#define MAXN 100000

#define MAXNM (2*MAXN + 1)

#define Memset(m,v) memset(m, v, sizeof(m))
#define Clr(m) Memset(m,0)


typedef long long i64;
typedef pair<int, int> II;


II grp1[MAXN], grp2[MAXN];
II *blue, *red;

int tb[MAXNM];  // tb[i]: total of blue soldiers in the range [0:i]
int lb[MAXNM];  // lb[i]: location of blue soldier whose hook is "closest" to i
int hb[MAXNM];  // hb[i]: location of hook of blue soldier located at i

int n, m;


void process()
{
	Clr(hb);

	int tIdx, lIdx, lastLoc;

	tIdx = lIdx = 0;
	lastLoc = -1;

	for (int i = 0; i < n; ++i) {
		II &b = blue[i];

		while (tIdx < b.first) tb[tIdx++] = i;
		tb[tIdx++] = i + 1;

		while (lIdx < b.second) lb[lIdx++] = lastLoc;
		lb[lIdx++] = lastLoc = b.first;

		hb[b.first] = b.second;
	}

	int nm = n + m;
	while (tIdx <= nm)
		tb[tIdx++] = n;

	while (lIdx <= nm)
		lb[lIdx++] = lastLoc;
}

i64 solve()
{
	sort(blue, blue + n);
	sort(red, red + m);

	// this algorithm requires that the leftmost hook is blue
	if (red[0].second < blue[0].second) {
		swap(red, blue);
		swap(n, m);
	}

	process();

	i64 ans = 0;

	// iterate over the red ones, each pass checking how many blues intersect
	for (int i = 0; i < m; ++i) {
		II &r = red[i];

		int l = lb[r.second];

		if (l > r.first)
			ans += tb[l] - tb[r.first];
		else if (l > 0) {
			ans += tb[r.first] - tb[l];
			if (hb[l] >= r.second) ++ans;
		}
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &m);

		blue = grp1, red = grp2;
		int i, j;
		for (int k = 0; k < n; ++k) {
			scanf("%d%d", &i, &j);
			blue[k] = II(i, j);
		}
		for (int k = 0; k < m; ++k) {
			scanf("%d%d", &i, &j);
			red[k] = II(i, j);
		}

		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}
