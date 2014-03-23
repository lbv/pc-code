#include <cstdio>
#include <cstring>

typedef unsigned int u32;

int N;
u32 P;

bool is_palindrome(u32 n)
{
    char str[15];
    sprintf(str, "%u", n);

    for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j)
        if (str[i] != str[j])
            return false;
    return true;
}

u32 reverse_add(u32 n)
{
    u32 a = n;
    u32 b = 0;

    while (a != 0) {
        u32 d = a % 10;
        a /= 10;
        b = b * 10 + d;
    }

    return n + b;
}

int main()
{
    scanf("%d", &N);

    while (N--) {
        scanf("%u", &P);

        int steps = 0;
        while (! is_palindrome(P)) {
            P = reverse_add(P);
            ++steps;
        }

        printf("%d %u\n", steps, P);
    }

    return 0;
}
