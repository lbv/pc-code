#include <cstdio>


int a, b, c;


bool solve()
{
    return a + b > c &&
        a + c > b &&
        b + c > a;
}

int main()
{
    int T;
    scanf("%d",&T);

    while (T--) {
        scanf("%d%d%d", &a, &b, &c);
        if (solve())
            puts("OK");
        else
            puts("Wrong!!");
    }

    return 0;
}
