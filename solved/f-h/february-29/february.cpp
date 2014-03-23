#include <cstdio>
#include <cstring>

// Returns the amount of numbers in the range [a:b] that are divisible by d
int f(int a, int b, int d)
{
    int res = b / d - a / d;
    if (a % d == 0) ++res;
    return res;
}

int solve(int year1, int year2)
{
    if (year2 < year1) return 0;

    return f(year1, year2, 4) - f(year1, year2, 100) + f(year1, year2, 400);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        char month[20];
        int day, year1, year2;

        scanf("%s %d, %d", month, &day, &year1);
        if (strncmp(month, "Jan", 3) != 0 &&
            strncmp(month, "Feb", 3) != 0)
            ++year1;

        scanf("%s %d, %d", month, &day, &year2);
        if (strncmp(month, "Jan", 3) == 0 ||
            (strncmp(month, "Feb", 3) == 0 && day < 29))
            --year2;

        printf("Case %d: %d\n", ++ncase, solve(year1, year2));
    }
}
