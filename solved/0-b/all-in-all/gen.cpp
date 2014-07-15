#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100
#define MAXLEN 1023
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXLEN 20
#define NCRIT 3
#endif


#define Clr(m) memset(m, 0, sizeof(m))


const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int nalpha = strlen(alphabet);


int T;
char s1[MAXLEN + 1], s2[MAXLEN + 1];
int idx[MAXLEN];
bool used[MAXLEN];


void fill_random(char *s, int n, int na)
{
	for (int i = 0; i < n; ++i)
		s[i] = alphabet[rand() % na];
	s[n] = 0;
}

void gen(bool crit = false)
{
	int na = crit ? nalpha : rand() % nalpha + 1;
	int len1 = crit ? MAXLEN : rand() % MAXLEN + 1;
	int len2 = crit ? MAXLEN : rand() % MAXLEN + 1;

	fill_random(s1, len1, na);
	fill_random(s2, len2, na);

	printf("%s %s\n", s1, s2);

	--T;
}

void gen_good(bool crit = false)
{
	int na = crit ? nalpha : rand() % nalpha + 1;
	int len2 = crit ? MAXLEN : rand() % MAXLEN + 1;
	int len1 = rand() % len2 + 1;

	fill_random(s2, len2, na);

	Clr(used);
	for (int i = 0; i < len1; ++i) {
		int x;
		do {
			x = rand() % len2;
		} while (used[x]);
		used[x] = true;
		idx[i] = x;
	}
	sort(idx, idx + len1);

	for (int i = 0; i < len1; ++i)
		s1[i] = s2[idx[i]];
	s1[len1] = 0;

	printf("%s %s\n", s1, s2);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen_good(true);
	while (T)
		if (rand() % 3 == 0) gen();
		else gen_good();

	return 0;
}
