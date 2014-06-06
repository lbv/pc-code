#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXLENA 100
#define MAXLENB 100
#define MAXLENC 300
#define MOD 1000000007
#define INF 310

const int ALPHA = 26;

#define Neg(m) memset(m, -1, sizeof(m))
#define Mod(x) ((x) >= MOD ? (x) % MOD : (x))


const int MAX_NODES = (MAXLENA+1) * (MAXLENB+1) * (MAXLENC+1);
char buf[MAXLENA + MAXLENB + 1];
struct DPString {
	struct Node {
		int p;   // parent
		char c;  // character
	};
	Node nodes[MAX_NODES];
	int n;

	void init() { nodes[0].p = -1, nodes[0].c = 0, n = 1; }
	int append(int node, char c) {
		nodes[n].p = node;
		nodes[n].c = c;
		return n++;
	}
	void print(int k) const {
		for (int len=0; k >= 0; k = nodes[k].p) buf[len++] = nodes[k].c;
		puts(buf);
	}
};

DPString dps;

struct State {
	int n;    // number of distinct sequences
	int s;    // index of the DPString node that represents the lowest sequence
	short l;  // length of the sequences
	short i;  // counter to check if it needs to be calculated

	State &set(int N, short L, int S) { n=N, l=L, s=S; return *this; }
	State &set(const State &x) { n=x.n, l=x.l, s=x.s; return *this; }
};


char A[MAXLENA + 1];
char B[MAXLENB + 1];
char C[MAXLENC + 1];
int la, lb, lc;
short gidx;

State dp[MAXLENA + 1][MAXLENB + 1][MAXLENC + 1];

int prev[MAXLENC][ALPHA];


void reverse(char *s, int n)
{
	for (int i = 0, j = n-1; i < j; ++i, --j) swap(s[i], s[j]);
}

void state_merge(State &x, const State &y, char suf)
{
	if (y.l >= x.l) return;
	if (y.l + 1 < x.l) {
		x.set(y.n, y.l + 1, dps.append(y.s, suf));
		return;
	}

	int n = Mod(x.n + y.n);
	int s = dps.nodes[x.s].c < suf ? x.s : dps.append(y.s, suf);

	x.set(n, y.l + 1, s);
}


State fun(int a, int b, int c)
{
	if (dp[a][b][c].i == gidx) return dp[a][b][c];

	State &st = dp[a][b][c];
	st.i = gidx;

	if (a == 0 && b == 0)
		return st.set(1, 0, 0);

	st.set(0, INF, -1);
	if (a > c || b > c) return st;

	if (a > 0 && b > 0 && A[a-1] == B[b-1]) {
		int idx = prev[c-1][ A[a-1] - 'a' ];
		if (idx >= 0) {
			State x = fun(a-1, b-1, idx);
			st.set(x.n, x.l + 1, dps.append(x.s, A[a-1]));
		}
		return st;
	}

	if (a > 0) {
		int idx = prev[c-1][ A[a-1] - 'a' ];
		if (idx >= 0) {
			State x = fun(a-1, b, idx);
			state_merge(st, x, A[a-1]);
		}
	}

	if (b > 0) {
		int idx = prev[c-1][ B[b-1] - 'a' ];
		if (idx >= 0) {
			State x = fun(a, b-1, idx);
			state_merge(st, x, B[b-1]);
		}
	}

	return st;
}

State solve()
{
	la = strlen(A);
	lb = strlen(B);
	lc = strlen(C);
	reverse(A, la);
	reverse(B, lb);
	reverse(C, lc);

	++gidx;
	dps.init();

	Neg(prev);
	for (int i = 0; i < lc; ++i)
		for (int j = i; j >= 0; --j) {
			int k = C[j] - 'a';
			if (prev[i][k] < 0)
				prev[i][k] = j;
		}

	return fun(la, lb, lc);
}

int main()
{
	int T;
	scanf("%d", &T);
	gets(A);

	int ncase = 0;
	while (T--) {
		gets(A);
		gets(B);
		gets(C);

		State ans = solve();
		printf("Case %d: %d\n", ++ncase, ans.n);

		if (ans.l < INF) dps.print(ans.s);
		else puts("NOT FOUND");
	}

	return 0;
}
