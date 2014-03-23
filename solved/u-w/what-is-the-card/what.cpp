#include <cstdio>

struct Card {
    char r;  // rank
    char s;  // suit
    Card(char R, char S) : r(R), s(S) {}
    Card() {}
    int val() {
        if (r >= '2' && r <= '9')
            return r - '0';
        return 10;
    }
};

Card deck[52];

Card solve()
{
    int top = 26;
    int Y = 0;

    for (int i = 0; i < 3; ++i) {
        int X = deck[top].val();
        Y += X;
        top -= 11 - X;
    }

    --Y;
    if (Y <= top) return deck[Y];
    return deck[26 + Y - top];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        for (int i = 0; i < 52; ++i) {
            char r, c;
            scanf(" %c%c", &r, &c);
            deck[i] = Card(r, c);
        }

        Card ans = solve();
        printf("Case %d: %c%c\n", ++ncase, ans.r, ans.s);
    }

    return 0;
}
