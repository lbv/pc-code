#include <algorithm>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;


#define MAXLEN 1048576

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned int       u32;
typedef unsigned long long u64;
typedef unsigned char      uch;


//
// I/O
//
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void skip_line() {
        for (; b != 10 && b != 13 && b != 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

struct Datum {
    string ing;
    int c;
    Datum(string Ing, int C) : ing(Ing), c(C) {}
    bool operator==(const Datum &x) const { return ing == x.ing; }
};

struct Recipe {
    string name; int cost;
    Recipe(string Name, int Cost) : name(Name), cost(Cost) {}
    bool operator<(const Recipe &x) const {
        if (cost != x.cost) return cost < x.cost;
        return name < x.name;
    }
};

typedef vector<Recipe> RV;

//
// Hash Map
//
#define HASHB 4096
struct HM {
    typedef vector<Datum> DV; DV b[HASHB];
    u32 fnv_hash(const string &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<char*>(k.c_str()));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    bool add(const Datum &k) {
        int i = fnv_hash(k.ing, k.ing.size() * sizeof(char)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j] == k) {  return false; }
        b[i].push_back(k);
        return true;
    }
    int get(string k) const {
        int i = fnv_hash(k, k.size() * sizeof(char)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].ing == k) { return b[i][j].c;  }
        return 0;
    }
};


char str[MAXLEN];
int len;
int m, n, b;
string title;


int main()
{
    Reader rr;
    int t = rr.next_u32();

    while (t--) {
        rr.skip_line();
        rr.next_real_line(str, len);
        for (int i = 0; i < len; ++i)
            str[i] = toupper(str[i]);

        title = string(str);
        m = rr.next_u32();
        n = rr.next_u32();
        b = rr.next_u32();

        HM hm;

        while (m--) {
            rr.next(str);
            int c = rr.next_u32();
            Datum d(str, c);
            hm.add(d);
        }

        RV recipes;
        while (n--) {
            rr.skip_line();
            rr.next_real_line(str, len);
            string recipe = string(str);

            int n_ing = rr.next_u32();
            int recipe_cost = 0;

            while (n_ing--) {
                rr.next(str);
                int k = rr.next_u32();

                recipe_cost += hm.get(string(str)) * k;
            }
            if (recipe_cost <= b)
                recipes.push_back(Recipe(recipe, recipe_cost));
        }

        printf("%s\n", title.c_str());
        if (recipes.size() > 0) {
            sort(recipes.begin(), recipes.end());
            cFor (RV, r, recipes)
                printf("%s\n", (r->name).c_str());
        }
        else
            puts("Too expensive!");
        putchar('\n');
    }

    return 0;
}
