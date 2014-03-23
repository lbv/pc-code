#include <cmath>
#include <cstdio>
#include <cstring>


#define EPS (1e-6)


char out_ok[256] = "data.out";
char out_ch[256] = "data.tmp";

FILE *f_ok;
FILE *f_ch;

int retval;

void check()
{
    int ncase1, ncase2;
    double res1, res2;

    while (true) {
        if (fscanf(f_ok, "Case %d: %lf ", &ncase1, &res1) != 2) break;

        printf("Checking case %d .. ", ncase1);

        if (fscanf(f_ch, "Case %d: %lf ", &ncase2, &res2) != 2) {
            printf("Error reading data for case %d\n", ncase1);
            retval = 1;
            return;
        }

        if (fabs(res1 - res2) > EPS) {
            printf("error (expected %.8lf, got %.8lf)\n", res1, res2);
            retval = 1;
            continue;
        }

        printf("OK\n");
    }
}

int main()
{
    f_ok = fopen(out_ok, "r");
    f_ch = fopen(out_ch, "r");

    if (f_ok == NULL || f_ch == NULL) {
        fprintf(stderr, "Couldn't open %s or %s\n", out_ok, out_ch);
        return 1;
    }

    check();

    fclose(f_ok);
    fclose(f_ch);

    return retval;
}
