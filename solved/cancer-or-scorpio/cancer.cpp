#include <cstdio>

//
// Time - Leap years
//
// A[i] has the accumulated number of days from months previous to i
const int A[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
// same as A, but for a leap year
const int B[13] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
// returns number of leap years up to, and including, y
int leap_years(int y) { return y / 4 - y / 100 + y / 400; }
bool is_leap(int y) { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }
// number of days in blocks of years
const int p400 = 400*365 + leap_years(400);
const int p100 = 100*365 + leap_years(100);
const int p4   = 4*365 + 1;
const int p1   = 365;
int date_to_days(int d, int m, int y)
{
    return (y - 1) * 365 + leap_years(y - 1) + (is_leap(y) ? B[m] : A[m]) + d;
}
void days_to_date(int days, int &d, int &m, int &y)
{
    bool top100;  // are we in the top 100 years of a 400 block?
    bool top4;    // are we in the top 4 years of a 100 block?
    bool top1;    // are we in the top year of a 4 block?

    y = 1;
    top100 = top4 = top1 = false;

    y += ((days-1) / p400) * 400;
    d = (days-1) % p400 + 1;

    if (d > p100*3) top100 = true, d -= 3*p100, y += 300;
    else y += ((d-1) / p100) * 100, d = (d-1) % p100 + 1;

    if (d > p4*24) top4 = true, d -= 24*p4, y += 24*4;
    else y += ((d-1) / p4) * 4, d = (d-1) % p4 + 1;

    if (d > p1*3) top1 = true, d -= p1*3, y += 3;
    else y += (d-1) / p1, d = (d-1) % p1 + 1;

    const int *ac = top1 && (!top4 || top100) ? B : A;
    for (m = 1; m < 12; ++m) if (d <=  ac[m + 1]) break;
    d -= ac[m];
}

int date;
int M, D, Y;

void print_sign()
{
    if ((M == 1 && D >= 21) ||
        (M == 2 && D <= 19)) { puts("aquarius"); return; }

    if (M == 2 || (M == 3 && D <= 20)) { puts("pisces"); return; }
    if (M == 3 || (M == 4 && D <= 20)) { puts("aries"); return; }
    if (M == 4 || (M == 5 && D <= 21)) { puts("taurus"); return; }
    if (M == 5 || (M == 6 && D <= 21)) { puts("gemini"); return; }
    if (M == 6 || (M == 7 && D <= 22)) { puts("cancer"); return; }
    if (M == 7 || (M == 8 && D <= 21)) { puts("leo"); return; }
    if (M == 8 || (M == 9 && D <= 23)) { puts("virgo"); return; }
    if (M == 9 || (M == 10 && D <= 23)) { puts("libra"); return; }
    if (M == 10 || (M == 11 && D <= 22)) { puts("scorpio"); return; }
    if (M == 11 || (M == 12 && D <= 22)) { puts("sagittarius"); return; }

    puts("capricorn");
}

int main()
{
    int N;
    scanf("%d", &N);

    int ncase = 0;
    while (N--) {
        scanf("%d", &date);
        Y = date % 10000;
        date /= 10000;
        D = date % 100;
        date /= 100;
        M = date;

        int x = date_to_days(D, M, Y);
        days_to_date(x + 40*7, D, M, Y);

        printf("%d %02d/%02d/%04d ", ++ncase, M, D, Y);
        print_sign();
    }

    return 0;
}
