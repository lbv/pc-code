#include <cstdio>

typedef long long i64;

int B, P, M;

int mod_pow(int _b, i64 e, int m) {
    i64 res = 1;
    for (i64 b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}

int main()
{
    while (true) {
        if (scanf("%d%d%d", &B, &M, &P) != 3) break;

        printf("%d\n", mod_pow(B, M, P));
    }

    return 0;
}
