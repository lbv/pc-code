#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXA 100
#define MAXB 100
#define MAXC 300
#define NCRIT 5


int T;

char A[MAXA + 1];
char B[MAXB + 1];
char C[MAXC + 1];

int idx[MAXC + 1];


void fill(char *s, int len, int alpha)
{
	for (int i = 0; i < len; ++i)
		s[i] = 'a' + (rand() % alpha);
	s[len] = 0;
}

void gen_rand()
{
	int alpha = rand() % 26 + 1;
	fill(A, rand() % MAXA + 1, alpha);
	fill(B, rand() % MAXB + 1, alpha);
	fill(C, rand() % MAXC + 1, alpha);
	puts(A);
	puts(B);
	puts(C);

	--T;
}

void gen(bool crit = false)
{
	int c = crit ? MAXC : rand() % MAXC + 1;
	int alpha = crit ? 26 : rand() % 26 + 1;
	fill(C, c, alpha);

	int a = crit ? MAXA : rand() % min(MAXA, c) + 1;
	int b = crit ? MAXB : rand() % min(MAXB, c) + 1;

	for (int i = 0; i < c; ++i) idx[i] = i;

	random_shuffle(idx, idx + c);
	sort(idx, idx + a);
	for (int i = 0; i < a; ++i) A[i] = C[idx[i]];
	A[a] = 0;

	random_shuffle(idx, idx + c);
	sort(idx, idx + b);
	for (int i = 0; i < b; ++i) B[i] = C[idx[i]];
	B[b] = 0;

	puts(A);
	puts(B);
	puts(C);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) {
		int r = rand() % 10;
		if (r < 4)
			gen_rand();
		else
			gen();
	}

	return 0;
}
