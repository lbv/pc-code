/*
	Author       :	Jan
	Problem Name :	Binary Simulation
	Algorithm    :	BIT
	Complexity   :	O(n*log(n))
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

using namespace std;

/*
#define MAXN 100000
#define MINN 50000
#define MINQ 50000
*/
#define MAXN 20
#define MINN 10
#define MAXQ 10


int main() {
	//freopen("b.in", "w", stdout);

    srand(time(NULL));
	int cases = 9;
	printf("%d\n", cases + 1);
	while( cases-- ) {
		int n;
		while(1) {
			n = rand() % MAXN + 1;
			if( n > MINN ) break;
		}
		//if( cases % 2 == 0 ) n = 100000;
		for( int i = 0; i < n; i++ ) {
			if( rand() % 2 ) putchar('0');
			else putchar('1');
		}
		puts("");

		int q = min(MAXQ, 2*n);
		printf("%d\n", q);
		while( q-- ) {
			int i, j;
			if( rand() % 3 ) {
				i = rand() % n + 1;
				j = rand() % n + 1;
				if( i > j ) swap( i, j );
				printf("I %d %d\n", i, j);
			}
			else {
				printf("Q %d\n", rand()%n + 1);
			}
		}
	}
	puts("0");
	puts("9");
	puts("Q 1");
	puts("I 1 1");
	puts("Q 1");
	puts("I 1 1");
	puts("I 1 1");
	puts("I 1 1");
	puts("Q 1");
	puts("I 1 1");
	puts("Q 1");
	return 0;
}

