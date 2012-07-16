#include <cstdio>
#include <cstring>

typedef long long i64;

#define MAXS 60
#define Zero(v) memset(v, 0, sizeof(v))

char str[MAXS + 5];
int len;

// dp[i][j] has the number of palindromic subsequences starting at i, and
// ending at j
i64 dp[MAXS][MAXS];

void run_dp()
{
    Zero(dp);
    for (int i = 0; i < len; i++) dp[i][i] = 1;
    for (int w = 2; w <= len; w++)
        for (int i = 0, j = i+w-1; j < len; i++, j++) {
            dp[i][j] = dp[i+1][j] - dp[i+1][j-1] + dp[i][j-1];
            if (str[i] == str[j])
                dp[i][j] += 1 + dp[i+1][j-1];
        }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%s", str);
        len = strlen(str);
        run_dp();
        printf("Case %d: %lld\n", ncase++, dp[0][len-1]);
    }

    return 0;
}
