#include <cstdio>


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


int n;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();

        rr.next_u32();  // the first number, which should always be a zero
        --n;

        int above = 0;  // amount of students above the first one
        int below = 1;  // amount of students below or equal to the first one

        while (n--) {
            int i = rr.next_u32();
            if (i <= above) ++above;
            else ++below;
        }

        printf("Case %d: %d\n", ++ncase, below);
    }

    return 0;
}
