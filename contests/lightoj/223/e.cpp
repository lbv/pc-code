#include <cstdio>

int N;

void print_binary(int n)
{
    for (int i = N - 1; i >= 0; --i)
        putchar(n & (1 << i) ? '1' : '0');
    putchar('\n');
}

int main()
{
    while (true) {
        if (scanf("%d", &N) != 1) break;

        int top = 1 << N;
        for (int i = 0; i < top; ++i)
            print_binary(i);
    }

    return 0;
}
