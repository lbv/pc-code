#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10000
#define MAXC 100
#endif

#if 1
#define MAXT 25
#define MAXC 20
#endif


struct Point {
    int x, y, z;
    Point() {}
    Point(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
};


Point rand_point()
{
    int x = rand() % (MAXC + 1);
    int y = rand() % (MAXC + 1);
    int z = rand() % (MAXC + 1);

    return Point(x, y, z);
}

void test_case()
{
    Point A, B, C;

    A = rand_point();
    B = rand_point();
    C = rand_point();

    printf("%d %d %d %d %d %d %d %d %d\n",
           A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
