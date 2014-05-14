#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 5000


struct Stick {
	int l, w;
};

bool cmp_desc(const Stick &a, const Stick &b)
{
	if (a.l != b.l) return a.l > b.l;
	return a.w > b.w;
}

bool cmp_w(const Stick &a, const Stick &b) { return a.w < b.w; }


typedef Stick LisT;
LisT I[MAXN + 1];
int lis(const LisT *seq, int n)
{
	int len = 0;
	for (int i = 0; i < n; ++i) {
		int lo = 1, hi = len;
		while (lo <= hi) {
			int m = (lo + hi) / 2;
			if (cmp_w(I[m], seq[i])) lo = m + 1;
			else hi = m - 1;
		}
		I[lo] = seq[i];
		if (len < lo) len = lo;
	}
	return len;
}


int n;
Stick tuples[MAXN];


int solve()
{
	sort(tuples, tuples + n, cmp_desc);

	return lis(tuples, n);
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d%d", &tuples[i].l, &tuples[i].w);
		printf("%d\n", solve());
	}

	return 0;
}
