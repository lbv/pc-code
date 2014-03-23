#include <cstdio>

#define MAXN 1000

int N;
int ns[MAXN];

int main()
{
    int C;
    scanf("%d", &C);

    while (C--) {
        scanf("%d", &N);

        double sum = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &ns[i]);
            sum += ns[i];
        }
        double avg = sum / N;

        int above = 0;
        for (int i = 0; i < N; ++i)
            if (ns[i] > avg)
                ++above;

        printf("%.3lf%%\n", 100.0 * above / N);
    }

    return 0;
}
