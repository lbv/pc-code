#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 20
#define MAXN 1000


int T;


void gen()
{
	int L = rand() % (MAXN + 1);
	int n = rand() % (MAXN + 1);

	double fac = (rand() % 250 + 1) / 1000.0;
	double C = fac/n;

	double dL = L * (1.0 - (rand() % 10)/100.0);
	double dn = n * (1.0 - (rand() % 10)/100.0);
	printf("%.2lf %.2lf %.5lf\n", dL, dn, C);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) gen();

	return 0;
}
