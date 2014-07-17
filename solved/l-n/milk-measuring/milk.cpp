#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXQ 20000
#define MAXP 100

#define INF 0x3f3f3f3f

#define InfN(m,n,t) memset(m, 0x3f, sizeof(t)*(n))


struct Trail {
	int p;  // quarts of the current pail
	int n;  // index of next node
};
Trail trail[2*MAXQ*MAXP+1];
int ntrail;


void print_trail(int x)
{
	if (trail[x].p < 0) return;
	printf(" %d", trail[x].p);
	print_trail(trail[x].n);
}

bool cmp_trail(int a, int b)
{
	while (a != b && trail[a].n >= 0 && trail[b].n >= 0
	       && trail[a].p == trail[b].p)
		a = trail[a].n, b = trail[b].n;

	return trail[a].p < trail[b].p;
}

struct State {
	int n;  // number of pails used
	int t;  // index of trail node

	int last() const { return t < ntrail ? trail[t].p : INF; }
	State add(int p) const {
		trail[ntrail++] = (Trail) { p, t };
		return (State) { n + 1, ntrail - 1 };
	}
	void merge(const State &x) {
		if (x.n >= INF || x.n > n) return;
		if (x.n < n || cmp_trail(x.t, t))
			n = x.n, t = x.t;
	}
};


int Q, P;
int ps[MAXP];

State _dp1[MAXQ + 1];
State _dp2[MAXQ + 1];


State solve()
{
	sort(ps, ps + P);

	ntrail = 0;
	trail[ntrail++] = (Trail) { -1, -1 };

	InfN(_dp1, Q+1, State);
	_dp1[0] = (State) { 0, 0 };

	State *dp1 = _dp1;
	State *dp2 = _dp2;

	for (int i = P-1; i >= 0; --i) {
		int p = ps[i];

		memcpy(dp2, dp1, sizeof(State) * (Q+1));

		for (int j = 0; j < p; ++j) {
			State best = (State) { INF, INF };
			for (int q = p + j; q <= Q; q += p) {
				if (dp1[q-p].n < INF)
					best.merge(dp1[q-p].add(p));
				dp2[q].merge(best);
			}
		}

		swap(dp1, dp2);
	}

	return dp1[Q];
}


int main()
{
	scanf("%d%d", &Q, &P);
	for (int i = 0; i < P; ++i) scanf("%d", &ps[i]);

	State ans = solve();

	printf("%d", ans.n);
	print_trail(ans.t);
	putchar('\n');

	return 0;
}
