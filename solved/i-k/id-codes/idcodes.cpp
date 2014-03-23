#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXLEN 50

char str[MAXLEN + 1];
int len;

int main()
{
    while (true) {
        scanf("%s", str);
        if (str[0] == '#') break;

        len = strlen(str);

        if (next_permutation(str, str + len))
            printf("%s\n", str);
        else
            puts("No Successor");
    }

    return 0;
}
