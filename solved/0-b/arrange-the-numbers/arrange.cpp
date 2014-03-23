#include <cstdio>

typedef long long i64;

#define MAXN 1000
#define MOD  1000000007

#define Sc(t,v) static_cast<t>(v)

namespace Num {
    // Binomial coefficients
#define BCSIZE MAXN
    int bc[BCSIZE + 1][BCSIZE + 1];
    void chooseTable() {
        for (int n = 1; n <= BCSIZE; n++) { bc[n][n] = 1; bc[n][1] = n; }
        for (int n = 3; n <= BCSIZE; n++)
            for (int k = 2; k < n; k++)
                bc[n][k] = (bc[n-1][k-1] + bc[n-1][k]) % MOD;
    }
}
using namespace Num;

// factseg[i][j] has ((i)*(i+1)*..*(j)) % MOD
int factseg[MAXN + 1][MAXN + 1];
int N, M, K;

void prepare()
{
    chooseTable();
    for (int i = 1; i <= MAXN; i++) {
        i64 f = i;
        factseg[i][i] = i;
        for (int j = i+1; j <= MAXN; j++) {
            f = (f*j) % MOD;
            factseg[i][j] = f;
        }
    }
    factseg[1][0] = 1;  // 0! = 1
}

int chooseDerangement()
{
    // Base case
    if (M == K) return 1;

    int R = M - K;
    int f1 = N - M + 1;
    int f2 = N - K;
    i64 der = factseg[f1][f2];
    int sgn = -1;
    for (int i = 1; i < R; i++) {
        i64 tmp = Sc(i64, bc[R][i]) * factseg[f1][f2-i] % MOD;
        der = (der + sgn*tmp) % MOD;
        sgn = -sgn;
    }
    der = (der + sgn) % MOD;
    return der;
}

int solve()
{
    // Base case
    if (N == K) return 1;

    i64 ans;

    // The calculation is based on three factors:

    // (1) The number of ways K numbers can be chosen (the ones that will
    // stay in their place)
    ans = K == 0 ? 1 : bc[M][K];  // conditional used for the UVa judge

    // (2) The number of ways M-K numbers can be chosen (the ones that are
    // in the first M, but will not be in their place)
    int der = chooseDerangement();
    ans = ans * der % MOD;
    if (ans < 0) ans += MOD;

    // (3) The number of ways the rest (N-M) of the numbers con be chosen
    ans = ans * factseg[1][N-M] % MOD;

    return ans;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d%d%d", &N, &M, &K);
        printf("Case %d: %d\n", ncase++, solve());
    }

    return 0;
}
