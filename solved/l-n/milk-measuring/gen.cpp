#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXQ 20000
#define MAXP 100

#define MAXPV 10000


bool used[MAXPV+1];
int ps[MAXP];


int main()
{
	srand(time(NULL));

	int P = rand() % MAXP + 1;
	for (int i = 0; i < P; ++i) {
		int v;
		do {
			v = rand() % MAXPV + 1;
		} while (used[v]);
		used[v] = true;
		ps[i] = v;
	}

	int Q = ps[0];
	int iter = rand() % 100;
	while (iter--) {
		int x = rand() % P;
		if (Q + ps[x] <= MAXQ)
			Q += ps[x];
	}

	printf("%d\n%d\n", Q, P);
	for (int i = 0; i < P; ++i) printf("%d\n", ps[i]);

	return 0;
}
