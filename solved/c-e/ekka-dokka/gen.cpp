#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
	//freopen("g.in", "w", stdout);
	int cases = 9990;

	printf("%d\n", cases + 1);
	puts("9223372036854775804");
	while( cases-- ) {
		long long k;

		while( true ) {
			k = rand() * rand();
			if( rand() % 4 == 0 ) k = (1LL << 62) - k;
			if( rand() % 100 == 0 ) k = 1LL << (rand() % 63);
			if( rand() % 50 == 0 ) k = rand() % 100;

			if( k > 1 ) {
				long long x = k;
				while( x % 2 == 0 ) x /= 2;
				if( x == 1 ) continue;
				break;
			}
		}
		if( k == 64 ) {
			puts("why");
			while(1);
		}
		cout << k << endl;
	}
	return 0;
}

