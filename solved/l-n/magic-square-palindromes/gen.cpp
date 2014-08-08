#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#if 0
#define MAXT 60
#define MAXL 10000
#define NCRIT 5
#endif

#if 1
#define MAXT 20
#define MAXL 20
#define NCRIT 3
#endif

#define Clr(m) memset(m, 0, sizeof(m))

const int MAXSIZE = sqrt(MAXL);

const char punct[] = " ,.?!()";
const int npunct = strlen(punct);

int T;

char str[MAXL + 1];
char magic[MAXSIZE][MAXSIZE];


void gen(bool crit = false)
{
	int len = crit ? MAXL : rand() % MAXL + 1;
	int paln = sqrt(rand() % len + 1);
	int pals = paln * paln;
	int noise = len - pals;

	Clr(str);

	while (noise--) {
		int i;
		do {
			i = rand() % len;
		} while (str[i] != 0);
		str[i] = punct[rand() % npunct];
	}

	for (int i = 0; i < paln; ++i)
		for (int j = 0; j < paln; ++j) {
			magic[i][j] = 'a' + (rand() % 26);
			int r, c;
			r = paln - 1 - i;
			c = paln - 1 - j;
			magic[r][c] = magic[i][j];

			r = j;
			c = i;
			magic[r][c] = magic[i][j];

			r = paln - 1 - j;
			c = paln - 1 - i;
			magic[r][c] = magic[i][j];
		}

	int x = 0;
	for (int i = 0; i < paln; ++i)
		for (int j = 0; j < paln; ++j) {
			while (str[x] != 0) ++x;
			str[x] = magic[i][j];
		}

	if (rand() % 3 == 0) {
		int garbage = rand() % (len + 1);
		while (garbage--) {
			int x = rand() % len;
			str[x] = 'a' + (rand() % 26);
		}
	}
	puts(str);

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
