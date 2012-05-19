#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

vector<pair<int, bool> > implications[30][2];  // T = w, F = h
int val[30], val2[30];

bool doit(int n, int v) {
  if (val[n] != -1) return val[n] == v;
  val[n] = v;
  vector<pair<int, bool> >& imp = implications[n][v];
  for (int i = 0; i < imp.size(); i++)
    if (!doit(imp[i].first, imp[i].second)) return false;
  return true;
}

main() {
  int N, M;
  while (cin >> N >> M && N) {
    for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
      implications[i][j].clear();
    for (int i = 0; i < M; i++) {
      char a, b;
      int an, bn;
      cin >> an >> a >> bn >> b;
      implications[an][a=='h'].push_back(make_pair(bn, b=='w'));
      implications[bn][b=='h'].push_back(make_pair(an, a=='w'));
    }
    memset(val, -1, sizeof(val));
    if (!doit(0, 1)) goto fail;
    for (int i = 0; i < N; i++) if (val[i] == -1) {
      memcpy(val2, val, sizeof(val));
      if (!doit(i, 0)) {
        memcpy(val, val2, sizeof(val));
        if (!doit(i, 1)) goto fail;
      }
    }
    for (int i = 1; i < N; i++) {
      if (i > 1) cout << ' ';
      cout << i << (val[i] ? 'w' : 'h');
    }
    cout << endl;
    continue;
fail:
    cout << "bad luck" << endl;
  }
}
