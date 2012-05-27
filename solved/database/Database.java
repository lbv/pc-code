import java.util.*;

public class Database {
    public static void main(String[] args) {
        new Database().run();
    }

    class TwoRows {
        int r1, r2;
        final int PRIME = 31;
        TwoRows(int R1, int R2) { r1=R1; r2=R2; }
        public boolean equals(Object obj) {
            TwoRows o = obj != null ? (TwoRows)obj : null;
            return o != null && r1==o.r1 && r2==o.r2;
        }
        public int hashCode() {
            int res = 1;
            res = (res * PRIME) + r1;
            res = (res * PRIME) + r2;
            return res;
        }
    }
    class RowSet extends HashSet<Integer> {}
    class ColRowsMap extends HashMap<Integer, RowSet> {}
    class WordMap extends HashMap<String, ColRowsMap> {
        RowSet find(String str, int col) {
            if (!containsKey(str)) return null;
            ColRowsMap crMap = get(str);
            if (!crMap.containsKey(col)) return null;
            return crMap.get(col);
        }
        void add(String str, int col, int row) {
            ColRowsMap crMap = get(str);
            if (crMap == null) put(str, crMap = new ColRowsMap());
            RowSet rs = crMap.get(col);
            if (rs == null) crMap.put(col, rs = new RowSet());
            rs.add(row);
        }
    }
    class RowsColMatch extends HashMap<TwoRows, Integer> {}
    class DB {
        WordMap wmap;
        RowsColMatch matches;
        boolean error;
        int[] conflictRows, conflictCols;
        DB() {
            wmap = new WordMap();
            matches = new RowsColMatch();
            error = false;
            conflictRows = new int[2];
            conflictCols = new int[2];
        }
        void add(String str, int row, int col) {
            RowSet rs = wmap.find(str, col);
            if (rs != null) {
                for (int row0 : rs) {
                    TwoRows tr = new TwoRows(row0, row);
                    if (matches.containsKey(tr)) {
                        error = true;
                        conflictRows[0] = row0;
                        conflictRows[1] = row;
                        conflictCols[0] = matches.get(tr);
                        conflictCols[1] = col;
                        return;
                    }
                    matches.put(tr, col);
                }
            }
            wmap.add(str, col, row);
        }
    }

    Scanner scn;
    int n, m;
    void run() {
        scn = new Scanner(System.in);

        while (scn.hasNextInt()) {
            n = scn.nextInt();
            m = scn.nextInt();
            scn.nextLine();
            DB db = new DB();
            for (int i = 1; i <= n; i++) {
                String[] words = scn.nextLine().split(",");
                for (int j = 1; j <= m && !db.error; j++) {
                    db.add(words[j-1], i, j);
                }
            }
            if (db.error) {
                System.out.println("NO");
                System.out.println("" + db.conflictRows[0] + " " + db.conflictRows[1]);
                System.out.println("" + db.conflictCols[0] + " " + db.conflictCols[1]);
            }
            else
                System.out.println("YES");
        }
    }
}
