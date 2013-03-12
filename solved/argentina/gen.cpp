#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>
using namespace std;


#if 0
#define MAXT   50
#define MAXLEN 20
#define MAXABI 99
#endif

#if 1
#define MAXT   50
#define MAXLEN 6
#define MAXABI 99
#endif


const char alpha[] = "aeoiubctrs";
const int  nalpha  = 10;


void gen_name(char *name, bool crit)
{
    int len = crit ? MAXLEN : rand() % MAXLEN + 1;
    for (int i = 0; i < len; ++i)
        name[i] = alpha[rand() % nalpha];
    name[len] = 0;
}

void test_case(bool crit = false)
{
    set<string> names;

    for (int i = 0; i < 10; ++i) {
        char name[MAXLEN + 1];
        string str;

        do {
            gen_name(name, crit);
            str = string(name);
        } while (names.find(str) != names.end());

        names.insert(str);

        int attack = rand() % (MAXABI + 1);
        int defend = rand() % (MAXABI + 1);
        printf("%s %d %d\n", name, attack, defend);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}
