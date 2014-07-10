#include <cstdio>


int N, M;

const char dirs[4] = { 'R', 'D', 'L', 'U' };


char solve()
{
	int r = N-1, c = M;

	int m;
	if (c <= r) m = (c*2-1) % 4;
	else m = (r*2) % 4;

	return dirs[m];
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		printf("%c\n", solve());
	}

	return 0;
}
