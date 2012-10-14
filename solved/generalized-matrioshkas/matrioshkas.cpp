#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;


const int INF = 10000000 + 100;


typedef pair<int, int> II;
typedef stack<II>      IIS;


struct LineReader {
    char b; LineReader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }

    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};


int main()
{
    LineReader lr;
    for (; ! lr.eof(); lr.skip_line()) {
        bool ans = true;

        IIS st;
        int sz = INF;

        while (lr.has_next()) {
            int n = lr.next_int();
            if (! ans) continue;

            if (n < 0) {
                if (sz == INF) {
                    st.push(II(-n, 0));
                    sz = -n;
                    continue;
                }
                sz += n;
                if (sz <= 0) ans = false;
                st.push(II(-n, sz));
                sz = -n;
            }
            else {
                if (st.empty()) { ans = false; continue; }
                II t = st.top();
                st.pop();
                if (t.first != n) ans = false;
                sz = t.second;
            }
        }
        if (ans && !st.empty()) ans = false;

        if (ans)
            puts(":-) Matrioshka!");
        else
            puts(":-( Try again.");
    }

    return 0;
}
