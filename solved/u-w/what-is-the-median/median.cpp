#include <cstdio>
#include <set>
using namespace std;


struct Node {
    int x;  // value
    int s;  // serial number, to guarantee unambiguous order
    Node(int X, int S) : x(X), s(S) {}
    bool operator<(const Node &y) const {
        if (x != y.x) return x < y.x;
        return s < y.s;
    }
};

typedef multiset<Node> NS;

typedef NS::iterator NSi;


NS ns;
NSi i;
int X;
int n;


int main()
{
    if (scanf("%d", &X) != 1) return 0;

    ns.insert(Node(X, 0));
    i = ns.begin();
    n = 1;
    printf("%d\n", X);


    while (true) {
        if (scanf("%d", &X) != 1) break;

        ns.insert(Node(X, n));
        if (n % 2 == 0 && X > i->x)
            ++i;
        else if (n % 2 != 0 && X < i->x)
            --i;

        ++n;

        int median = i->x;
        if (n % 2 == 0) {
            NSi j = i;
            ++j;
            median = (median + j->x) / 2;
        }

        printf("%d\n", median);
    }

    return 0;
}
