#include <cstdio>
#include <cstring>

#define MAXN 1000

#define Zero(v) memset(v, 0, sizeof(v))

// dp[i][j] will have the truth value of whether a pile with i stones, and
// the chance to take at most j is a winner position
bool dp[MAXN + 1][MAXN + 1];
int n;

void run_dp()
{
    for (int i = 1; i <= MAXN; ++i)
        for (int j = 1; j <= i; ++j) {
            bool win = false;
            for (int k = 1; k <= j; ++k) {
                int top = k * 2;
                if (top >= i-k) break;
                if (! dp[i - k][top]) {
                    win = true;
                    break;
                }
            }
            dp[i][j] = win;
        }
}

int main()
{
    run_dp();

    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        printf("%s\n", dp[n][n-1] ? "Alicia" : "Roberto");
    }

    return 0;
}
