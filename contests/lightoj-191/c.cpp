#include <cmath>
#include <cstdio>

#define EPS    (1e-9)
#define MAXLEN 7

#define ICE    0
#define WATER  1
#define VAPOUR 2

const double SI = 2100.0;
const double SW = 4200.0;
const double SV = 2000.0;

const double LF = 336000.0;
const double LV = 2286000.0;

double m, t1, t2;
char w1[MAXLEN + 1];
char w2[MAXLEN + 1];

int from, to;

bool eps_less(double a, double b) { return b - a > EPS; }
bool eps_equal(double a, double b) { return fabs(a - b) < EPS; }

double state_no_change(double m, double s, double d)
{
    return m*s*d;
}

double state_change(double m, double l)
{
    return m*l;
}

double specific_heat(int state)
{
    if (state == ICE) return SI;
    if (state == WATER) return SW;
    return SV;
}

double heat()
{
    double Q = 0.0;

    if (from == ICE && (to == WATER || to == VAPOUR)) {
        if (eps_less(t1, 0.0)) {
            Q += state_no_change(m, SI, -t1);
            t1 = 0.0;
        }

        Q += state_change(m, LF);
        from = WATER;
    }

    if (from == WATER && to == VAPOUR) {
        if (eps_less(t1, 100.0)) {
            Q += state_no_change(m, SW, 100.0-t1);
            t1 = 100.0;
        }

        Q += state_change(m, LV);
        from = VAPOUR;
    }

    if (eps_less(t1, t2)) {
        double s = specific_heat(to);

        Q += state_no_change(m, s, t2-t1);
    }

    if (from == VAPOUR && (to == WATER || to == ICE)) {
        if (eps_less(100.0, t1)) {
            Q += state_no_change(m, SV, 100.0-t1);
            t1 = 100.0;
        }

        Q -= state_change(m, LV);
        from = WATER;
    }

    if (from == WATER && to == ICE) {
        if (eps_less(0.0, t1)) {
            Q += state_no_change(m, SW, -t1);
            t1 = 0.0;
        }

        Q -= state_change(m, LF);
        from = ICE;
    }

    if (eps_less(t2, t1)) {
        double s = specific_heat(to);
        Q += state_no_change(m, s, t2-t1);
    }

    return Q;
}

void assign_state(int &v, char c)
{
    switch (c) {
    case 'i':
        v = ICE;
        break;
    case 'w':
        v = WATER;
        break;
    case 'v':
        v = VAPOUR;
        break;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s%s%lf%lf%lf", w1, w2, &m, &t1, &t2);

        m /= 1000.0;

        assign_state(from, w1[0]);
        assign_state(to, w2[0]);

        printf("Experiment %d: ", ++ncase);

        double ans = heat();

        if (eps_equal(ans, 0.0))
            puts("No Change.");
        else {
            ans /= 1000.0;
            printf("%.2lf kJ heat is %s.\n", fabs(ans),
                   eps_less(0.0, ans) ? "absorbed" : "released");
        }
    }

    return 0;
}
