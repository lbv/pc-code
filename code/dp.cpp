//
// Classic DP routines
//


//
// LIS
// Returns the length of the LIS and store lengths for each element of seq
// in ls
//
typedef int LisT;
LisT I[MAXN + 1];
int lis(const LisT *seq, int n, LisT *ls)
{
	int len = 0;
	for (int i = 0; i < n; ++i) {
		int lo = 1, hi = len;
		while (lo <= hi) {
			int m = (lo + hi) / 2;
			if (I[m] < seq[i]) lo = m + 1;
			else hi = m - 1;
		}
		I[lo] = seq[i], ls[i] = lo;
		if (len < lo) len = lo;
	}
	return len;
}


//
// Coin change
//	 W:  answer
//	 C:  coin values
//	 n:  number of coins
//	 k:  maximum amount of money
//	 pre-cond: W is cleared
//
void cc(int *W, const int *C, int n, int k)
{
	W[0] = 1;
	for (int i = n - 1; i >= 0; --i)
		for (int a = 0, b = C[i]; b <= k; ++a, ++b)
			W[b] = (W[b] + W[a]) % MOD;
}


//
// DPString
// Similar to a Trie. Useful for DP problems in which a certain string (for
// example, the lexicographically lowest) is requested.
//
const int MAX_NODES = MAXLEN;
char buf[MAXLEN + 1];
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


//
// CYK (Cocke-Younger-Kasami) algorithm for parsing context-free grammars
//
const int MaxN = MAXC;       // max length of input string
const int MaxS = MAXCOLORS;  // max number of symbols

struct Rule { int X, A, B; };  // X -> A B

// CYK(i, j, k) is the interface to the DP table. Each cell is true if
// symbol k produces the substring Si..Sj
int CYK_N, CYK_S;
#define CYK(i,j,k)       (_cyk_dp[(i)*CYK_N*CYK_S + (j)*CYK_S + (k)])
#define CYK_AUX(i,j)     (_cyk_aux[(i)*CYK_N + (j)])
#define CYK_SET(i, j, k) (CYK_AUX(i, j) = CYK(i, j, k) = true)
bool _cyk_dp[MaxN * MaxN * MaxS];
bool _cyk_aux[MaxN * MaxN];  // for optimization purposes

// call with the length of the input string (N) and the number of symbols (S)
void cyk_init(int N, int S)
{
	Clr(_cyk_dp);
	Clr(_cyk_aux);
	CYK_N = N, CYK_S = S;
}

// pre-cond: calling cyk_init, and then calling CYK_SET(i, i, k) for each i
// if the ith token is symbol k
void cyk_run(Rule *rs, int R)
{
	for (int sz = 2; sz <= CYK_N; ++sz)
		for (int i = 0, j = i+sz-1; j < CYK_N; ++i, ++j)
			for (int k = i; k < j; ++k)
				if (CYK_AUX(i, k) && CYK_AUX(k+1, j))
					for (int p = 0; p < R; ++p) {
						Rule &r = rs[p];

						if (CYK(i, k, r.A) && CYK(k+1, j, r.B))
							CYK_SET(i, j, r.X);
					}

	// post-cond: CYK(0, N-1, k) == true iff the symbol k produces the input
}
