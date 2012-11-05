#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <set>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))


#if 1
#define MAXT 10
#define MAXN 100000
#define MAXV 20000
#endif

#if 0
#define MAXT 25
#define MAXN 100
#define MAXV 90
#endif


typedef pair<int, int> II;
typedef set<II> IIS;


int team[MAXV];


void test_case()
{
    int n = rand() % MAXN + 1;
    printf("%d\n", n);

    IIS fights;
    Zero(team);

    while (n--) {
        int u, v;
        do {
            u = rand() % MAXV;
            v = rand() % MAXV;

            if (team[u] == 0)
                team[u] = rand() % 2 + 1;
            if (team[v] == 0)
                team[v] = rand() % 2 + 1;

        } while (team[u] == team[v] || fights.find(II(u, v)) != fights.end());

        fights.insert(II(u, v));
        printf("%d %d\n", u + 1, v + 1);
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
