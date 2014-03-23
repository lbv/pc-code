#include <cstdio>

typedef long long i64;

i64 A, L;

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%lld%lld", &A, &L);
        if (A < 0 && L < 0) break;

        int n = 1;
        i64 T = A;

        while (T > 1) {
            if (T % 2 == 0) T /= 2;
            else {
                T = 3*T + 1;
                if (T > L) break;
            }
            ++n;
        }

        printf("Case %d: A = %lld, limit = %lld, number of terms = %d\n",
               ++ncase, A, L, n);
    }

    return 0;
}
