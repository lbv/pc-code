#include <cstdio>
#include <cstring>

#define MAXLEN 35

typedef unsigned int u32;

char num[MAXLEN + 1];

u32 convert()
{
    u32 ans = 0;
    u32 p = 1 << 1;

    for (int i = strlen(num) - 1; i >= 0; --i) {
        ans += (num[i] - '0') * (p - 1);
        p <<= 1;
    }

    return ans;
}

int main()
{
    while (true) {
        scanf("%s", num);
        if (strcmp("0", num) == 0) break;

        printf("%u\n", convert());
    }

    return 0;
}
