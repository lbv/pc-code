#include <cstdio>

// returns the position of the last visited in range [0, n-1]
int josephus(int n, int k)
{
    if (n == 1) return 0;
    return (josephus(n-1, k) + k) % n;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("Case %d: %d\n", ++ncase, josephus(n, k) + 1);
    }

    return 0;
}
