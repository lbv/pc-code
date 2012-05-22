#include <cstdio>

int main()
{
    printf("380\n");
    for (int i = 1; i <= 20; ++i)
        for (int j = 2; j <= 20; ++j)
            printf("%d %d\n", i, j);
    return 0;
}
