#include <cstdio>

int n;

/*
 * s : The counter of the sheet of paper being used
 * l : The number of sheets of paper left to use
 * p : The counter of the next page to print
 * n : The total number os pages to print (global)
 */
void print_sheets(int s, int l, int p)
{
    if (l == 0) return;

    printf("Sheet %d, front:", s);

    if (p + 4*l - 1 <= n)
        printf(" %d", p + 4*l - 1);
    else
        printf(" Blank");

    printf(", %d\n", p);
    if (p + 1 > n) return;

    printf("Sheet %d, back : %d", s, p + 1);

    if (p + 4*l - 2 <= n)
        printf(", %d\n", p + 4*l - 2);
    else
        puts(", Blank");

    print_sheets(s + 1, l - 1, p + 2);
}

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        printf("Printing order for %d pages:\n", n);
        print_sheets(1, (n + 3) / 4, 1);
    }

    return 0;
}
