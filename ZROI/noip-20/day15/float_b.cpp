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
typedef long double f80;
const int N = 2e5+5;
int n, k;
int a[N];
f80 s[N];
int dp[N];

bool chk(f80 mid) {
  FOR(i, 1, n + 1) s[i] = s[i - 1] + a[i] - mid;
  FOR(i, 1, n + 1) {
    dp[i] = -1;
    for (int j = 0; j < i; ++j) {
      if (s[i] >= s[j] && dp[j] != -1) chkmax(dp[i], dp[j] + 1);
    }
  }
  //cerr << mid << ": " << dp[n] << '\n';
  return dp[n] >= k;
}

inline void solve() {
  cin >> n >> k;
  FOR(i, 1, n + 1) cin >> a[i];
  f80 l = 0, r = 1e4;
  FOR(i, 0, 30) {
    f80 mid = (l + r) / 2;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  cout << fixed << setprecision(4) << l << '\n';
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

