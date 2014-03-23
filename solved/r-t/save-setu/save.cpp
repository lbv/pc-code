#include <cstdio>

char comm[10];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N;
        scanf("%d", &N);

        int acc = 0;
        int don;

        printf("Case %d:\n", ++ncase);
        while (N--) {
            scanf("%s", comm);

            if (comm[0] == 'd') {
                scanf("%d", &don);
                acc += don;
            }
            else
                printf("%d\n", acc);
        }
    }

    return 0;
}
