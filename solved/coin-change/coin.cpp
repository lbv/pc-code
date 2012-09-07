#include <cstdio>


#define MAXMONEY 7489


// dp[i] has the number of ways to make i with the coins
int dp[MAXMONEY + 1];

int x;

const int coins[] = { 50, 25, 10, 5, 1 };

void run_dp()
{
    dp[0] = 1;
    int n = sizeof(coins) / sizeof(int);

    for (int i = 0; i < n; ++i)
        for (int j = coins[i], a = 0; j <= MAXMONEY; ++j, ++a)
            dp[j] += dp[a];
}

int main()
{
    run_dp();

    while (true) {
        if (scanf("%d", &x) != 1) break;

        printf("%d\n", dp[x]);
    }

    return 0;
}
