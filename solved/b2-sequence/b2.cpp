#include <cstdio>
#include <cstring>


#define MAXN 100
#define MAXB 10000

#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_SUM = 2 * MAXB;


int N;

int  bs[MAXN];
bool used[MAX_SUM + 1];


bool solve()
{
    if (bs[0] < 1) return false;
    for (int i = 1; i < N; ++i)
        if (bs[i - 1] >= bs[i]) return false;

    Zero(used);

    for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j) {
            int sum = bs[i] + bs[j];
            if (used[sum]) return false;
            used[sum] = true;
        }

    return true;
}

int main()
{
    int ncase = 0;
    while (true) {
        if (scanf("%d", &N) != 1) break;
        for (int i = 0; i < N; ++i) scanf("%d", &bs[i]);

        printf("Case #%d: ", ++ncase);
        if (solve())
            puts("It is a B2-Sequence.\n");
        else
            puts("It is not a B2-Sequence.\n");
    }

    return 0;
}
