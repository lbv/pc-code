#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <set>
#include <vector>
using namespace std;


#if 0
#define MAXT 30
#define MAXN 10000
#define MAXM 20000
#endif

#if 1
#define MAXT 25
#define MAXN 6
#define MAXM 1000
#endif


#define Zero(v) memset((v), 0, sizeof(v))


typedef pair<int, int> II;
typedef vector<int> IV;
typedef set<II>     IIS;


void test_case()
{
    int n = rand() % (MAXN - 2) + 3;
    int MaxEdges = min(n*(n-1)/2, MAXM);
    int m = rand() % (MaxEdges + 1);

    if (m < n - 1) m = n - 1;

    printf("\n%d %d\n", n, m);

    IV ls;
    IIS s;
    for (int i = 0; i < n; ++i)
        ls.push_back(i);
    random_shuffle(ls.begin(), ls.end());

    printf("%d %d\n", ls[0], ls[1]); --m;
    int u = ls[0], v = ls[1];
    if (u > v) swap(u, v);
    s.insert(II(u, v));

    for (int i = 2; i < n; ++i) {
        u = ls[rand() % i], v = ls[i];
        printf("%d %d\n", u, v); --m;
        if (u > v) swap(u, v);
        s.insert(II(u, v));
    }

    while (m--) {
        int u, v;
        do {
            u = rand() % n;
            v = rand() % n;
            if (u > v) swap(u, v);
        } while (u == v || s.find(II(u, v)) != s.end());

        s.insert(II(u, v));

        if (rand() % 2 == 0) swap(u, v);
        printf("%d %d\n", u, v);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
