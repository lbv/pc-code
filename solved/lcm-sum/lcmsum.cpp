#include <cstdio>

typedef long long i64;

#define MAXN 1000000
#define SC(t,v) static_cast<t>(v)

namespace Num {
    void eulerPhi(int a[], int N) {
        for (int i = 1; i <= N; i++) a[i] = i;
        for (int i = 2; i <= N; i += 2) a[i] = i/2;
        for (int i = 3; i <= N; i += 2)
            if (a[i] == i) {
                a[i]--;
                for (int j = i+i; j <= N; j += i) a[j] -= a[j]/i;
            }
    }
}

void calcSum(i64 a[], int N, int phi[])
{
    for (int i = 1; i <= N; i++) a[i] = 1;
    for (int i = 2; i <= N; i++)
        for (int j = i; j <= N; j += i)
            a[j] += SC(i64,i) * phi[i];
}

int phi[MAXN + 1];

// sum[i] has Sum_{d|i}{d*phi(d)}
i64 sum[MAXN + 1];

int main()
{
    Num::eulerPhi(phi, MAXN);
    calcSum(sum, MAXN, phi);

    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", (sum[n]+1) / 2 * n);
    }

    return 0;
}
