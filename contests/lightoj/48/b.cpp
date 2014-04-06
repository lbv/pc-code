/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem B: Ja Issa Tai
 *
 * Keywords:
 *   - geometry
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;


typedef double GeomT;


const double pi = acos(-1.0);
int a, b, c;


GeomT triangle_opp_angle(GeomT a, GeomT b, GeomT c)
{
	return acos((b*b + c*c - a*a) / (b * c * 2));
}

void solve()
{
	if (a + b <= c || a + c <= b || b + c <= a) {
		puts("They can't sit in a triangle :-(");
		return;
	}

	double best = pi;
	double ang;

	int tri = 0, dear = 0;

	ang = triangle_opp_angle(a, b, c);
	if (ang < best)
		tri = max(b, c), dear = min(b, c), best = ang;

	ang = triangle_opp_angle(b, a, c);
	if (ang < best)
		tri = max(a, c), dear = min(a, c), best = ang;

	ang = triangle_opp_angle(c, a, b);
	if (ang < best)
		tri = max(a, b), dear = min(a, b), best = ang;

	int iang = best / pi * 180;
	printf(
		"\"Triangle\" should sit on chair with size %d\n"
		"\"Dear\" should sit on chair with size %d\n"
		"The angle between them is %d\n", tri, dear, iang);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &a, &b, &c);
		printf("Case %d:\n", ++ncase);
		solve();
	}

	return 0;
}
