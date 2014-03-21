#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define MAXLEN 1000

#define Zero(v) memset(v, 0, sizeof(v))

// Trie
struct Trie {
    struct Node {
        int ch[26];
        int n;
        Node() { n = 0; Zero(ch); }
    };
    int sz;
    vector<Node> nodes;

    struct Node2 {
        string pref;
        int n;
        Node2() { n = 0; }
    };
    vector<Node2> map;

    void init() {
        nodes.clear(); nodes.resize(1); sz = 1;
        map.clear(); map.resize(MAXLEN + 1);
    }
    void insert(const char *s) {
        int idx, cur = 0, cnt = 0;
        const char *first = s;

        while (*s) {
            idx = *s - 'a';
            if (! nodes[cur].ch[idx]) {
                nodes[cur].ch[idx] = sz++;
                nodes.resize(sz);
            }

            cur = nodes[cur].ch[idx];
            ++(nodes[cur].n);
            ++s;
            ++cnt;

            if (nodes[cur].n >= map[cnt].n) {
                string str(first, cnt);

                if (nodes[cur].n > map[cnt].n) {
                    map[cnt].n = nodes[cur].n;
                    map[cnt].pref = str;
                }
                else if (str < map[cnt].pref)
                    map[cnt].pref = str;
            }
        }
    }

    void find(int n) {
        if (map[n].n == 0) {
            puts("Not Found!");
            return;
        }
        printf("%s %d\n", map[n].pref.c_str(), map[n].n);
    }
};

Trie t;
char str[MAXLEN + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        t.init();

        while (n--) {
            scanf("%s", str);
            t.insert(str);
        }

        printf("Case %d:\n", ++ncase);

        int q;
        scanf("%d", &q);

        while (q--) {
            int n;
            scanf("%d", &n);
            t.find(n);
        }
    }

    return 0;
}
