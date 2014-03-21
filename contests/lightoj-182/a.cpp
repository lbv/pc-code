#include <cstdio>
#include <cstring>

#define MAXLEN 10000
#define MOD 1000003

char num[MAXLEN + 1];
int B;
int ans;

void solve()
{
    ans = 0;
    int p = 1;
    for (int i = strlen(num) - 1; i >= 0; --i) {
        ans += (num[i] - '0') * p;
        p *= B;

        ans %= MOD;
        p %= MOD;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%s", &B, num);
        solve();
        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
