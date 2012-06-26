#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

// why don't they specify these things?
#define MAXLEN 1024

struct Comp {
    bool operator() (const char &a, const char &b) {
        char A = toupper(a);
        char B = toupper(b);
        if (A < B) return true;
        if (A > B) return false;
        return a < b;
    }
};

char word[MAXLEN + 1];
char aux[MAXLEN + 1];
int len;

int main()
{
    int n;
    scanf("%d", &n);

    Comp comp;

    while (n--) {
        scanf("%s", word);
        len = strlen(word);

        sort(word, word + len, comp);

        strcpy(aux, "");

        while (true) {
            if (strcmp(aux, word) == 0) continue;
            printf("%s\n", word);
            strcpy(aux, word);
            if (! next_permutation(word, word + len, comp)) break;
        }

    }

    return 0;
}
