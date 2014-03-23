#include <cstdio>

// A[i] has the accumulated number of days from months previous to i
const int A[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

// same as A, but for a leap year
const int B[13] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };


// returns number of leap years up to, and including, y
int leap_years(int y)
{
    return y / 4 - y / 100 + y / 400;
}

bool is_leap(int y)
{
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

// number of days in blocks of years
const int p400 = 400*365 + leap_years(400);
const int p100 = 100*365 + leap_years(100);
const int p4   = 4*365 + 1;
const int p1   = 365;

int date_to_days(int d, int m, int y)
{
    int res = (y - 1) * 365;

    res += leap_years(y - 1);
    res += is_leap(y) ? B[m] : A[m];
    res += d;

    return res;
}

void days_to_date(int days, int &d, int &m, int &y)
{
    int r;        // remainder of days
    bool top100;  // are we in the top 100 years of a 400 block?
    bool top4;    // are we in the top 4 years of a 100 block?
    bool top1;    // are we in the top year of a 4 block?

    y = 1;
    top100 = top4 = top1 = false;

    y += ((days-1) / p400) * 400;
    r = (days-1) % p400 + 1;

    if (r > p100*3) {
        top100 = true;
        r -= 3*p100;
        y += 300;
    }
    else {
        y += ((r-1) / p100) * 100;
        r = (r-1) % p100 + 1;
    }

    if (r > p4*24) {
        top4 = true;
        r -= 24*p4;
        y += 24*4;
    }
    else {
        y += ((r-1) / p4) * 4;
        r = (r-1) % p4 + 1;
    }

    if (r > p1*3) {
        top1 = true;
        r -= p1*3;
        y += 3;
    }
    else {
        y += (r-1) / p1;
        r = (r-1) % p1 + 1;
    }

    const int *ac = top1 && (!top4 || top100) ? B : A;

    d = r;
    for (m = 1; m < 12; ++m)
        if (d <=  ac[m + 1]) break;

    d -= ac[m];
}

int main()
{
    int days, d, m, y;

    while (true) {
        scanf("%d%d%d%d", &days, &d, &m, &y);
        if (y == 0) break;

        int x = date_to_days(d, m, y);
        days_to_date(x + days, d, m, y);

        printf("%d %d %d\n", d, m, y);
    }

    return 0;
}
