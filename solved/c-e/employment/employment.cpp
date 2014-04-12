#include <cstdio>
#include <cstring>


#define MAXN 100


#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))



//
// Stable Marriage Problem
//

// man[i][j]: woman with priority j for man i
int man[MAXN][MAXN];

// woman[i][j]: priority for man j given by woman i
int woman[MAXN][MAXN];

// next_for[i]: next priority to consider for man i
int next_for[MAXN];

struct Marriage {
	int w, m;
	Marriage() {}
	Marriage(int W, int M): w(W), m(M) {}

	bool operator<(const Marriage &x) const {
		return woman[w][m] > woman[x.w][x.m];
	}
};

// marriage[j]: current marriage for woman j
Marriage marriage[MAXN];

// Gale-Shapley algorithm.
// pre-cond: Clr(next_for) Neg(marriage)
void stable_match(int m)
{
	// if a solution is not guaranteed, add check here to see if maybe there
	// are no more matches

	int w = man[m][ next_for[m]++ ];

	Marriage cur(w, m);

	if (marriage[w].m < 0)
		marriage[w] = cur;
	else if (marriage[w] < cur) {
		int mp = marriage[w].m;
		marriage[w] = cur;
		stable_match(mp);
	}
	else
		stable_match(m);
}


int n;

void solve()
{
	Clr(next_for);
	Neg(marriage);

	for (int i = 0; i < n; ++i)
		stable_match(i);

	for (int i = 0; i < n; ++i)
		printf(" (%d %d)", marriage[i].m + 1, marriage[i].w + n + 1);
	putchar('\n');
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);

		int p;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				scanf("%d", &p);
				man[i][j] = p - (n+1);
			}

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				scanf("%d", &p);
				woman[i][p-1] = j;
			}

		printf("Case %d:", ++ncase);
		solve();
	}

	return 0;
}
