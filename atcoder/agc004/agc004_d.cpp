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

const int N = 1e5+5;
int ans;
int n, k;
vector<int> g[N];

int dfs(int u, int fa) {
  int d = 0;
  for (auto v : g[u])
    chkmax(d, dfs(v, u));
  ++d;
  if (d == k && fa != 1) {
    ++ans;
    d = 0;
  }
  return d;
}

inline void solve() {
  cin >> n >> k;
  int a;
  cin >> a;
  if (a != 1) ++ans;
  FOR(i, 2, n + 1) {
    cin >> a;
    g[a].pb(i);
  }
  dfs(1, 1);
  cout << ans << '\n';
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

