#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAXLEN 100


char s1[MAXLEN + 1];
char s2[MAXLEN + 1];


int random_str(char *s)
{
    int len = rand() % MAXLEN + 1;
    if (rand() % 20 == 0) len = MAXLEN;

    for (int i = 0; i < len; ++i) {
        int n = rand() % 30;
        if (n >= 26) { s[i] = ' '; continue; }
        s[i] = n + (rand() % 2 == 0 ? 'a' : 'A');
    }
    s[len] = 0;
    return len;
}

void test_case()
{
    int l1 = random_str(s1);

    if (rand() % 10 == 0)
        random_str(s2);
    else {
        int l2 = l1 + (rand() % (MAXLEN - l1 + 1));

        for (int i = 0; i < l2; ++i) {
            if (i < l1)
                s2[i] = rand() % 2 == 0 ? tolower(s1[i]) : toupper(s1[i]);
            else
                s2[i] = ' ';
        }
        s2[l2] = 0;
        random_shuffle(s2, s2 + l2);
    }

    printf("%s\n%s\n", s1, s2);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
