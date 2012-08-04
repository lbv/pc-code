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

int main() {
	// freopen("a.in", "w", stdout);

    srand(time(NULL));

	double cl = clock();

	int cases = 9995;
	printf("%d\n", cases);
	while( cases-- ) {
	    /*
		double L = rand() % 20000000 + 1000;
		double W = rand() % 20000000 + 1000;
		*/
		double L = rand() % 200000 + 1000;
		double W = rand() % 200000 + 1000;

		L /= 2000;
		W /= 2000;

		printf("%.2lf %.2lf\n", L, W);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

