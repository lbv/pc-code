#include <cstdio>


#define MAXN 1000000


typedef long long i64;


i64 aux[MAXN + 1];
i64 tri[MAXN + 1];
int n;


void prepare()
{
    int inc = 0;
    for (int i = 4; i <= MAXN; ++i) {
        if (i % 2 == 0) ++inc;
        aux[i] = aux[i - 1] + inc;
        tri[i] = tri[i - 1] + aux[i];
    }
}

int main()
{
    prepare();
    while (true) {
        scanf("%d", &n);
        if (n < 3) break;
        printf("%lld\n", tri[n]);
    }

    return 0;
}
