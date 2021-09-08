#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 100005;
#define MULTI
int a[N];
int ans[N], tot;
 
inline void rev(int p) {
  reverse(a + 1, a + p + 1);
  ans[tot++] = p;
}
 
void solve() {
  int n = rd();
  tot = 0;
  FOR(i, 1, n + 1) a[i] = rd();
  FOR(i, 1, n + 1) if (abs(a[i] - i) & 1) {
    puts("-1");
    return;
  }
  for(int i = n; i > 1; i -= 2) {
    int p1 = 0, p2 = 0;
    for (; a[p1] != i; ++p1);
    for (; a[p2] != i - 1; ++p2);
    if (p1 == i && p2 == i - 1) {
      continue;
    } else if (p1 == 1 && p2 == 2) {
      rev(i);
    } else if (p1 == p2 + 1) {
      rev(p1);
      rev(i);
    } else if (p2 == p1 + 1) {
      rev(p2 + 1);
      rev(3);
      rev(i);
    } else if (p2 > p1) {
      rev(p1);
      rev(p2 - 1);
      rev(p2 + 1);
      rev(3);
      rev(i);
    } else {
      rev(p1);
      p2 = 1 + (p1 - p2);
      rev(p2 - 1);
      rev(p2 + 1);
      rev(3);
      rev(i);
    }
  }
  cout << tot << '\n';
  for (int i = 0; i < tot; ++i) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
 
int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve();
#else
  solve();
#endif
  return 0;
}