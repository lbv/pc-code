/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
	Complexity   :
*/

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int cases, caseno;

int main() {
	freopen("a.in", "w", stdout);

	double cl = clock();

	int cases = 95;
	printf("%d\n", cases);
	while( cases-- ) {
		int vv1 = rand() % 9999 + 1;
		int vv2 = rand() % 9999 + 1;
		int vv3 = rand() % 10000 + 1;

		if( vv3 < vv1 ) swap( vv3, vv1 );
		if( vv3 < vv2 ) swap( vv2, vv3 );

		if( vv3 == vv1 ) vv3++;
		if( vv3 == vv2 ) vv3++;

		double v1, v2, v3, a1, a2;

		v1 = vv1 / 10.0;
		v2 = vv2 / 10.0;
		v3 = vv3 / 10.0;

		if( rand() % 6 == 0 ) {
			v1 = vv1 / 100.0;
			v2 = vv2 / 100.0;
			v3 = vv3 / 100.0;
		}

		if( rand() % 6 == 0 ) {
			v1 = vv1 / 1000.0;
			v2 = vv2 / 1000.0;
			v3 = vv3 / 1000.0;
		}

		a1 = ( rand() % 10000 + 1 ) / 10.0;
		a2 = ( rand() % 10000 + 1 ) / 10.0;

		if( rand() % 6 == 0 ) {
			a1 = ( rand() % 10000 + 1 ) / 100.0;
			a2 = ( rand() % 10000 + 1 ) / 100.0;
		}
		if( rand() % 6 == 0 ) {
			a1 = ( rand() % 10000 + 1 ) / 1000.0;
			a2 = ( rand() % 10000 + 1 ) / 1000.0;
		}

		printf("%.3lf %.3lf %.3lf %.3lf %.3lf\n", v1, v2, v3, a1, a2);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

