#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 5005;
const int p = 998244353;

inline void red(int &x) { if (x >= p) x -= p; }
int f[N], g[N][N];

void solve() {
  int n = rd(), m = rd();
  g[0][0] = 1;
  FOR(k, 1, n + 1) {
    FOR(s, k, n + 1) {
      f[s] = g[k - 1][s - k];
      if (k - m - 1 >= 0) red(f[s] += p - g[k - m - 1][s - k]);
      red(f[s] += f[s - k]);
    }
    cout << f[n] << '\n';
    FOR(i, 0, n + 1) red(g[k][i] = f[i] + g[k - 1][i]), f[i] = 0;
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
