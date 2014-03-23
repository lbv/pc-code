#include <cstdio>


int M, N;


int main()
{
    while (true) {
        if (scanf("%d%d", &M, &N) != 2) break;
        printf("%d\n", M*N - 1);
    }

    return 0;
}
