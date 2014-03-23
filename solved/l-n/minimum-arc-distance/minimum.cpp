#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const double Pi2 = acos(0) * 4;

double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }

typedef double p_t;
struct Vector {
    p_t x, y;
    Vector(p_t X, p_t Y) : x(X), y(Y) {}
    double norm() { return sqrt(x*x + y*y); }
    double angle(const Vector &p) const {
        return circle_angle(atan2(p.y, p.x) - atan2(y, x));
    }
};

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int Ox, Oy, Ax, Ay, Bx, By;
        scanf("%d%d%d%d%d%d", &Ox, &Oy, &Ax, &Ay, &Bx, &By);

        Vector u(Ax - Ox, Ay - Oy);
        Vector v(Bx - Ox, By - Oy);

        double a = min(u.angle(v), v.angle(u));

        printf("Case %d: %.8lf\n", ++ncase, u.norm() * a);
    }

    return 0;
}
