#include <cstdio>

#define MAXN 50

int n;
int hs[MAXN];

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &hs[i]);
            sum += hs[i];
        }

        int moves = 0;
        int avg = sum / n;

        for (int i = 0; i < n; ++i)
            if (hs[i] > avg)
                moves += hs[i] - avg;

        printf("Set #%d\n"
               "The minimum number of moves is %d.\n\n", ++ncase, moves);
    }

    return 0;
}
