#include <cstdio>
#include <cstring>
#include <list>
using namespace std;


#define MAXLEN 100000

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef list<char> CL;
typedef CL::iterator CLi;


char str[MAXLEN + 1];


int main()
{
    while (gets(str) != NULL) {
        CL text;
        CLi it = text.begin();

        int len = strlen(str);
        for (int i = 0; i < len; ++i) {
            if (str[i] == '[')
                it = text.begin();
            else if (str[i] == ']')
                it = text.end();
            else
                text.insert(it, str[i]);
        }

        For (CL, c, text)
            putchar(*c);
        putchar('\n');
    }

    return 0;
}
