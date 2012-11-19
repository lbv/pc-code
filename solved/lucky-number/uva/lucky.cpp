#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 2000000
#define MAXLUCKY 2000000
const int MAXK = (MAXLUCKY + 1) / 2;


typedef vector<int> IV;
typedef IV::iterator IVi;


IV luckies;
bool lucky_map[MAXN + 1];


//
// Binary Search Tree
//
const int Nil = 0;
#define LT(t)  (T[T[t].l])
#define RT(t)  (T[T[t].r])
#define PAR(t) (T[T[t].p])
struct Bst {
    struct Node {
        int p, l, r, s, k;  // parent, left, right, size, key
        void init(int K) { k = K; p = l = r = Nil; s = 1; }
        void clear() { p = l = r = s = k = 0; }
    };
    int K[MAXK];
    Node T[MAXK + 1];
    int root, sz;
    int get(int t) { return K[T[t].k]; }
    int size() { return T[root].s; }
    void init(int n) { T[0].clear(); sz = 0; root = init_tree(0, n - 1); }
    int init_tree(int a, int b) {
        if (a > b) return Nil;
        int t = ++sz;
        if (a == b) { T[t].init(a); return t; }
        int m = (a + b) / 2;
        T[t].l = init_tree(a, m - 1);
        T[t].r = init_tree(m + 1, b);
        T[t].p = Nil, T[t].k = m, T[t].s = 1 + LT(t).s + RT(t).s;
        LT(t).p = t; RT(t).p = t;
        return t;
    }
    int find_kth(int k) { return find_kth_tree(k, root); }
    int find_kth_tree(int k, int t) {
        if (LT(t).s > k) return find_kth_tree(k, T[t].l);
        k -= LT(t).s;
        if (k == 0) return t;
        if (--k >= RT(t).s) return Nil;
        return find_kth_tree(k, T[t].r);
    }
    void remove(int t) {
        int x;
        if (T[t].l != Nil && T[t].r != Nil) {
            if (RT(t).s >= LT(t).s) for (x=T[t].r; T[x].l != Nil; x=T[x].l) ;
            else                    for (x=T[t].l; T[x].r != Nil; x=T[x].r) ;
            T[t].k = T[x].k;
            t = x;
        }
        if (T[t].l == Nil && T[t].r == Nil) {
            if (T[t].p == Nil) { root = Nil; return; }
            if (PAR(t).l == t) PAR(t).l = Nil;
            else               PAR(t).r = Nil;
        }
        else {
            x = T[t].l != Nil ? T[t].l : T[t].r;
            if (T[t].p == Nil) { T[root = x].p = Nil; return; }
            if (PAR(t).l == t) PAR(t).l = x;
            else               PAR(t).r = x;
            T[x].p = T[t].p;
        }
        for (x = T[t].p; x != Nil; x = T[x].p) --T[x].s;
    }
    void inorder(int t) {
        if (T[t].l != Nil) inorder(T[t].l);
        int lucky = K[T[t].k];
        luckies.push_back(lucky);
        lucky_map[lucky] = true;
        if (T[t].r != Nil) inorder(T[t].r);
    }
};


int n, L1, L2;
Bst tree;


void prepare()
{
    int N = 0;
    for (int i = 1; i <= MAXLUCKY; i += 2)
        tree.K[N++] = i;

    tree.init(N);

    for (int i = 1; ; ++i) {
        int t = tree.find_kth(i);
        if (t == Nil) break;

        int mul = tree.get(t);
        if (mul > tree.size()) break;

        for (int j = mul * (tree.size() / mul); j > 0; j -= mul)
            tree.remove(tree.find_kth(j - 1));
    }

    tree.inorder(tree.root);
}

bool solve()
{
    if (n % 2 != 0) return false;
    IVi it = lower_bound(luckies.begin(), luckies.end(), n/2);

    while (it != luckies.end() && *it < n) {
        if (lucky_map[n - *it]) {
            L2 = *it;
            L1 = n - L2;
            return true;
        }
        ++it;
    }
    return false;
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &n) != 1) break;
        if (solve())
            printf("%d is the sum of %d and %d.\n", n, L1, L2);
        else
            printf("%d is not the sum of two luckies!\n", n);

    }

    return 0;
}
