#include <cstdio>

int P, N, n, m;

int R(int n, int m)
{
    return (n-m)*m+1;
}

int main(void)
{
    scanf("%d", &P);

    while (P--) {
        scanf("%d%d%d", &N, &n, &m);
        printf("%d %d\n", N, R(n, m));
    }

    return 0;
}
