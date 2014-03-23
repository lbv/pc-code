#include <cmath>
#include <cstdio>


#define EPS (1e-8)


int n, m;


int ipow(int b, int e) {
    int res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}

bool solve()
{
    if (n <= 1 || m <= 1) return false;

    int exp = log(n) / log(m) + EPS;

    int p = ipow(m, exp);
    if (p != n) return false;

    printf("%d", n);

    while (n != 1) {
        n /= m;
        printf(" %d", n);
    }
    putchar('\n');
    return true;
}

int main()
{
    while (true) {
        if (scanf("%d%d", &n, &m) != 2) break;

        if (! solve())
            puts("Boring!");
    }

    return 0;
}
