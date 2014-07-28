#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXN 2000000000


int T;


void gen()
{
	int n = rand() % MAXN + 1;

	int r = rand() % 10;
	if (n >= 100 && r < 1) n = rand() % 100 + 1;
	if (n >= 10000 && r < 3) n = rand() % 10000 + 1;
	if (n >= 1000000 && r < 5) n = rand() % 1000000 + 1;
	printf("%d\n", n);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) gen();
	puts("0");

	return 0;
}
