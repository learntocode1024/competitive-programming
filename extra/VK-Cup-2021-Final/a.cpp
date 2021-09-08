#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 300005;
int s[N], tot;
#define MULTI
 
void solve() {
  int a = rd(), b = rd();
  int n = a + b;
  tot = 0;
  int x = n / 2, y = n - x;
  int l, r;
  l = min(abs(x - a), abs(y - b));
  r = n - min(abs(n - a - x), abs(n - b - y));
  for (int i = l; i <= r; i += 2) s[tot++] = i;
  swap(x, y);
  l = min(abs(x - a), abs(y - b));
  r = n - min(abs(n - a - x), abs(n - b - y));
  for (int i = l; i <= r; i += 2) s[tot++] = i;
  sort(s, s + tot);
  tot = unique(s, s + tot) - s;
  cout << tot << '\n';
  for (int i = 0; i < tot; ++i) {
      cout << s[i] << ' ';
    }
    cout << '\n';
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
 