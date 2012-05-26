#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned int u32;

#define WORD_LEN   100
#define LINE_LEN   10000
#define TRIE_CHARS 100000

#define Zero(v) memset(v, 0, sizeof(v))

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    // Optional methods
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    void skip_line() {
        for (; b != 10 && b != 13; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next_real_line(char *s) {
        for (; b != 10 && b != 13; read()) *s++ = b; *s = 0;
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

// Trie
struct Trie {
    struct Node {
        int ch[52];
        int n;
    };
    int sz;
    Node nodes[TRIE_CHARS + 1];

    void init() { Zero(nodes); sz = 1; }

    void prepare_word(char *w) {
        int len = strlen(w);

        if (len > 2)
            sort(w + 1, w + len - 1);
    }

    void insert(char *s) {
        prepare_word(s);

        int idx, cur = 0;

        while (*s) {
            if (islower(*s))
                idx = *s - 'a';
            else
                idx = *s - 'A' + 26;

            if (! nodes[cur].ch[idx])
                nodes[cur].ch[idx] = sz++;

            cur = nodes[cur].ch[idx];
            ++s;
        }
        ++nodes[cur].n;
    }

    int lookup(char *s) {
        prepare_word(s);

        int idx, cur = 0;

        while (*s) {
            if (islower(*s))
                idx = *s - 'a';
            else
                idx = *s - 'A' + 26;
            if (! nodes[cur].ch[idx]) return 0;

            cur = nodes[cur].ch[idx];
            ++s;
        }

        return nodes[cur].n;
    }
};

Trie t;
char word[WORD_LEN + 1];
char line[LINE_LEN + 1];

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        int n = rr.next_u32();

        t.init();
        while (n--) {
            rr.next(word);
            t.insert(word);
        }

        printf("Case %d:\n", ++ncase);
        int m = rr.next_u32();
        rr.skip_line();
        while (m--) {
            rr.next_real_line(line);

            int ans = 1;
            char *tok = strtok(line, " ");

            for (; tok != NULL; tok = strtok(NULL, " "))
                ans *= t.lookup(tok);

            printf("%d\n", ans);
        }
    }

    return 0;
}
