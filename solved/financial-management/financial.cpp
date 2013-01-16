#include <cstdio>
#include <cstring>


#define EPS (1e-8)


char buf[1 << 20];


void print_num(double n)
{
    sprintf(buf, "%.2lf", n + EPS);
    int len = strlen(buf);

    if (len > 6) {
        for (int i = len, a = 0; a < 6; ++a, --i)
            buf[i] = buf[i - 1];
        buf[len + 1] = 0;
        buf[len - 6] = ',';
    }

    printf("%s\n", buf);
}

int main()
{
    int N;
    scanf("%d", &N);

    int ncase = 0;
    while (N--) {
        double sum = 0.0;
        for (int i = 0; i < 12; ++i) {
            double x;
            scanf("%lf", &x);
            sum += x;
        }

        printf("%d $", ++ncase);
        print_num(sum / 12.0);
    }

    return 0;
}
