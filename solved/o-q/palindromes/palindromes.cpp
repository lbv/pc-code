#include <cctype>
#include <cstdio>
#include <cstring>


#define MAXLEN 20


char str[MAXLEN + 1];
int len;

//                             ABCDEFGHIJKLMNOPQRSTUVWXYZ
const char mirror_letters[] = "A...3..HIL.JM.O...2TUVWXY5";
//                            123456789
const char mirror_digits[] = "1SE.Z..8.";


bool is_mirrored()
{
    char m;
    int idx;
    for (int i = 0, j = len - 1; i <= j; ++i, --j) {
        if (isupper(str[i])) {
            idx = str[i] - 'A';
            m = mirror_letters[idx];
        }
        else {
            idx = str[i] - '1';
            m = mirror_digits[idx];
        }

        if (str[j] != m) return false;
    }
    return true;
}

bool is_palindrome()
{
    for (int i = 0, j = len-1; i < j; ++i, --j)
        if (str[i] != str[j])
            return false;
    return true;
}

int main()
{
    while (true) {
        if (scanf("%s", str) != 1) break;
        len = strlen(str);

        bool pal = is_palindrome();
        bool mir = is_mirrored();

        printf("%s", str);

        if (pal && mir)
            puts(" -- is a mirrored palindrome.");
        else if (pal)
            puts(" -- is a regular palindrome.");
        else if (mir)
            puts(" -- is a mirrored string.");
        else
            puts(" -- is not a palindrome.");
        putchar('\n');
    }

    return 0;
}
