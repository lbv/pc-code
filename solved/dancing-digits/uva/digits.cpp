#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_PERM  = 40320;         // 8!
const int MAX_NODES = MAX_PERM * 8;


struct Trie {
    struct Node {
        int ch[8];
        int n;
    };
    Node nodes[MAX_NODES];
    int sz;
    void init() { Zero(nodes); sz = 1; }
    int insert(const char *s) {
        int idx, cur = 0;
        for (int i = 0; i < 8; ++i) {
            idx = toupper(s[i]) - 'A';
            if (! nodes[cur].ch[idx])
                nodes[cur].ch[idx] = sz++;
            cur = nodes[cur].ch[idx];
        }
        return ++nodes[cur].n;
    }
};

struct Node {
    char p[8];  // permutation
    int  s;     // steps
    Node() {}
    Node(const char *P, int S) : s(S) { strncpy(p, P, 8); }
    bool operator==(const Node &x) { return strncmp(p, x.p, 8) == 0; }
};

bool ci_cmp(char a, char b) { return toupper(a) < toupper(b); }


char perm[9];

Trie trie;
Node q[MAX_PERM];

bool is_prime[16];

const int primes[] = { 2, 3, 5, 7, 11, 13, -1 };


bool can_dance(char a, char b)
{
    if (isupper(a) == isupper(b)) return false;
    int n = toupper(a) - 'A' + 1 + toupper(b) - 'A' + 1;
    return is_prime[n];
}

bool find_dancing_pair(const char *p, int i)
{
    if (i - 1 >= 0 && can_dance(p[i], p[i-1])) return true;
    if (i + 1 <  8 && can_dance(p[i], p[i+1])) return true;
    return false;
}

int solve()
{
    char aux[8];
    strncpy(aux, perm, 8);
    sort(aux, aux + 8, ci_cmp);
    Node target(aux, 0);

    int front = -1, back = 0;
    q[++front] = Node(perm, 0);

    trie.init();
    trie.insert(perm);

    while (back <= front) {
        Node &nd = q[back++];
        if (nd == target) return nd.s;

        for (int from = 0; from < 8; ++from)
            for (int to = 0; to < 8; ++to) {
                if (from == to) continue;

                int x = 0;
                for (int k = 0; k < 8; ++k) {
                    if (x == from) ++x;
                    aux[k] = k == to ? nd.p[from] : nd.p[x++];
                }

                if (find_dancing_pair(aux, to) && trie.insert(aux) == 1)
                    q[++front] = Node(aux, nd.s + 1);
            }
    }

    return -1;
}

char num_to_char(int n)
{
    if (n > 0) return 'A' + n - 1;
    return 'a' - n - 1;
}

void prepare()
{
    for (int i = 0; primes[i] >= 0; ++i)
        is_prime[primes[i]] = true;
}

int main()
{
    prepare();

    int ncase = 0;
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        perm[0] = num_to_char(n);

        for (int i = 1; i < 8; ++i) {
            scanf("%d", &n);
            perm[i] = num_to_char(n);
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
