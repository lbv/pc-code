#include <cstdio>

#define Back(b)    ((b) & -(b))
#define PopBack(b) (b &= ~Back(b))

int M;

int popcnt(int x)
{
    int p = 0;
    while (x != 0) {
        PopBack(x);
        ++p;
    }
    return p;
}

int b1()
{
    return popcnt(M);
}

int b2()
{
    int b = 0;
    for (int x = M; x != 0; x /= 10) {
        int d = x % 10;
        b += popcnt(d);
    }
    return b;
}

int main()
{
    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%d", &M);

        printf("%d %d\n", b1(), b2());
    }

    return 0;
}
