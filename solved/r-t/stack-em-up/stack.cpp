#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAXSH 100

typedef unsigned int u32;

// I/O
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
    void next_real_line(char *s) {
        for (; b != 10 && b != 13 && b != 0; read()) *s++ = b; *s = 0;
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

struct Card {
    int r;  // rank
    int s;  // suit
    Card(int R, int S) : r(R), s(S) {}
    Card() {}
};

int shuffles[MAXSH][53];

Card deck_a[53];
Card deck_b[53];

Card *A, *B;
int n;

char line[80];

void deck_init(Card *d)
{
    int idx = 1;
    for (int s = 1; s <= 4; ++s) {
        for (int r = 2; r <= 13; ++r)
            d[idx++] = Card(r, s);
        d[idx++] = Card(1, s);
    }
}

void deck_shuffle(Card *src, Card *dst, int sh)
{
    for (int i = 1; i <= 52; ++i) {
        int j = shuffles[sh][i];
        dst[i] = src[j];
    }
}

void print_card(const Card &c)
{
    switch(c.r) {
    case 1:
        printf("Ace");
        break;
    case 11:
        printf("Jack");
        break;
    case 12:
        printf("Queen");
        break;
    case 13:
        printf("King");
        break;
    default:
        printf("%d", c.r);
    }

    printf(" of ");

    switch(c.s) {
    case 1:
        printf("Clubs\n");
        break;
    case 2:
        printf("Diamonds\n");
        break;
    case 3:
        printf("Hearts\n");
        break;
    case 4:
        printf("Spades\n");
        break;
    }
}

int main()
{
    Reader rr;

    int T = rr.next_u32();
    bool first = true;
    while (T--) {
        n = rr.next_u32();

        for (int i = 0; i < n; ++i)
            for (int j = 1; j <= 52; ++j)
                shuffles[i][j] = rr.next_u32();

        rr.next_real_line(line);

        A = deck_a;
        B = deck_b;
        deck_init(A);

        while (true) {
            rr.next_real_line(line);
            int sh = atoi(line);
            if (sh == 0) break;

            deck_shuffle(A, B, sh - 1);
            swap(A, B);
        }

        if (first) first = false;
        else putchar('\n');

        for (int i = 1; i <= 52; ++i)
            print_card(A[i]);
    }

    return 0;
}
