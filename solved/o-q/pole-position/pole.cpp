#include <cstdio>
#include <cstring>


#define MAXN 1000

#define Zero(v) memset((v), 0, sizeof(v))


int N;
int grid[MAXN];


int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        Zero(grid);

        bool valid = true;
        for (int i = 0; i < N; ++i) {
            int C, P;
            scanf("%d%d", &C, &P);

            int idx = i + P;
            if (idx < 0 || idx >= N || grid[idx] != 0) {
                valid = false;
                continue;
            }

            grid[idx] = C;
        }

        if (valid) {
            printf("%d", grid[0]);
            for (int i = 1; i < N; ++i)
                printf(" %d", grid[i]);
            putchar('\n');
        }
        else
            puts("-1");
    }

    return 0;
}
