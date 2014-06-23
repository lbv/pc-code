#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXLEN 20
#define NCRIT 5


int T;
const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
const int nalpha = sizeof(alpha) / sizeof(char) - 1;
char aux[128];


void gen(bool crit = false)
{
	int len = crit ? MAXLEN : rand() % MAXLEN + 1;
	int n = crit ? nalpha : rand() % nalpha + 1;

	strncpy(aux, alpha, nalpha);
	random_shuffle(aux, aux + nalpha);

	for (int i = 0; i < len; ++i) putchar(aux[rand() % n]);
	putchar('\n');

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
