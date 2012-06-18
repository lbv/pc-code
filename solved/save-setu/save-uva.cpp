#include <cstdio>

char comm[10];

int main()
{
    int T;
    scanf("%d", &T);

    int acc = 0;
    int don;

    while (T--) {
        scanf("%s", comm);

        if (comm[0] == 'd') {
            scanf("%d", &don);
            acc += don;
        }
        else
            printf("%d\n", acc);
    }

    return 0;
}
