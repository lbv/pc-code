#include <cmath>
#include <cstdio>
#include <cstring>


#define MAXLEN    10  // max length of a number in the range [A:B]
#define NUMDIGITS 10  // digits 0..9
#define MAXK      90  // maximum interesting K, given the sum of digits

#define Zero(v) memset((v), 0, sizeof(v))


typedef long long i64;


// dp[i][j][m][n] has the amount of numbers X of length i, that start with the
// digit j, where (sum of digits of X) % K is m and X % K is n
int dp[MAXLEN + 1][NUMDIGITS][MAXK][MAXK];

// acc[i][m][n] is the accumulation of dp[i][j][m][n] for all digits j
int acc[MAXLEN + 1][MAXK][MAXK];

// p10[i] is 10^i
i64 p10[MAXLEN];

int A, B, K;
int len;



int mod(i64 n, int k)
{
    i64 m = n % k;
    if (m < 0) m += k;
    return m;
}

void run_dp()
{
    Zero(dp);
    Zero(acc);

    for (int d = 0; d <= 9; ++d) {
        ++dp[1][d][d % K][d % K];
        ++acc[1][d % K][d % K];
    }

    for (int i = 2; i <= len; ++i)
        for (int d = 0; d <= 9; ++d)
            for (int m = 0; m < K; ++m)
                for (int n = 0; n < K; ++n) {
                    int p = mod(m - d, K);
                    int q = mod(n - d * p10[i - 1], K);
                    dp[i][d][m][n] += acc[i - 1][p][q];
                    acc[i][m][n] += acc[i - 1][p][q];
                }
}

int number(int n)
{
    char num[MAXLEN + 1];
    sprintf(num, "%d", n);
    int lnum = strlen(num);

    int p = 0;
    int q = 0;

    int ans = 0;

    for (int i = lnum; i >= 1; --i) {
        int dig = num[lnum - i] - '0';

        for (int d = 0, D = i == 1 ? dig : dig - 1; d <= D; ++d)
            ans += dp[i][d][p][q];

        p = mod(p - dig, K);
        q = mod(q - dig * p10[i - 1], K);
    }

    return ans;
}

int solve()
{
    len = 1 + log10(B);
    if (K > len * 9) return 0;

    run_dp();
    return number(B) - number(A - 1);
}

void prepare()
{
    p10[0] = 1;
    for (int i = 1; i < MAXLEN; ++i)
        p10[i] = p10[i - 1] * 10;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d", &A, &B, &K);
        printf("%d\n", solve());
    }

    return 0;
}
