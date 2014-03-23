#include <cstdio>
#include <cstring>
#include <set>
using namespace std;


#define MAXBILL 1000000

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;
typedef long long    i64;

typedef set<int>     IS;
typedef IS::iterator ISi;


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
};


// bills[i] has the amount of bills with value i
int bills[MAXBILL + 1];
int n, k, b;
i64 total;


int main()
{
    Reader rr;

    while (true) {
        n = rr.next_u32();
        if (n == 0) break;

        total = 0;
        Zero(bills);
        IS bag;

        while (n--) {
            k = rr.next_u32();

            while (k--) {
                b = rr.next_u32();
                if (bills[b] == 0)
                    bag.insert(b);
                ++bills[b];
            }

            int front = *(bag.begin());
            int back  = *(bag.rbegin());

            if (--bills[front] == 0)
                bag.erase(bag.begin());
            if (--bills[back] == 0) {
                ISi it= bag.end();
                bag.erase(--it);
            }

            total += back - front;
        }
        printf("%lld\n", total);
    }

    return 0;
}
