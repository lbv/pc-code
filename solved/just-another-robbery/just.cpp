#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 100
#define MAXM 10000

// dp[i][j] will contain the minimum probability of getting caught gathering i
// millions from j banks
double dp[MAXM + 1][MAXN + 1];

// ms[i] is the amount of millions at bank i
int ms[MAXN];

// ps[i] is the probability of getting caught at bank i
double ps[MAXN];

double P;
int N;
int TM;   // total of millions from all banks
int sol;

void init()
{
    for (int i = 0; i <= TM; ++i)
        for (int j = 0; j <= N; ++j)
            dp[i][j] = 1.0;
    dp[0][0] = 0.0;
}

void run_dp()
{
    double prev, newp;

    for (int k = 0; k < N; ++k)
        for (int j = k + 1; j >= k + 1; --j)
            for (int i = 0; i <= TM; ++i) {
                prev = dp[i][j - 1];
                dp[i][j] = min(dp[i][j], prev);

                if (i - ms[k] < 0) continue;

                prev = dp[i - ms[k]][j - 1];
                newp = prev + (1.0 - prev) * ps[k];

                dp[i][j] = min(dp[i][j], newp);
            }

    sol = 0;
    for (int i = 1; i <= TM; ++i)
        if (dp[i][N] < P) sol = i;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while(T--) {
        scanf("%lf%d", &P, &N);

        TM = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d%lf", &ms[i], &ps[i]);
            TM += ms[i];
        }

        init();
        run_dp();

        printf("Case %d: %d\n", ++ncase, sol);
    }

    return 0;
}
