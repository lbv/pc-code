#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


#if 0
#define MAXT 12
#define MAXN 100000
#define MAXR 1000000000
#endif

#if 1
#define MAXT 25
#define MAXN 10
#define MAXR 1000000
#endif


void test_case()
{
    vector<int> rs;
    int n = rand() % MAXN + 1;

    for (int i = 0; i < n; ++i)
        rs.push_back(rand() % MAXR + 1);

    sort(rs.begin(), rs.end());
    vector<int>::iterator it = unique(rs.begin(), rs.end());
    rs.resize(it - rs.begin());

    n = rs.size();
    printf("%d\n%d", n, rs[0]);
    for (int i = 1; i < n; ++i)
        printf(" %d", rs[i]);
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
