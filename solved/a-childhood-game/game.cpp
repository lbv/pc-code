#include <cstdio>

char player[8];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d%s", &n, player);
        
        if ((player[0] == 'B' && n % 3 == 0) ||
            (player[0] == 'A' && (n-1) % 3 != 0))
            printf("Case %d: Alice\n", ++ncase);
        else
            printf("Case %d: Bob\n", ++ncase);
    }

    return 0;
}
