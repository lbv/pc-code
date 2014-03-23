#include <cstdio>
#include <cstring>


#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


int n;
int rows[MAXN];
int cols[MAXN];


int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        Zero(rows);
        Zero(cols);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int bit;
                scanf("%d", &bit);
                rows[i] += bit;
                cols[j] += bit;
            }

        // number of "wrong" rows and cols
        int wr = 0;
        int wc = 0;
        int row, col;

        for (int i = 0; i < n; ++i) {
            if (rows[i] % 2 != 0) {
                ++wr;
                row = i;
            }
            if (cols[i] % 2 != 0) {
                ++wc;
                col = i;
            }
        }

        if (wr == 0 && wc == 0)
            puts("OK");
        else if (wr == 1 && wc == 1)
            printf("Change bit (%d,%d)\n", row + 1, col + 1);
        else
            puts("Corrupt");
    }

    return 0;
}
