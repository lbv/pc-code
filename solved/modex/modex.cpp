#include <cstdio>


typedef long long i64;


int x, y, n;


int mod_pow(int _b, i64 e, int m) {
    i64 res = 1;
    for (i64 b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}

int main()
{
    int c;
    scanf("%d", &c);

    while (c--) {
        scanf("%d%d%d", &x, &y, &n);
        printf("%d\n", mod_pow(x, y, n));
    }

    return 0;
}
