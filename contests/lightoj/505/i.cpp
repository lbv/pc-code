/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem I: RhyHan and Pizza
 *
 * Keywords:
 *   - geometry
 */

#include <cmath>
#include <cstdio>


const double pi_t2 = 2 * acos(-1);


int N, R, H, W;


void solve()
{
	double ang = pi_t2 / N;
	double arc = ang * R;

	H = R;
	W = arc * N/2.0;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &N, &R);
		solve();
		printf("Case %d: %d %d\n", ++ncase, H, W);
	}

	return 0;
}
