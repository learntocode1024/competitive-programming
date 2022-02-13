#include "Memory2_lib.h"
#include <vector>
#include <iostream>
using std::cerr;
using std::endl;
using std::vector;

#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
int n;
//int cntt;
struct stat {
  int c, i, j;
  stat(int _i, int _j) {
    i = _i, j = _j, c = Flip(_i, _j);
    //++cntt;
    //cerr << "#" << cntt << ": (" << i << ' ' << j << ' ' << c << ')' << endl;
  }
  void ret() {
    //cerr << "!" << cntt << ": (" << i << ' ' << j << ' ' << c << ')' << endl;
    Answer(i, j, c);
  }
};
vector<stat> g[55];

int cur;
bool chk() {
  FOR(i, 0, n) if (g[i].size() == 2) {
    cur = i;
    return 1;
  }
  return 0;
}

void Solve(int T, int N) {
  n = N;
  FOR(i, 0, n) {
    stat c(i*2, i*2+1);
    g[c.c].pb(c);
  }
  while (chk()) {
    stat a = g[cur][0], b = g[cur][1];
    g[cur].clear();
    vector<stat> f;
    f.pb(stat(a.i, b.i));
    f.pb(stat(a.i, b.j));
    f.pb(stat(a.j, b.i));
    f.pb(stat(a.j, b.j));
    FOR(i, 0, 4) {
      if (f[i].c != cur) {
        g[f[i].c].pb(f[i]);
        f[3-i].ret();
        break;
      }
    }
  }
  FOR(i, 0, n) if (g[i].size() == 1) {
    g[i][0].ret();
  }
}
