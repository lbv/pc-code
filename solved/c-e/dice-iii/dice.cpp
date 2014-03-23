#include <cstdio>


#define MAXN 100000


double H[MAXN + 1];
int n;


void prepare()
{
    H[1] = 1.0;

    for (int i = 2; i <= MAXN; ++i)
        H[i] = H[i - 1] + 1.0/i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        printf("Case %d: %.8lf\n", ++ncase, H[n]*n);
    }

    return 0;
}
