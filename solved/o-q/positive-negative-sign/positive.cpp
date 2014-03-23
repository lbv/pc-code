#include <cstdio>

typedef long long i64;

i64 n, m;

int main(void)
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%lld%lld", &n, &m);
        
        printf("Case %d: %lld\n", ncase++, n*m/2);
    }
}
