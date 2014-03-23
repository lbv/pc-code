/*
	Author       :	Jan
	Problem Name :	Birthday Paradox
	Algorithm    :	Math Prbability
	Complexity   :	O(sqrt(n))
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

#define MM 100001

const double eps = 1e-9;

int cases, caseno;
double f[MM];

int main() {
	freopen("e.in", "w", stdout);

	int i;
	cases = 19998;

    srand(time(NULL));
	printf("%d\n", cases);
	for( i = 1; i <= 10000; i++ ) {
		printf("%d\n", i);
		caseno++;
		cases--;
	}
	puts("100000");
	puts("99999");
	puts("1");
	cases-=3;
	caseno+=3;
	while(cases--) {
		int k;

		k = rand() % 100000;
		if( rand() % 10 == 0 ) k *= rand() % 1000;
		k %= 100000;
		k++;
		caseno++;
		if( caseno == 17412 ) {
			cases++;
			continue;
		}
		printf("%d\n", k);
	}
	return 0;
}

