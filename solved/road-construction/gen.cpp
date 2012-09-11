#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;


#define MAXT 500
#define MAXM 50
#define MAXW 1000


vector<string> cities;
int ncities;


void test_case()
{
    int m = rand() % MAXM + 1;

    printf("\n%d\n", m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        do {
            u = rand() % (2*m);
            v = rand() % (2*m);
        } while (u == v);

        int w = rand() % (MAXW + 1);

        if (rand() % 5 == 0) w = 0;

        printf("%s %s %d\n", cities[u].c_str(), cities[v].c_str(), w);
    }
}

void prepare()
{
    char name[3];

    name[2] = 0;
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j) {
            name[0] = 'a' + i;
            name[1] = 'a' + j;
            cities.push_back(string(name));
        }

    ncities = cities.size();
}

int main()
{
    srand(time(NULL));

    prepare();

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
