#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

const int N = 0;

i64 p3[40];
i64 ret[1005], tot;

void work(i64 n, int t) {
  // cerr << n << ' ' << t << '\n';
  if (n == 0) return;
  if (n & 1) {
    int i;
    for (i = 0; i < 39 && p3[i] <= n; ++i);
    ret[tot++] = (1ll << t) * p3[i - 1];
    work(n - p3[i - 1], t);
  } else {
    while (!(n & 1)) ++t, n >>= 1;
    work(n, t);
  }
}

inline void solve() {
  i64 n;
  cin >> n;
  p3[0] = 1;
  FOR(i, 1, 39) p3[i] = p3[i - 1] * 3;
  // cerr << (p3[1] <= 1) << '\n';
  work(n, 0);
  cout << tot << '\n';
  FOR(i, 0, tot) cout << ret[i] << ' ';
  cout << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

