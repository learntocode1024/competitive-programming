#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
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

#define MULTI
const int N = 300;
dbl f[N], g[N][N], p[N][N];
int d[N];
int n, r;

inline void solve() {
  rd(n, r);
  FOR(i, 1, n + 1) {
    rd(p[i][1], d[i]);
    p[i][0] = 1;
    p[i][1] = 1 - p[i][1];
    f[i] = 0;
  }
  FOR(i, 1, n + 1) FOR(j, 2, r + 1) {
    p[i][j] = p[i][j-1] * p[i][1];
  }
  g[0][0] = 1;
  FOR(i, 1, n + 1) FOR(j, 0, min(r, i) + 1) {
    g[i][j] = g[i-1][j] * p[i][r-j];
    if (j) {
      dbl cur = g[i-1][j-1] * (1-p[i][r-j+1]);
      g[i][j] += cur;
      f[i] += cur;
    }
  }
  dbl ans = 0;
  FOR(i, 1, n + 1) ans += d[i] * f[i];
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
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

