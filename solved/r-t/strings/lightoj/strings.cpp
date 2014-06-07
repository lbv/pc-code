#include <cstdio>
#include <cstring>


#define MAXLENA 100
#define MAXLENB 100
#define MAXLENC 100
#define MOD 1000000007

const int ALPHA = 26;

#define Mod(x) ((x) >= MOD ? (x) % MOD : (x))
#define Neg(m) memset(m, -1, sizeof(m))


struct State {
	int c;  // DP count
	int v;  // visited counted

	void inc(int C) { c = Mod(c + C); }
};

char A[MAXLENA + 1];
char B[MAXLENB + 1];
char C[MAXLENC + 1];

int gvis;

// dp[a][b][c][x]: Number of ways to combine the first a chars of A and the
// first b chars of B to produce C, finishing in a letter from x (0: A, 1: B)
State dp[MAXLENA + 1][MAXLENB + 1][MAXLENC + 1][2];

int prev_a[MAXLENA][ALPHA];
int prev_b[MAXLENB][ALPHA];


State fun(int a, int b, int c, int x)
{
	if (dp[a][b][c][x].v == gvis) return dp[a][b][c][x];

	State &st = dp[a][b][c][x];
	st.c = 0;
	st.v = gvis;

	if (c == 0) {
		if (x == 0) st.inc(1);
		return st;
	}

	int idx = C[c-1] - 'a';
	int p = a > 0 ? prev_a[a-1][idx] : -1;
	int q = b > 0 ? prev_b[b-1][idx] : -1;

	if (x == 0 && p >= 0) {
		st.inc(fun(p, b, c-1, 0).c);
		st.inc(fun(p, b, c-1, 1).c);
		st.inc(fun(p, b, c, 0).c);
	}
	else if (x == 1 && q >= 0) {
		st.inc(fun(a, q, c-1, 0).c);
		st.inc(fun(a, q, c-1, 1).c);
		st.inc(fun(a, q, c, 1).c);
	}

	return st;
}

void calc_prev(int prev[][ALPHA], const char *s, int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = i; j >= 0; --j) {
			int idx = s[j] - 'a';
			if (prev[i][idx] < 0)
				prev[i][idx] = j;
		}
}

int solve()
{
	int la = strlen(A);
	int lb = strlen(B);
	int lc = strlen(C);

	++gvis;

	Neg(prev_a);
	calc_prev(prev_a, A, la);
	Neg(prev_b);
	calc_prev(prev_b, B, lb);

	return Mod(fun(la, lb, lc, 0).c + fun(la, lb, lc, 1).c);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%s%s%s", A, B, C);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
