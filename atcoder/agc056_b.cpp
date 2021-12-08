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

const int N = 305;
const int p = 998244353;
int dp[N][N];
int vis[N][N][N];
pii a[N];
int n, m;

int run(int l, int r) {
  if (dp[l][r] != -1) return dp[l][r];
  if (l > r) return 1;
  if (r == l) return dp[l][r] = 1;
  int ans = 0;
  int cnt = 0;
  FOR(i, 0, m) {if (a[i].fi >= l && a[i].se <= r) {++cnt; FOR(j, a[i].fi + 1, a[i].se + 1) {
    ++vis[l][r][j];
  }
  }
  }
  FOR(i, l, r + 1) if (!cnt || vis[l][r][i] != cnt) {
    ans = (ans + 1ll * run(l, i - 1) * run(i + 1, r)) % p;
  }
  return dp[l][r] = ans;
}

inline void solve() {
  memset(dp, 0xff, sizeof(dp));
  cin >> n >> m;
  FOR(i, 0, m) cin >> a[i].fi >> a[i].se;
  // sort(a, a + m);
  run(1, n);
  cout << dp[1][n] << '\n';
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

