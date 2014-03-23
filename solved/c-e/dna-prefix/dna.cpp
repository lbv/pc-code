#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define Zero(v) memset(v, 0, sizeof(v))

// Trie
struct Trie {
    struct Node {
        int ch[4];
        int n;
        Node() { n=0; Zero(ch); }
    };
    int sz;
    vector<Node> nodes;
    void init() { nodes.clear(); nodes.resize(1); sz = 1; }
    void insert(const char *s, int &ans) {
        int idx, cur = 0;
        int len = 0;

        while (*s) {
            switch (*s) {
            case 'A':
                idx = 0;
                break;
            case 'C':
                idx = 1;
                break;
            case 'G':
                idx = 2;
                break;
            case 'T':
                idx = 3;
                break;
            }
            if (! nodes[cur].ch[idx]) {
                nodes[cur].ch[idx] = sz++;
                nodes.resize(sz);
            }

            cur = nodes[cur].ch[idx];
            int score = ++nodes[cur].n * ++len;
            if (score > ans) ans = score;
            ++s;
        }
    }
};

Trie t;
char word[51];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        t.init();
        int ans = 0;

        while (n--) {
            scanf("%s", word);
            t.insert(word, ans);
        }

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}
