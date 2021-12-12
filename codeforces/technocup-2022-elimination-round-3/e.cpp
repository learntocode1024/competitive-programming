#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

const int N = 1e6+5;
int n, q;
vector<int> h[N], g[N];
int L[N], K[N];
int a[N], d[N], ans[N], dd[N];
using namespace __gnu_pbds;
tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> S;

void dfs(int u) {
  if (d[a[u]]) S.erase({d[a[u]], dd[a[u]]});
  ++d[a[u]];
  int mem = dd[a[u]];
  dd[a[u]] = u;
  S.insert({d[a[u]], u});
  for (auto id : h[u]) {
    int t = S.order_of_key({L[id], 0});
    if (t + K[id] > S.size()) ans[id] = -1;
    else {
      ans[id] = a[S.find_by_order(t + K[id] - 1)->se];
    }
  }
  for (auto v : g[u]) {
    dfs(v);
  }
  S.erase({d[a[u]], u});
  --d[a[u]];
  dd[a[u]] = mem;
  if (d[a[u]]) S.insert({d[a[u]], mem});
}

inline void solve() {
  rd(n, q);
  FOR(i, 1, n + 1) g[i].clear(), h[i].clear();
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 2, n + 1) {
    int p;
    cin >> p;
    g[p].pb(i);
  }
  FOR(i, 0, q) {
    int v;
    rd(v, L[i], K[i]);
    h[v].pb(i);
  }
  dfs(1);
  FOR(i, 0, q) cout << ans[i] << " \n"[i == q-1];
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

