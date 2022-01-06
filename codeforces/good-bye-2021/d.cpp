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

const int N = 5e4+5;
int a[N];
int n;
int dp[N][4], f[N];

inline void solve() {
  cin >> n;
  memset(dp, 0, sizeof(dp));
  memset(f, 0, sizeof(f));
  FOR(i, 1, n + 1) cin >> a[i];
  int x;
  cin >> x;
  FOR(i, 1, n + 1) a[i] -= x;
  int ans = 0;
  FOR(i, 1, n + 1) {
    chkmax(dp[i][0], 1);
    if (i > 2) chkmax(dp[i][0], f[i-3] + 1);
    if (i && a[i-1] + a[i] >= 0) chkmax(dp[i][1], max(dp[i-1][0], dp[i-1][2]) + 1);
    if (i > 1) chkmax(dp[i][2], f[i-2] + 1);
    if (i > 1 && a[i-1] + a[i] >= 0 && a[i-2] + a[i-1] + a[i] >= 0) chkmax(dp[i][3], max(dp[i-1][1], dp[i-1][3]) + 1);
    FOR(j, 0, 4) chkmax(ans, dp[i][j]);
    f[i] = ans;
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
  int T;
  cin >> T;
  while (T--)
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

