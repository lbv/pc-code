#include <algorithm>
#include <cstdio>
using namespace std;

int num[3];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &num[0], &num[1], &num[2]);
        sort(num, num + 3);

        int a = num[0]*num[0];
        int b = num[1]*num[1];
        int c = num[2]*num[2];

        printf("Case %d: %s\n", ++ncase, a+b==c ? "yes" : "no");
    }

    return 0;
}
