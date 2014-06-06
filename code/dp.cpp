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
