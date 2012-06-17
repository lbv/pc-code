class Util {
    // Permutations in lexicographic order
    boolean nextPermutation(char[] p, int n) {
        if (n < 2) return false;
        int i = n - 2;
        while (p[i] >= p[i + 1]) if (--i < 0) return false;
        int j = n - 1;
        while (p[j] <= p[i]) j--;
        _swap(p, i, j);
        for (i++, j=n-1; i < j; i++, j--) _swap(p, i, j);
        return true;
    }
    void _swap(char[] p, int a, int b) {
        char x = p[a];
        p[a] = p[b];
        p[b] = x;
    }
}
