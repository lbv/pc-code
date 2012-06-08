#include <cctype>
#include <cstdio>
#include <cstring>

typedef unsigned long long u64;

#define SIZE 7

char input[SIZE + 1];
char output[SIZE + 1];

int from, to;

bool convert()
{
    u64 num = 0;

    int len = strlen(input);

    u64 fac = 1;
    int dig;

    for (int i = len - 1; i >= 0; --i) {
        dig = isdigit(input[i]) ? input[i] - '0' : input[i] - 'A' + 10;
        num += dig * fac;
        fac *= from;
    }

    if (num == 0) {
        strcpy(output, "      0");
        return true;
    }

    for (int i = 6; i >= 0; --i) {
        if (num == 0) {
            output[i] = ' ';
            continue;
        }
        dig = num % to;
        num /= to;
        output[i] = dig < 10 ? '0' + dig : 'A' + dig - 10;
    }

    return num == 0;
}

int main()
{
    while (true) {
        if (scanf("%s%d%d", input, &from, &to) != 3) break;

        if (convert())
            printf("%s\n", output);
        else
            puts("  ERROR");

    }

    return 0;
}
