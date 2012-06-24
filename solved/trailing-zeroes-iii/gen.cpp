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

int cases = 9999;

int main() {
	freopen("f.in", "w", stdout);

	double cl = clock();

	printf("%d\n", cases);
	int n = 100000000;

	for( int i = 0; i < 2000; i++ ) {
		printf("%d\n", n);
		n--;
		cases--;
	}
	n = 1;
	for( int i = 0; i < 5000; i++ ) {
		printf("%d\n", n);
		n++;
		cases--;
	}
	while( cases-- ) {
		int k = rand() % 100000000 + 1;
		printf("%d\n", k);
	}
	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);
	return 0;
}

