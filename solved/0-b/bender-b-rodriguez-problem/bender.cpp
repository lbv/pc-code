#include <cstdio>
#include <cstring>


enum Dirs {
    XP,  // X positive
    XN,  // X negative
    YP,
    YN,
    ZP,
    ZN
};


int L;
int tip;
char bend[4];

const char dir_strs[6][4] = {
    "+x",
    "-x",
    "+y",
    "-y",
    "+z",
    "-z"
};

const int tab_bends[6][4] = {
//    YP  YN  ZP  ZN
    { YP, YN, ZP, ZN }, // XP
    { YN, YP, ZN, ZP }, // XN
    { XN, XP, YP, YP }, // YP
    { XP, XN, YN, YN }, // YN
    { ZP, ZP, XN, XP }, // ZP
    { ZN, ZN, XP, XN }  // ZN
};


void apply_bend()
{
    int b = -1;
    for (int i = 2; i < 6; ++i)
        if (strcmp(bend, dir_strs[i]) == 0) {
            b = i - 2;
            break;
        }
    if (b < 0) return;
    tip = tab_bends[tip][b];
}

int main()
{
    while (true) {
        scanf("%d", &L);
        if (L == 0) break;

        tip = XP;
        for (--L; L--; ) {
            scanf("%s", bend);
            apply_bend();
        }

        printf("%s\n", dir_strs[tip]);
    }

    return 0;
}
