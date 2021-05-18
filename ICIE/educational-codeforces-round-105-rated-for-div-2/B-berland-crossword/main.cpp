// Original Author: misaka18931
// Date: 03-02-21
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x)                                                             \
  T x;                                                                         \
  cin >> x;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES\n");                                                             \
  else                                                                         \
    printf("NO\n");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define max(X, Y) ((X) > (Y) ? (X) : (Y))
#define MX

int cnt[4];
int blk[4];

void solve() {
  int n;
  for (int i = 0; i < 4; ++i) {
    blk[i] = 1;
  }
  cin >> n;
  bool ans = 1;
  for (int i = 0; i < 4; ++i) {
    cin >> cnt[i];
    if (!cnt[i]) blk[i] = blk[(i + 1) % 4] = 0;
  }
  for (int i = 0; i < 4; ++i) {
    if (cnt[i] == 1 && blk[i] + blk[(i + 1) % 4] == 2) {
      if (cnt[(i + 3) % 4] >= cnt[(i + 1) % 4]) blk[(i + 1) % 4] = 0;
      else blk[i] = 0;
    }
  }
  for (int i = 0; i < 4; ++i) {
    if (cnt[i] > blk[i] + blk[(i + 1) % 4] + n - 2) ans = 0;
  }
  printb(ans)
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
