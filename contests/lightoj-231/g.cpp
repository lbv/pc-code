#include <cstdio>


int A, B;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &A, &B);
        printf("Case %d: ", ++ncase);

        if (A > B && A % 13 == 0)
            puts("First One");
        else if (B > A && B % 13 == 0)
            puts("Second One");
        else
            puts("Confused");
    }

    return 0;
}
