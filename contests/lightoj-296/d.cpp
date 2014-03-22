#include <cstdio>
#include <cstring>


#define MAXLEN 75


char num[MAXLEN + 1];
int  len;


int solve()
{
    if (len < 2) return 0;
    int n = 0;
    for (int i = 0; i < len; ++i) n += num[i] - '0';
    int deg = 1;

    while (n > 9) {
        int x = 0;
        while (n) {
            x += n % 10;
            n /= 10;
        }
        ++deg;
        n = x;
    }

    return deg;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", num);
        len = strlen(num);

        printf("%d\n", solve());
    }

    return 0;
}
