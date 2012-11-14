#include <cstdio>


#define MAXK 30000


typedef long long i64;


i64 ways[MAXK + 1];
const int coins[] = { 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5 };
const int ncoins = 11;


void cc(i64 *W, const int *C, int n, int k)
{
    W[0] = 1;
    for (int i = n - 1; i >= 0; --i)
        for (int a = 0, b = C[i]; b <= k; ++a, ++b)
            W[b] += W[a];
}

int main()
{
    cc(ways, coins, ncoins, MAXK);

    while (true) {
        int d, c;
        scanf("%d.%d", &d, &c);
        if (d == 0 && c == 0) break;

        int m = d*100 + c;
        printf("%3d.%02d%17lld\n", d, c, ways[m]);
    }

    return 0;
}
