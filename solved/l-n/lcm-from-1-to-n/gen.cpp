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

#define PrimeLIMIT 100000000
#define MAX_TOTAL 5800000
unsigned int prime[PrimeLIMIT / 64], prlen;
#define gP(n) (prime[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (prime[n>>6]&=~(1<<((n>>1)&31)))

typedef long long i64;

pair <int, int> pr[MAX_TOTAL];

void addPowers( int k ) {
	i64 res = k;
	while( res <= PrimeLIMIT ) {
		pr[prlen].first = res;
		pr[prlen++].second = k;
		res *= k;
	}
}

unsigned save[1000001];

void sieve() {
	unsigned int i,j,sqrtN,i2;
	memset( prime, -1, sizeof( prime ) );
	sqrtN = ( unsigned int ) sqrt ( ( double ) PrimeLIMIT ) + 1;
	for( i = 3; i < sqrtN; i += 2 ) if( gP( i ) )
		for( j = i * i, i2 = i << 1; j < PrimeLIMIT; j += i2 ) rP( j );
	addPowers(2);
	for( i = 3; i < PrimeLIMIT; i += 2 ) if( gP( i ) ) addPowers(i);

	sort( pr, pr + prlen );

	for( i = 0; i < 1000001; i++ ) save[i] = 1;
	for( i = 0; i < prlen; i++ ) {
		int p = (pr[i].first - 1) / 100 + 1;
		save[p] *= pr[i].second;
	}
}

int cases, caseno, n;

int main() {
	// freopen("lcm.in", "w", stdout);

	double cl = clock();

	sieve();

	int cases = 10000;
	printf("%d\n", cases);

	for( int i = 2; i <= 500; i++ ) {
		printf("%d\n", i);
		cases--;
	}

	for( int i = 100000000, k = 0; k < 1000; i--, k++ ) {
		printf("%d\n", i);
		cases--;
	}

	while( cases-- ) {
		if( rand() % 3 ) printf("%d\n", pr[rand() % prlen].first);
		else {
			int n = rand() % 10000000 + 2;
			if( rand() % 3 ) n = 100000000 - rand() % 1000000;
			printf("%d\n", n);
		}
	}

	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);

	return 0;
}

