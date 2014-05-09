#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXU 1000000


int T;


void test_case()
{
	int L = rand() % (MAXU + 1);
	int U = rand() % (MAXU + 1);

	if (L > U) swap(L, U);
	printf("%d %d\n", L, U);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) test_case();

	return 0;
}
