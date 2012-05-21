#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        int sz   = 2;
        int lies = 0;
        int a;

        while (n--) {
            scanf("%d", &a);
            if (a == sz) continue;
            lies += (a-sz+4) / 5;
            sz = a;
        }

        printf("Case %d: %d\n", ++ncase, lies);
    }

    return 0;
}
