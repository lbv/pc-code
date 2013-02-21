#include <cctype>
#include <cstdio>
#include <cstring>


char buf[1024];
int len;


void hex_to_dec()
{
    int n = 0, f16 = 1;
    for (int i = len - 1; i > 1; --i) {
        int dig;
        char &c = buf[i];

        if (isdigit(c)) dig = c - '0';
        else if (isupper(c)) dig = c - 'A' + 10;
        else dig = c - 'a' + 10;

        n += dig * f16;
        f16 *= 16;
    }
    printf("%d\n", n);
}

void dec_to_hex()
{
    int n = 0, f10 = 1;
    for (int i = len - 1; i >= 0; --i) {
        n += (buf[i] - '0') * f10;
        f10 *= 10;
    }
    printf("0x%X\n", n);
}

int main()
{
    while (true) {
        scanf("%s", buf);
        len = strlen(buf);

        if (len > 0 && buf[0] == '-') break;
        if (len >= 2 && buf[1] == 'x') hex_to_dec();
        else dec_to_hex();
    }

    return 0;
}
