#include <cstdio>


int N;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);
        int m = N / 2;

        int med;
        for (int i = 0; i < N; ++i)
            if (i == m)
                scanf("%d", &med);
            else
                scanf("%*d");
        printf("Case %d: %d\n", ++ncase, med);
    }

    return 0;
}
