/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem E: The Mathmatician
 *
 * Keywords:
 *   - probability
 *   - combinatorial
 */

#include <cmath>
#include <cstdio>


#define MAXN 20


typedef unsigned long long u64;


// Binomial coefficients
#define BCSIZE MAXN
u64 bc[BCSIZE + 1][BCSIZE + 1];
void choose_table() {
	for (int n = 1; n <= BCSIZE; n++) { bc[n][n] = 1; bc[n][1] = n; }
	for (int n = 3; n <= BCSIZE; n++)
		for (int k = 2; k < n; k++)
			bc[n][k] = bc[n-1][k-1] + bc[n-1][k];
}


int n, k;
double p, q;


double solve()
{
	return pow(p, n-k) * pow(q, k) * bc[n][k] + 1e-8;
}

int main()
{
	choose_table();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%lf%lf%d", &n, &p, &q, &k);
		printf("Case %d: %.4lf\n", ++ncase, solve());
	}

	return 0;
}
