#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 1000

int N;
int fruit[2][MAXN];
int stairs[2][MAXN-1];

// dp[i][j] has the minimum time required to eat fruit up to floor j, at
// tower i
int dp[2][MAXN];

void run_dp()
{
    dp[0][0] = fruit[0][0];
    dp[1][0] = fruit[1][0];

    for (int i = 1; i <= N; i++) {
        dp[0][i] = min(dp[0][i-1], dp[1][i-1] + stairs[1][i-1]) + fruit[0][i];
        dp[1][i] = min(dp[1][i-1], dp[0][i-1] + stairs[0][i-1]) + fruit[1][i];
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) scanf("%d", &fruit[0][i]);
        for (int i = 0; i < N; i++) scanf("%d", &fruit[1][i]);
        for (int i = 0, I = N-1; i < I; i++) scanf("%d", &stairs[0][i]);
        for (int i = 0, I = N-1; i < I; i++) scanf("%d", &stairs[1][i]);

        run_dp();

        printf("Case %d: %d\n", ncase++, min(dp[0][N-1], dp[1][N-1]));
    }

    return 0;
}
