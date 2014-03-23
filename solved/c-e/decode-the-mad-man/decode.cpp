#include <cctype>
#include <cstdio>
#include <cstring>

char tbl[] = "qwertyuiop[]asdfghjkl;'zxcvbnm,.";

int main()
{
    while (true) {
        char c = fgetc(stdin);
        if (c == EOF) break;

        if (isupper(c)) c = tolower(c);

        char *p = strchr(tbl, c);
        if (p != NULL)
            c = *(p - 2);
        putchar(c);
    }

    return 0;
}
