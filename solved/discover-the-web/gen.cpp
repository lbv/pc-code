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

int cases = 300;

void randomUrl( char *a ) {
	strcpy( a, "http://jan.debashis.net/lightoj/jaks/" );
	int k = rand() % 100;
	int len = strlen(a);

	while( k-- ) {
		int i = rand() % len;
		if( i > 5 && a[i] != '/' ) {
			a[i] = rand() % 26 + 97;
		}
	}
}

int main() {
	freopen("d.in", "w", stdout);

	double cl = clock();

    srand(13);
	printf("%d\n", cases);
	while( cases-- ) {
		int len = rand() % 98 + 1;
		while( len-- ) {
			int k = rand() % 3;
			if( !k ) puts("BACK");
			else if( k == 1 ) puts("FORWARD");
			else {
				char a[100];
				randomUrl(a);
				printf("VISIT %s\n", a);
			}
		}
		puts("QUIT");
	}
	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);
	return 0;
}

