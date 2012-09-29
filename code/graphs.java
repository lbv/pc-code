public class TestGraphs {
        // Auxiliary types/attr
        class EQ extends ArrayDeque<E> {}
        IQ vq; boolean[] col; int[] dis, glow, gidx; int gcnt;

        // Euler trails
        IL _trail; EQ[] _adjq;
        IL eulerTrail() {
            _adjq = new EQ[n];
            int nOdd = 0, start = 0;
            for (int u = 0; u < n; u++) {
                _adjq[u] = new EQ();
                if (start == 0 && out[u] > 0) start = u;
                for (int i = 0; i < out[u]; i++)
                    _adjq[u].add(edge(u, i));
            }
            for (int v = 0; v < n; v++) {
                int diff = Math.abs(in[v] - out[v]);
                if (diff > 1) return null;
                if (diff == 1) {
                    if (++nOdd > 2) return null;
                    if (out[v] > in[v]) start = v;
                }
            }
            _trail = new IL();
            eulerBuildTrail(start);
            Collections.reverse(_trail);
            return _trail;
        }
        void eulerBuildTrail(int u) {
            while(! _adjq[u].isEmpty()) {
                E e = _adjq[u].remove();
                eulerBuildTrail(e.v);
            }
            _trail.add(u);
        }
    }
}
