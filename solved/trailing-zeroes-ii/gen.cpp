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

int main() {
	freopen("c.in", "w", stdout);

	double cl = clock();

	int cases = 10000;
	printf("%d\n", cases);
	while( cases-- ) {
		int n = rand() % 1000000 + 1;
		int r = rand() % n + 1;
		int p = rand() % 1000000 + 1;
		int q = rand() % 1000000 + 1;

		printf("%d %d %d %d\n", n, r, p, q);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);
	return 0;
}

