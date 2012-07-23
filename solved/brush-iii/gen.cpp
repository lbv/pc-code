/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
	Complexity   :
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

int cases;

int main() {
	//freopen("dd.in", "w", stdout);

	cases = 99;
	srand(time(NULL));
	printf("%d\n", cases);
	while( cases-- ) {
		//int n = 100 - rand() % 10;
		int n = rand() % 10 + 1;
		int w = rand() % 10000 + 1;
		int k = rand() % 100 + 1;

		//k = rand() % 10 + 5;
		k = rand() % 8 + 2;

		w = rand() % 10 + 10;
		int A[105];
		printf("\n%d %d %d\n", n, w, k);
		int prev = 0;
		for( int i = 0; i < n; i++ ) {
			A[i] = prev + rand() % w + 1;
			prev = A[i];
		}
		for( int i = 0; i < n; i++ ) {
			printf("0 %d\n", A[i]);
		}
	}
	return 0;
}

