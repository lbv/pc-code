#include <cstdio>
#include <cstring>

#define Zero(v) memset(v, 0, sizeof(v))

bool deck[4][13];
bool stp[4];
int suits[4];
int pts, pts2;

const char suit_id[5] = "SHDC";

int suit(char s)
{
    switch(s) {
    case 'S':
        return 0;
    case 'H':
        return 1;
    case 'D':
        return 2;
    case 'C':
        return 3;
    }
    return -1;
}

int rank(char r)
{
    if (r == 'A') return 0;
    if (r >= '2' && r <= '9') return r - '1';
    if (r == 'T') return 9;
    if (r == 'J') return 10;
    if (r == 'Q') return 11;
    return 12;
}

void add(char rc, char sc)
{
    int r = rank(rc);
    int s = suit(sc);

    deck[s][r] = true;
    ++suits[s];

    if (r == 0) pts += 4;
    else if (r == 12) pts += 3;
    else if (r == 11) pts += 2;
    else if (r == 10) pts += 1;
}

void solve()
{
    for (int i = 0; i < 4; ++i) {
        if (deck[i][12] && suits[i] == 1) --pts;
        if (deck[i][11] && suits[i] <= 2) --pts;
        if (deck[i][10] && suits[i] <= 3) --pts;

        if (deck[i][0] ||
            (deck[i][12] && suits[i] >= 2) ||
            (deck[i][11] && suits[i] >= 3))
            stp[i] = true;
    }

    pts2 = pts;
    for (int i = 0; i < 4; ++i) {
        if (suits[i] == 2) pts2 += 1;
        if (suits[i] == 1) pts2 += 2;
        if (suits[i] == 0) pts2 += 2;
    }

    if (pts2 < 14) {
        puts("PASS");
        return;
    }

    if (pts >= 16 && stp[0] && stp[1] && stp[2] && stp[3]) {
        puts("BID NO-TRUMP");
        return;
    }

    char best_suit;
    int hi = 0;
    for (int i = 0; i < 4; ++i)
        if (suits[i] > hi) {
            hi = suits[i];
            best_suit = suit_id[i];
        }

    printf("BID %c\n", best_suit);
}

int main()
{
    char r, s;  // rank, suit
    while (true) {
        if (scanf(" %c%c", &r, &s) != 2) break;

        Zero(deck);
        Zero(suits);
        Zero(stp);
        pts = 0;

        add(r, s);
        for (int i = 0; i < 12; ++i) {
            scanf(" %c%c", &r, &s);
            add(r, s);
        }

        solve();
    }

    return 0;
}
