//
// Knuth-Morris-Pratt
//
#define MAXW MAXLEN
struct KMP {
	int T[MAXW + 1];
	void init(const char *W, int lw) {
		T[0] = -1, T[1] = 0;
		for (int p = 2, c = 0; p < lw;) {
			if (W[p-1] == W[c]) T[p++] = ++c;
			else if (c > 0) c = T[c];
			else T[p++] = 0;
		}
	}

	// Return index of first occurrence of W inside S
	int search(const char *W, int lw, const char *S, int ls) {
		for (int m=0, i=0; m + i < ls;) {
			if (W[i] == S[m + i]) { if (++i == lw) return m; }
			else { m += i - T[i]; i = T[i] >= 0 ? T[i] : 0; }
		}
		return -1;
	}
};


//
// Suffix Array
//
const int MAXP = 3 * (3 * MAXLEN + 30) + (MAXLEN + 2)/3 + MAXLEN/3;
struct SuffixArray {
	int pool[MAXP];
	int *pp;

	bool leq(int a1, int a2, int b1, int b2) {
		return a1 < b1 || (a1 == b1 && a2 <= b2); }
	bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
		return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3)); }

	// stably sort a[0..n-1] to b[0..n-1] with keys in [0:k] from r
	void radix_pass(const int *a, int *b, const int *r, int n, int k)
	{
		int *c = pp;
		memset(c, 0, sizeof(int)*(k+1));
		for (int i = 0; i < n; ++i) ++c[r[a[i]]];
		for (int i = 0, sum = 0; i <= k; ++i) {
			int t = c[i]; c[i] = sum; sum += t; }
		for (int i = 0; i < n; ++i) b[ c[r[a[i]]]++ ] = a[i];
	}

	/*
	 * DC3 / Skew algorithm
	 *
	 * Adapted from sample code given in the paper "Simple Linear Work Suffix
	 * Array Construction" by Karkkainen, Sanders.
	 *
	 * S:  string, as a sequence of integers in the range [0:k]
	 * SA: array where the S.A. will be stored
	 * n:  length of s
	 * K:  size of alphabet (integer 0 will be used as marker)
	 *
	 * pre-cond: s[n]=s[n+1]=s[n+2] = 0, n >= 2
	 */
	void skew(const int *S, int *SA, int n, int K) {
		int n0 = (n+2) / 3, n1 = (n+1) / 3, n2 = n / 3, n02 = n0 + n2;

		int *S12 = pp; pp += n02 + 3;
		int *SA12 = pp; pp += n02 + 3;
		int *S0 = pp; pp += n0;
		int *SA0 = pp; pp += n0;
		S12[n02] = S12[n02 + 1] = S12[n02 + 2] = 0;
		SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = 0;

		for (int i = 1, j = 0; i < n+n0-n1; ++i) if (i % 3 != 0) S12[j++] = i;

		radix_pass(S12, SA12, S + 2, n02, K);
		radix_pass(SA12, S12, S + 1, n02, K);
		radix_pass(S12, SA12, S + 0, n02, K);

		int name = 0;
		int tri[3];
		memset(tri, -1, sizeof(tri));
		for (int i = 0; i < n02; ++i) {
			if (memcmp(S + SA12[i], tri, sizeof(tri)) != 0) {
				++name;
				memcpy(tri, S + SA12[i], sizeof(tri));
			}
			int off = SA12[i] % 3 == 1 ? 0 : n0;
			S12[SA12[i] / 3 + off] = name;
		}

		if (name < n02) {
			skew(S12, SA12, n02, name);
			for (int i = 0; i < n02; ++i) S12[SA12[i]] = i + 1;
		} else
			for (int i = 0; i < n02; ++i) SA12[S12[i] - 1] = i;

		for (int i = 0, j = 0; i < n02; ++i)
			if (SA12[i] < n0) S0[j++] = 3 * SA12[i];
		radix_pass(S0, SA0, S, n0, K);

#define GetI() (SA12[t] < n0 ? SA12[t]*3 + 1 : (SA12[t] - n0)*3 + 2)
		for (int p = 0, t = n0 - n1, k = 0; k < n; ++k) {
			int i = GetI();
			int j = SA0[p];

			if (SA12[t] < n0 ?
				leq(S[i], S12[SA12[t] + n0], S[j], S12[j / 3]) :
				leq(S[i], S[i + 1], S12[SA12[t] - n0 + 1],
					S[j], S[j + 1], S12[j / 3 + n0])) {
				SA[k] = i;
				if (++t == n02) for (++k; p < n0; ) SA[k++] = SA0[p++];
			} else {
				SA[k] = j;
				if (++p == n0) for (++k; t < n02; ++t) SA[k++] = GetI();
			}
		}
	}

	/*
	 * Calculate the suffix array, leaving it in {sa}.
	 *
	 * s: string
	 * n: length of s
	 * f: first letter of the alphabet
	 * k: size of the alphabet
	 */
	int si[MAXLEN + 3];
	int sa[MAXLEN];
	void calculate(const char *s, int n, char f, int k) {
		if (n < 2) { sa[0] = 0; return; }
		for (int i = 0; i < n; ++i) si[i] = s[i] - f + 1;
		si[n] = si[n + 1] = si[n + 2] = 0;
		pp = pool;
		skew(si, sa, n, k);
	}

	// Calculates the Longest Common Prefix between consecutive suffixes
	int rank[MAXLEN];
	int lcp[MAXLEN];
	void calc_lcp(const char *s, int n) {
		for (int i = 0; i < n; ++i) rank[sa[i]] = i;
		for (int i = 0, h = 0; i < n; ++i) {
			if (rank[i] == n - 1) { lcp[rank[i]] = 0; continue; }
			for (int j = sa[rank[i] + 1]; s[i + h] == s[j + h]; ++h) ;
			lcp[rank[i]] = h;
			if (h > 0) --h;
		}
	}

	void copy(int n, int *SA, int *LCP, int *RNK) {
		if (SA) memcpy(SA, sa, sizeof(int) * n);
		if (LCP) memcpy(LCP, lcp, sizeof(int) * n);
		if (RNK) memcpy(RNK, rank, sizeof(int) * n);
	}
};
