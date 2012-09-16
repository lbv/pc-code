#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXNAME 20


typedef unsigned int  u32;
typedef unsigned char uch;

typedef vector<int> IV;


// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i=0; i < n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};

//
// Hash Map
//
#define HASHB 65536
struct HM {
    struct Datum {
        char name[MAXNAME + 1];
        int i;
        Datum(const char *str, int I) : i(I) { strcpy(name, str); }
        bool eq(const char *x) const {
            return strcmp(name, x) == 0;
        }
    };

    typedef vector<Datum> DV; DV b[HASHB];
    int idx;
    HM() { idx = 1; }
    u32 fnv_hash(const char *str, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<char*>(str));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    bool add(const char *str, int &id) {
        int i = fnv_hash(str, strlen(str) * sizeof(char)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].eq(str)) { id = b[i][j].i; return false; }
        id = idx;
        b[i].push_back(Datum(str, idx++));
        return true;
    }
};


int F;
char n1[MAXNAME + 1];
char n2[MAXNAME + 1];
IV people;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &F);

        HM hm;
        Set s(F + 1);
        people = IV(F + 1, 1);

        while (F--) {
            scanf("%s%s", n1, n2);

            int a, b;

            hm.add(n1, a);
            hm.add(n2, b);

            int p = 0;

            if (s.find(a) == s.find(b))
                p = people[s.find(a)];
            else {
                p = people[s.find(a)] + people[s.find(b)];
                s.merge(a, b);
                people[s.find(a)] = p;
            }

            printf("%d\n", p);
        }
    }

    return 0;
}
