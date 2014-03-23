#include <cctype>
#include <cstdio>


#define MAXLEN 25
#define EPS    (1e-9)


char s1[MAXLEN + 1];
char s2[MAXLEN + 1];


int get_value(const char *s)
{
    int v = 0;
    for (; *s; ++s) {
        if (!isalpha(*s)) continue;
        v += toupper(*s) - 'A' + 1;
    }

    while (v >= 10) {
        int x = 0;
        while (v) {
            x += v % 10;
            v /= 10;
        }
        v = x;
    }
    return v;
}

double solve()
{
    int v1 = get_value(s1);
    int v2 = get_value(s2);

    return v1 <= v2 ? 100.0 * v1 / v2 : 100.0 * v2 / v1;
}

int main()
{
    while (gets(s1) != NULL && gets(s2) != NULL) {
        printf("%.2lf %%\n", solve() + EPS);
    }

    return 0;
}
