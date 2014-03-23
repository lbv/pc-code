#include <cstdio>

const int numbers[10][2] = {
    { 6, 8 },
    { 35, 49 },
    { 204, 288 },
    { 1189, 1681 },
    { 6930, 9800 },
    { 40391, 57121 },
    { 235416, 332928 },
    { 1372105, 1940449 },
    { 7997214, 11309768 },
    { 46611179, 65918161 }
};

int main()
{
    for (int i = 0; i < 10; ++i)
        printf("%10d%10d\n", numbers[i][0], numbers[i][1]);
    return 0;
}

#if 0
#include <cmath>
#include <cstdio>

typedef long long i64;


int main()
{
    int cnt = 0;
    for (i64 i = 2; cnt < 10; ++i) {
        i64 p = i*(i+1) / 2;
        i64 sp = sqrt(p);
        if (sp*sp == p) {
            printf("%lld %lld\n", sp, i);
            ++cnt;
        }
    }

    return 0;
}
#endif
