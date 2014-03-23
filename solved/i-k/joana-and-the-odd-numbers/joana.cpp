#include <cstdio>


typedef long long i64;


i64 n;


int main()
{
    while (true) {
        if (scanf("%lld", &n) != 1) break;

        i64 l = n + (n - 1) * ((n - 1) / 2 + 1);
        printf("%lld\n", 3*l - 6);
    }

    return 0;
}
