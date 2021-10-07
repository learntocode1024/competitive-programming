#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 1e3+5;
int a[N];
i64 p;
i64 g[N], d[N];
i64 s2[N][N];

i64 q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

void solve() {
  int n = rd(), x = rd(), _p = rd(), m = rd();
  FOR(i, 0, m + 1) a[i] = rd();
  p = _p;
  d[0] = 1;
  FOR(i, 1, m + 1) d[i] = d[i - 1] * (n - i + 1) % p;
  FOR(i, 0, m + 1) g[i] = d[i] * q_pow(x, i) % p * q_pow(x + 1, n - i) % p;
  s2[0][0] = 1;
  FOR(i, 1, m + 1) FOR(j, 1, i + 1) s2[i][j] = (s2[i - 1][j - 1] + j * s2[i - 1][j]) % p;
  i64 ans = 0;
  FOR(j, 0, m + 1) FOR(i, 0, j + 1) ans = (ans + a[j] * s2[j][i] % p * g[i]) % p;
  cout << ans << '\n';
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
