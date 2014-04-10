#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXT 100

#define Clr(m) memset(m, 0, sizeof(m))


int T;
bool used[13][4];

const char ranks[] = "A23456789TJQK";
const char suits[] = "SHDC";


void test_case()
{
	Clr(used);

	for (int i = 0; i < 13; ++i) {
		if (i > 0) putchar(' ');

		int r, s;
		do {
			r = rand() % 13;
			s = rand() % 4;
		} while (used[r][s]);
		used[r][s] = true;

		printf("%c%c", ranks[r], suits[s]);
	}
	puts("");

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) test_case();

	return 0;
}
