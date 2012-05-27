#include <cstdio>
#include <cstring>
#include <memory>
using namespace std;

#define MAXL 10

#define Zero(v) memset(v, 0, sizeof(v))

struct Trie {
    typedef auto_ptr<Trie> TP;
    bool end;
    TP children[10];

    Trie() { end = false; Zero(children); }
    void insert(const char *s, bool &c) {
        Trie *cur = this;

        while (*s) {
            if (cur->end) { c = false; return; }

            int idx = *s - '0';
            if (! cur->children[idx].get())
                cur->children[idx] = TP(new Trie());

            cur = cur->children[idx].get();
            ++s;
        }

        for (int i = 0; i < 10; ++i)
            if (cur->children[i].get()) c = false;
        cur->end = true;
    }
};

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        Trie t;
        bool consistent = true;
        char num[MAXL + 1];

        while (n--) {
            scanf("%s", num);

            if (consistent)
                t.insert(num, consistent);
        }

        printf("Case %d: %s\n", ++ncase, consistent ? "YES" : "NO");
    }

    return 0;
}
