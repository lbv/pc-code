#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXN 10000000
#define MAXK 10000000
#define MAXI 1000000000


int main()
{
    srand(time(NULL));

    int n = MAXN;
    int k = rand() % MAXK + 1;
    printf("%d %d\n", n, k);

    while (n--) {
        int i = rand() % MAXI + 1;
        printf("%d\n", i);
    }

    return 0;
}
