#include <cstdio>

int N;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        int total, dust;
        total = 0;

        while (N--) {
            scanf("%d", &dust);
            if (dust > 0) total += dust;
        }

        printf("Case %d: %d\n", ++ncase, total);
    }

    return 0;
}
