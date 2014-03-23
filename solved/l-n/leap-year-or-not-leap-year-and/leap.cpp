#include <cstdio>
#include <cstring>


#define MAXLEN (1<<20)


char num[MAXLEN];
int m4, m100, m400, m15, m55;


void process()
{
    int len = strlen(num);
    int p4, p100, p400, p15, p55;

    m4 = m100 = m400 = m15 = m55 = 0;
    p4 = p100 = p400 = p15 = p55 = 1;

    for (int i = len - 1; i >= 0; --i) {
        int d = num[i] - '0';

        m4   = (m4 + d * p4) % 4;
        m100 = (m100 + d * p100) % 100;
        m400 = (m400 + d * p400) % 400;
        m15  = (m15 + d * p15) % 15;
        m55  = (m55 + d * p55) % 55;

        p4   = p4 * 10 % 4;
        p100 = p100 * 10 % 100;
        p400 = p400 * 10 % 400;
        p15  = p15 * 10 % 15;
        p55  = p55 * 10 % 55;
    }
}

bool is_leap()
{
    return (m4 == 0 && m100 != 0) || m400 == 0;
}

bool is_huluculu()
{
    return m15 == 0;
}

bool is_bulukulu()
{
    return m55 == 0 && is_leap();
}

int main()
{
    bool first = true;
    while (true) {
        if (scanf("%s", num) != 1) break;
        process();

        if (first) first = false;
        else       putchar('\n');

        if (is_leap())
            puts("This is leap year.");
        if (is_huluculu())
            puts("This is huluculu festival year.");
        if (is_bulukulu())
            puts("This is bulukulu festival year.");
        if (! (is_leap() || is_huluculu() || is_bulukulu()))
            puts("This is an ordinary year.");
    }

    return 0;
}
