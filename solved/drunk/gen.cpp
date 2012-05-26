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
#include <cstring>
#include <sstream>

using namespace std;

set <string> S;
char names[30001][12];

int main() {
	freopen("d.in","w",stdout);

	for( int i = 0; i < 30000; i++ ) {
		int len = rand() % 10 + 1;
		char a[20];
		for( int j = 0; j < len; j++ ) {
			a[j] = rand() % 26 + 97;
		}
		a[len] = 0;
		S.insert(a);
	}
	set <string> ::iterator s;
	int N = 0;
	for( s = S.begin(); s != S.end(); s++ ) {
		strcpy( names[N], (*s).c_str() );
		N++;
	}

	int cases = 50;

	printf("%d\n", cases);

	while( cases-- ) {
		int n = rand() % 10000 + 1;

		if( cases % 10 == 0 ) n = 10000;
		else n = rand() % 100 + 1;

		if( n < 5 ) n = 5;

		printf("%d\n", n);
		int k  = n;
		while( n-- ) {
			int a, b;
			
			while( 1 ) {
				if( cases % 5 != 0 ) {
					a = rand() % S.size();
					b = rand() % S.size();
				}
				else {
					a = rand() % (k/2);
					b = rand() % (k/2);
				}
				if( a != b ) break;
			}
			printf("%s %s\n", names[a], names[b]);
		}
	}
	return 0;
}

