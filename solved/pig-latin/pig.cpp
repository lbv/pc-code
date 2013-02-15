#include <cctype>
#include <cstdio>


const int BUFSIZE = 1 << 20;


char line[BUFSIZE];


bool is_vowel(char p)
{
    p = toupper(p);
    return p == 'A' || p == 'E' || p == 'I' || p == 'O' || p == 'U';
}

void solve()
{
    for (char *p = line; *p;) {
        while (*p && ! isalpha(*p)) putchar(*p++);

        if (! *p) continue;

        char first = 0;
        if (! is_vowel(*p)) first = *p++;

        while (*p && isalpha(*p))
            putchar(*p++);
        if (first != 0) putchar(first);

        printf("ay");
    }
    putchar('\n');
}

int main()
{
    while (gets(line) != NULL) {
        solve();
    }

    return 0;
}
