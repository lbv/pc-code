#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#define MAXLEN 1048575

typedef unsigned int u32;

typedef vector<int>    IV;
typedef vector<string> SV;

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
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l; *s = 0;
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

char in[MAXLEN + 1];
int len;
int N;

IV perm;
SV num;

void process_perm_array()
{
    IV aux;

    int i = 0;
    while (true) {
        while (i < len && ! isdigit(in[i])) ++i;

        int n;
        if (sscanf(in + i, "%d", &n) != 1) break;
        aux.push_back(n - 1);

        while (i < len && isdigit(in[i])) ++i;
    }

    N = aux.size();

    perm = IV(N);

    for (int i = 0; i < N; ++i)
        perm[aux[i]] = i;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();
    rr.next_real_line(in, len);

    bool first = true;
    while (T--) {
        rr.next_real_line(in, len);  // blank line
        rr.next_real_line(in, len);

        process_perm_array();

        num.clear();
        for (int i = 0; i < N; ++i) {
            rr.next(in);
            num.push_back(string(in));
        }
        rr.next_real_line(in, len);

        if (first) first = false;
        else puts("");

        for (int i = 0; i < N; ++i)
            printf("%s\n", num[perm[i]].c_str());
    }

    return 0;
}
