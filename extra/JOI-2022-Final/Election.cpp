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

//#define MULTI
const int N = 505;
int n, K;
pii IN[N];
double a[N], b[N];
double f[N][N];

inline void solve() {
  rd(n, K);
  FOR(i, 1, n + 1) rd(IN[i].se, IN[i].fi);
  FOR(i, 1, n + 1) if (IN[i].fi == -1) IN[i].fi = 1e8;
  sort(IN + 1, IN + n + 1);
  FOR(i, 1, n + 1) a[i] = IN[i].se, b[i] = IN[i].fi;
  double ans = 1e8;
  FOR(m, 1, K + 1) {
    FOR(i, 0, n + 1) FOR(j, 0, n + 1) f[i][j] = 1e6;
    f[0][0] = 0;
    FOR(i, 0, n) FOR(j, 0, min(K - m + 1, i) + 1) {
      chkmin(f[i+1][j+1], f[i][j] + a[i+1]/m);
      int c = i - j;
      if (c >= m - 1) chkmin(f[i+1][j], f[i][j]);
      else chkmin(f[i+1][j], f[i][j] + b[i+1]/(c+1));
    }
    chkmin(ans, f[n][K - m + 1]);
  }
  println(ans);
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

