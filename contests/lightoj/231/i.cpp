#include <cstdio>
#include <cstring>


#define MAXSONG 100000
#define MAXNAME 5000

char song[MAXSONG + 1];
char name[MAXNAME + 1];
int q;
int ls, ln;


bool solve()
{
    int i = 0;
    for (int j = 0; j < ln; ++j) {
        while (i < ls && song[i] != name[j]) ++i;
        if (i >= ls) return false;
        ++i;
    }
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s %d", song, &q);
        ls = strlen(song);

        printf("Case %d:\n", ++ncase);

        while (q--) {
            scanf("%s", name);
            ln = strlen(name);

            if (solve())
                puts("Yes");
            else
                puts("No");
        }
    }

    return 0;
}
