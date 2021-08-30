#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

int n;
char s[20005];
#define MULTI

void solve() {
  n = rd();
  rdstr(s + 1);
  int m1 = n / 2;
  int m2 = m1 + 1 + (n & 1);
  FOR(i, 1, n + 1) {
    if (s[i] == '0') {
      if (i <= m1) {
        printf("%d %d %d %d\n", i, n, i + 1, n);
        return;
      }
      if (i >= m2) {
        printf("%d %d %d %d\n", 1, i, 1, i - 1);
        return;
      }
    }
  }
  printf("%d %d %d %d\n", 1, m1, m2, n);
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
