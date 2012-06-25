#include <cctype>
#include <cstdio>
#include <cstring>

#define MAXBASE 16
#define MAXK 20

#define Zero(v) memset(v, 0, sizeof(v))

typedef long long i64;
typedef unsigned int u32;

// dp[i][j] contains the number of permutations using the digits from the
// bitmask i, such P modulo K = j, where P is the permutation number
i64 dp[1 << MAXBASE][MAXK];

int base, K;
int D;  // number of digits in the number
char num[MAXBASE + 1];

int ds[MAXBASE];  // digits in the number as integers
int pos[1 << MAXBASE];

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}

u32 init_popcount(int n) { return (1 << n) - 1; }

void run_dp()
{
    for (int i = 0; i < D; ++i) {
        if (isdigit(num[i]))
            ds[i] = num[i] - '0';
        else
            ds[i] = num[i] - 'A' + 10;
    }

    Zero(dp);
    u32 top = 1 << D;
    int rem;
    u32 b;

    for (b = 1; b < top; b <<= 1) {
        rem = ds[pos[b]] % K;
        dp[b][rem] = 1;
    }

    int baserem = 1;
    for (int i = 2; i <= D; ++i) {
        baserem = baserem * base % K;
        for (b = init_popcount(i); b < top; b = next_popcount(b)) {
            u32 x = b;
            while (x != 0) {
                u32 cur = x & -x;  // bit of the current digit
                u32 rest = b & ~cur;  // bitmask for all digits except cur

                rem = ds[pos[cur]] * baserem % K;
                for (int j = 0; j < K; ++j)
                    dp[b][(rem + j) % K] += dp[rest][j];

                x &= ~cur;
            }
        }
    }
}

void prepare()
{
    for (int i = 0; i < MAXBASE; ++i)
        pos[1 << i] = i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%s", &base, &K, num);
        D = strlen(num);

        run_dp();

        printf("Case %d: %lld\n", ++ncase, dp[(1 << D) - 1][0]);
    }

    return 0;
}
