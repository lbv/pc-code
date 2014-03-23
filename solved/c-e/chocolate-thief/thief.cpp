#include <cstdio>
#include <cstring>

#define MAXL 20
#define INF  1000010

char name[MAXL + 1];
char s1[MAXL + 1];
char s2[MAXL + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        int min = INF;
        int max = 0;
        int w, h, l, v;

        while (n--) {
            scanf("%s%d%d%d", name, &w, &h, &l);
            v = w*h*l;

            if (v > max) max = v, strcpy(s2, name);
            if (v < min) min = v, strcpy(s1, name);
        }

        if (min == max)
            printf("Case %d: no thief\n", ++ncase);
        else
            printf("Case %d: %s took chocolate from %s\n", ++ncase, s2, s1);
    }

    return 0;
}
