#include <cctype>
#include <cstdio>
#include <cstring>


#define MAXLEN 20


struct LineReader {
    char b; LineReader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }

    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
};


char word[MAXLEN + 1];


int main()
{
    LineReader lr;

    while (true) {
        int n = 0;
        char letter;
        bool ans = true;

        while (lr.has_next()) {
            lr.next(word);
            ++n;

            if (n == 1 && strcmp(word, "*") == 0) return 0;

            if (n == 1)
                letter = tolower(word[0]);
            else
                if (tolower(word[0]) != letter) ans = false;
        }
        lr.skip_line();
        puts(ans ? "Y" : "N");
    }

    return 0;
}
