#include <cstdio>

int A, F;

void print_wave()
{
    for (int i = 0; i < F; ++i) {
        if (i > 0) puts("");

        for (int j = 1; j <= A; ++j) {
            for (int k = 1; k <= j; ++k)
                printf("%d", j);
            puts("");
        }
        for (int j = A - 1; j >= 1; --j) {
            for (int k = 1; k <= j; ++k)
                printf("%d", j);
            puts("");
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d%d", &A, &F);

        if (i > 0) puts("");
        print_wave();
    }

    return 0;
}
