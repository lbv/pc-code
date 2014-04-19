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
