#include <cstdio>


#define MAXN 100


int N;
int f[MAXN + 1];


void prepare()
{
    for (int i = 1; i <= MAXN; ++i)
        f[i] = f[i - 1] + i*i;
}

int main()
{
    prepare();

    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        printf("%d\n", f[N]);
    }

    return 0;
}
