#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100
#define MAXP 10000

const int MAXDP = 2*MAXP;

#define Neg(v)  memset((v), -1, sizeof(v))


int P;  // price to make
int n;
int coins[MAXN];

// dp[i]: minimum number of coins to make i
int dp[MAXDP + 1];


int solve()
{
    Neg(dp);
    dp[0] = 0;

    int top = MAXDP;
    for (int i = 0; i < n; ++i) {
        int a = top - coins[i], b = top;

        for (; a >= 0; --a, --b)
            if (dp[a] >= 0) {
                dp[b] = dp[b] < 0 ? dp[a] + 1 : min(dp[b], dp[a] + 1);
                if (b >= P) top = b;
            }
    }
    return top;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &P, &n);
        for (int i = 0; i < n; ++i) scanf("%d", &coins[i]);

        int money = solve();
        printf("%d %d\n", money, dp[money]);
    }

    return 0;
}
