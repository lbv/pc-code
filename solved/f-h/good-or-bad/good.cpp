#include <cstdio>
#include <cstring>

#define MAXLEN 50

#define Zero(v) memset(v, 0, sizeof(v))

// vow[i][j] is true if the prefix of size i of the string can end in a
// maximum of j consecutive vowels
bool vow[MAXLEN + 1][3];

// con[i][j] is similar, but for consonants
bool con[MAXLEN + 1][5];

char str[MAXLEN + 1];
int len;

bool good, bad;  // indicate if the input can be good, or can be bad

bool is_vowel(char c)
{
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void run_dp()
{
    Zero(vow);
    Zero(con);

    vow[0][0] = true;
    con[0][0] = true;

    bad = false;
    for (int i = 1; i <= len; ++i) {
        bool v = is_vowel(str[i - 1]);

        if (v || str[i - 1] == '?') {
            if (vow[i - 1][2]) bad = true;
            for (int j = 0; j < 2; ++j)
                if (vow[i - 1][j]) {
                    vow[i][j + 1] = true;
                    con[i][0] = true;
                }
        }

        if (! v) {
            if (con[i - 1][4]) bad = true;
            for (int j = 0; j < 4; ++j)
                if (con[i - 1][j]) {
                    con[i][j + 1] = con[i - 1][j];
                    vow[i][0] = true;
                }
        }
    }

    good = false;
    for (int j = 0; j < 3; ++j)
        good |= vow[len][j];
    for (int j = 0; j < 5; ++j)
        good |= con[len][j];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s", str);
        len = strlen(str);

        run_dp();

        printf("Case %d: ", ++ncase);

        if (good && !bad)
            puts("GOOD");
        else if (bad && !good)
            puts("BAD");
        else
            puts("MIXED");
    }

    return 0;
}
