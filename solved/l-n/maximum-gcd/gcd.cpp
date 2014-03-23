#include <cstdio>


#define MAXM 100


typedef unsigned int u32;


struct LineReader {
    char b; LineReader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }


int ns[MAXM];
int M;


int solve()
{
    int ans = 0;
    for (int i = 0; i < M; ++i)
        for (int j = i + 1; j < M; ++j) {
            int g = gcd(ns[i], ns[j]);
            if (g > ans) ans = g;
        }
    return ans;
}

int main()
{
    LineReader lr;
    int N = lr.next_u32();
    lr.skip_line();

    while (N--) {
        M = 0;
        while (lr.has_next())
            ns[M++] = lr.next_u32();
        lr.skip_line();

        printf("%d\n", solve());
    }

    return 0;
}
