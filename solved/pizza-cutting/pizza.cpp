#include <cstdio>

typedef long long i64;

i64 N;

int main()
{
    while (true) {
        scanf("%lld", &N);
        if (N < 0) break;

        i64 pieces = (N*N + N + 2) / 2;

        printf("%lld\n", pieces);
    }

    return 0;
}
