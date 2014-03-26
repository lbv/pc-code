#include <cstdio>
#include <cstring>


#define MAXLEN 10
#define MAXD 1001

#define Neg(m) memset(m, -1, sizeof(m))

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))
static const int m37pos[] = {
	32,  0,  1, 26,  2, 23, 27,  0,  3,
	16, 24, 30, 28, 11,  0, 13,  4,  7,
	17,  0, 25, 22, 31, 15, 29, 10, 12,
	 6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


typedef unsigned int u32;


int s[MAXLEN];
char str[MAXLEN + 1];
int d, len;

int memo[1 << MAXLEN][MAXD];

// rems[i][j] = i * 10^j % d
int rems[10][10];



// f(b,r,n): The number of permutations using the digits in bitmask b that
// leave remainder r when divided by d. There are n digits in b.
int f(u32 b, int r, int n)
{
	if (memo[b][r] >= 0) return memo[b][r];

	if (n == 1)
		return memo[b][r] = (s[Ctz(b)] % d == r ? 1 : 0);

	u32 used = 0;
	int res = 0;
	for (u32 x = b; x; ClrFS(x)) {
		u32 bit = GetFS(x);
		int dig = s[Ctz(bit)];

		if (used & (1 << dig)) continue;
		used |= 1 << dig;

		res += f(b & ~bit, (r - rems[dig][n-1] + d) % d, n-1);
	}
	return memo[b][r] = res;
}

int solve()
{
	len = strlen(str);
	for (int i = 0; i < len; ++i) s[i] = str[i] - '0';
	Neg(memo);

	for (int i = 0; i < 10; ++i) {
		rems[i][0] = i % d;

		for (int j = 1; j < 10; ++j)
			rems[i][j] = rems[i][j-1] * 10 % d;
	}

	return f((1 << len) - 1, 0, len);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%s%d", str, &d);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
