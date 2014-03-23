#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n;
        scanf("%d", &n);
        bool steven = true;
        while (n != 0) {
            if (n & 1) steven = !steven;
            n >>= 1;
        }
        if (steven)
            printf("Case %d: even\n", ncase++);
        else
            printf("Case %d: odd\n", ncase++);
    }

    return 0;
}
