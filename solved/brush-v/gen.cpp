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
	//freopen("ee.in", "w", stdout);
    srand(time(NULL));

	cases = 100;
	printf("%d\n", cases);
	while( cases-- ) {
		int n = rand() % 5 + 2;
		int m = rand() % 20;

		printf("\n%d %d\n", n, m);
		while( m-- ) {
			int u, v, w;

			while(1) {
				u = rand() % n + 1;
				v = rand() % n + 1;
				if( u != v ) break;
			}
			w = rand() % 1000 + 1;
			printf("%d %d %d\n", u, v, w);
		}
	}
	return 0;
}

