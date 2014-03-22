#include <cstdio>


char ctype;
int ca, dw;


int main()
{
    int m;
    scanf("%d", &m);
    while (m--) {
        scanf(" %c%*s%d%d", &ctype, &ca, &dw);

        int mg = 0;
        if      (ctype == 'M') mg = 44 * ca;
        else if (ctype == 'S') mg = 150 * ca;
        else if (ctype == 'B') mg = 390 * ca;

        if (mg < 20*dw) puts("Monitor animal's behavior.");
        else if (mg <= 100*dw)
            puts("Induce vomiting and administer activated charcoal. "
                 "Animal may return home.");
        else
            puts("Induce vomiting and administer activated charcoal. "
                 "Leave animal at clinic.");
    }

    return 0;
}
