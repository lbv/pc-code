#include <cstdio>
#include <map>
#include <string>
using namespace std;


#define MAXLEN 20


typedef map<string, int> SIM;
typedef SIM::iterator SIMi;


int N, D;
char s[MAXLEN + 1];

SIM tuples;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);
        tuples = SIM();

        while (N--) {
            int v;
            scanf("%s%d", s, &v);
            tuples[s] = v;
        }

        scanf("%d%s", &D, s);

        printf("Case %d: ", ++ncase);
        SIMi it = tuples.find(s);
        if (it == tuples.end() || it->second > D + 5)
            puts("Do your own homework!");
        else if (it->second > D)
            puts("Late");
        else
            puts("Yesss");
    }

    return 0;
}
