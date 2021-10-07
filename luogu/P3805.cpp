#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils"
#include "io"

const int N = 1.1e7+5;
char s[N];
int d1[N], d2[N];

void solve() {
  int n = IO::rdstr(s) - s;
  cerr << n << '\n';
  int ans = 0;
  for (int i = 0, l = 0, r = -1, k = 0; i < n; ++i) {
    k = (i < r) ? min(d1[l + r - i], r - i + 1) : 1;
    while (i >= k && i + k < n && s[i + k] == s[i - k]) ++k;
    d1[i] = k--;
    if (i + k > r) {
      r = i + k;
      l = i - k;
    }
    chkmax(ans, (d1[i] << 1) - 1);
  }
  for (int i = 0, l = 0, r = -1, k = 0; i < n; ++i) {
    k = (i <= r) ? min(d2[l + r - i + 1], r - i + 1) : 0;
    while (i >= k + 1 && i + k < n && s[i + k] == s[i - k - 1]) ++k;
    d2[i] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k;
    }
    chkmax(ans, d2[i] << 1);
  }
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
