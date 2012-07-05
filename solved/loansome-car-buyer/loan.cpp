#include <cstdio>

#define MAXMONTHS 100

int    M;  // duration in months of the loan
double D;  // down payment
double L;  // amount of the loan
int    R;  // number of depreciation records

// depreciation records for each month
double rec[MAXMONTHS + 1];

int solve()
{
    double V = D + L;  // car's value
    double debt = L;
    double payment = L / M;

    for (int m = 0; m <= M; ++m) {
        V *= (1.0 - rec[m]);

        if (debt < V) return m;

        debt -= payment;
    }

    return M;
}

int main()
{
    while (true) {
        scanf("%d%lf%lf%d", &M, &D, &L, &R);
        if (M < 0) break;

        int    pre_m = 0;
        double pre_d = 0.0;

        while (R--) {
            int m;
            double dep;
            scanf("%d%lf", &m, &dep);

            for (int i = pre_m + 1; i < m; ++i)
                rec[i] = pre_d;

            rec[m] = dep;
            pre_m = m;
            pre_d = dep;
        }

        for (int i = pre_m + 1; i <= M; ++i)
            rec[i] = pre_d;

        int ans = solve();
        if (ans == 1)
            puts("1 month");
        else
            printf("%d months\n", ans);
    }

    return 0;
}
