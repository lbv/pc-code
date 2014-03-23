#include <cstdio>
#include <cstring>


#define MAXR 20
#define MAXC 20

#define Zero(v) memset((v), 0, sizeof(v))


int R, C, M, N;
char grid[MAXR][MAXC + 1];
int counts[26];


int solve()
{
    Zero(counts);
    int hi = 0;
    int groups = 0;

    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j) {
            int idx = grid[i][j] - 'A';

            ++counts[idx];
            if (counts[idx] > hi) {
                hi = counts[idx];
                groups = 1;
            }
            else if (counts[idx] == hi) {
                ++groups;
            }
        }

    int lo = R*C - hi*groups;
    return hi * groups * M + lo * N;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d", &R, &C, &M, &N);
        for (int i = 0; i < R; ++i) scanf("%s", grid[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
