/**
 * LightOJ Contest #477: Exam Ending Contest
 *
 * Problem C: Fair and Square
 *
 * Keywords:
 *	 - ad-hoc
 *	 - palindromes
 */

#include <cstdio>
#include <cstring>


#define MAXB 1000


bool fas[MAXB+1];  // is fair and square
int psum[MAXB+1];  // prefix sum of amount of fair and square numbers
char aux[16];
int A, B;


bool is_palin(int x)
{
	sprintf(aux, "%d", x);
	int l = strlen(aux);
	for (int i = 0, j = l - 1; i < j; ++i, --j)
		if (aux[i] != aux[j]) return false;
	return true;
}

void prepare()
{
	for (int i = 1; true; ++i) {
		int ii = i*i;
		if (ii > MAXB) break;

		if (is_palin(i) && is_palin(ii))
			fas[ii] = true;
	}

	for (int i = 1; i <= MAXB; ++i) {
		psum[i] = psum[i-1];
		if (fas[i]) ++psum[i];
	}
}

int solve()
{
	return psum[B] - psum[A-1];
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &A, &B);
		printf("Case #%d: %d\n", ++ncase, solve());
	}

	return 0;
}
