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

typedef long long i64;

#define PrimeLIMIT 10000010
#define MAX_TOTAL 665000

unsigned int prime[PrimeLIMIT / 64], pr[MAX_TOTAL], prlen;
#define gP(n) (prime[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (prime[n>>6]&=~(1<<((n>>1)&31)))
void sieve() {
	unsigned int i,j,sqrtN,i2;
	memset( prime, -1, sizeof( prime ) );
	sqrtN = ( unsigned int ) sqrt ( ( double ) PrimeLIMIT ) + 1;
	for( i = 3; i < sqrtN; i += 2 ) if( gP( i ) )
		for( j = i * i, i2 = i << 1; j < PrimeLIMIT; j += i2 ) rP( j );
	pr[prlen++] = 2;
	for( i = 3; i < PrimeLIMIT; i += 2 ) if( gP( i ) ) pr[prlen++] = i;
}

int cases, caseno;
i64 n;

i64 LIM = 100000000000000LL;

int main() {
	freopen("a.in", "w", stdout);

	double cl = clock();

	sieve();
	int cases = 200;
	printf("%d\n", cases);

	for( int i = 0; i < 50; i++ ) {
		printf("%lld\n", LIM - i);
		cases--;
	}
	for( int i = 0; i < 50; i++ ) {
		printf("%d\n", i + 1);
		cases--;
	}

	while( cases-- ) {
		i64 n = 1;

		int it = rand() % 100 + 1;

		while( it-- ) {
			i64 x;
			if( cases % 5 <= 2 ) {
				x = pr[rand() % 100];
			}
			else {
				x = pr[rand() % prlen];
			}

			if( n > 1000000000 && x > 100000 ) continue;
			if( n * x <= LIM ) n *= x;
		}
		printf("%lld\n", n);
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

