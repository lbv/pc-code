#include <cstdio>


int m, n;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &m, &n);
        int nim = 0;
        for (int i = 0; i < m; ++i) {
            int row = 0, stones;
            for (int j = 0; j < n; ++j) {
                scanf("%d", &stones);
                row += stones;
            }

            nim ^= row;
        }

        printf("Case %d: ", ++ncase);
        if (nim != 0) puts("Alice");
        else puts("Bob");
    }

    return 0;
}
