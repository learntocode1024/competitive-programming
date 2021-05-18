// Original Author: misaka18931
// Date: 03-03-21
// tag:
// 

#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define init(T, x) \
  T x; \
  cin >> x;
#define printb(x) \
  if ((bool)x) printf("YES"); \
  else printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 100005

LL x[MX], y[MX];
int totx, toty;

void solve() {
  int n;
  totx = toty = 0;
  cin >> n;
  LL tmp1, tmp2;
  for (int i = 0; i < 2 * n; ++i) {
    cin >> tmp1 >> tmp2;
    if (!tmp1) y[toty++] = abs(tmp2);
    else x[totx++] = abs(tmp1);
  }
  sort(x, x + n);
  sort(y, y + n);
  double ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += sqrt((double) x[i] * x[i] + y[i] * y[i]);
  }
  cout << fixed << std::setprecision(15) << ans << endl;
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
