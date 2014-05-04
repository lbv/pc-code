#include <cstdio>
#include <cstring>


#define MAXLEN 1000


typedef char LisT;
LisT I[MAXLEN + 1];
int lis(LisT *seq, int n)
{
	int len = 0;
	for (int i = 0; i < n; ++i) {
		int lo = 1, hi = len;
		while (lo <= hi) {
			int m = (lo + hi) / 2;
			if (I[m] < seq[i]) lo = m + 1;
			else hi = m - 1;
		}
		I[lo] = seq[i];
		if (len < lo) len = lo;
	}
	return len;
}


char input[MAXLEN + 1];


int solve()
{
	return lis(input, strlen(input));
}

int main()
{
	int ncase = 0;
	while (true) {
		scanf("%s", input);
		if (input[0] == 'e') break;

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
