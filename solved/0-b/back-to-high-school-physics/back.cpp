#include <cstdio>

int v, t;

int main()
{
    while (true) {
        if (scanf("%d%d", &v, &t) != 2) break;
        printf("%d\n", v*2*t);
    }

    return 0;
}
