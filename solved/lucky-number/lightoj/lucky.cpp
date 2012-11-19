#include <cstdio>
#include <cstring>


#define MAXN 100000
#define MAXLUCKY 1429431
const int MAXK = (MAXLUCKY + 1) / 2;

#define Zero(v) memset((v), 0, sizeof(v))
#define GetFS(b) ((b) & -(b))


int lucky[MAXN + 1];
int lucky_term;


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
        lucky[lucky_term++] = K[T[t].k];
        if (T[t].r != Nil) inorder(T[t].r);
    }
};


int n;
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
        for (int j = mul * (tree.size() / mul); j > 0; j -= mul)
            tree.remove(tree.find_kth(j - 1));
    }

    lucky_term = 1;
    tree.inorder(tree.root);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);
        printf("Case %d: %d\n", ++ncase, lucky[n]);
    }

    return 0;
}
