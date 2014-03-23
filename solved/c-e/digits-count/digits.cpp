#include <cstdio>
#include <cstring>


#define MAXDIG 9


typedef long long i64;


int A, B;
i64 cnt1[10];
i64 cnt2[10];

// string representation of current number
char S[MAXDIG + 1];

int len;  // length of number

// suf[i]: number formed by last i digits of the current number
i64 suf[MAXDIG];

// occ[i]: number of occurrences of any digit in numbers of i digits or
// less (including numbers that start with zero)
i64 occ[MAXDIG];

// oc0[i]: number of occurrences of zero for numbers of i digits, without
// leading zeroes
i64 oc0[MAXDIG];

// powers of 10
i64 p10[MAXDIG + 2];


i64 count(int D)
{
    i64 ans = 0;
    for (int i = len - 1, c = 0; i >= 0; --i, ++c) {
        int d = S[c] - '0';

        if (len > 1 && D == 0 && c == 0) {
            ans += occ[i] * (d - 1);
            ans += oc0[i];
            continue;
        }

        ans += occ[i] * d;

        if (d > D)
            ans += p10[i];
        else if (d == D)
            ans += suf[i] + 1;
    }
    return ans;
}

void count_digits(i64 N, i64 *cnt)
{
    sprintf(S, "%lld", N);
    len = strlen(S);

    for (int i = 1; i < len; ++i)
        suf[i] = N % p10[i];

    for (int i = 0; i < 10; ++i)
        cnt[i] = count(i);
}

void prepare()
{
    p10[0] = 1;
    for (int i = 1; i <= MAXDIG + 1; ++i)
        p10[i] = p10[i - 1] * 10;

    for (int i = 1; i < MAXDIG; ++i)
        occ[i] = p10[i - 1] + 10 * occ[i -1];

    oc0[1] = 1;
    for (int i = 2; i < MAXDIG; ++i)
        oc0[i] = oc0[i - 1] + 9*occ[i - 1];
}

int main()
{
    prepare();
    while (true) {
        scanf("%d%d",&A, &B);
        if (A == 0) break;

        count_digits(A - 1, cnt1);
        count_digits(B, cnt2);

        for (int i = 0; i < 10; ++i) {
            if (i > 0) putchar(' ');
            printf("%lld", cnt2[i] - cnt1[i]);
        }
        putchar('\n');
    }

    return 0;
}
