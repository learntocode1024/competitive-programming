#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1e5+5, M = 1e6+6;
int tot;
pii o[M];
vector<int> g[N];
int n;

void dfs(int u, int fa, int t) {
  o[++tot] = {u,t};
  int lim = g[u].size();
  chkmax(lim, t);
  for (auto v : g[u]) if (v != fa) {
    if (t == lim) {
      t -= g[u].size();
      o[++tot] = {u,t};
    }
    ++t;
    dfs(v, u, t);
    o[++tot] = {u,t};
  }
    if (t == lim) {
      t -= g[u].size();
      o[++tot] = {u,t};
    }
}

inline void solve() {
  rd(n);
  FOR(i,1,n-1) {
    int u, v;
    rd(u,v);
    g[u].pb(v);
    g[v].pb(u);
  }
  o[++tot] = {1,0};
  int d = 0;
  for (auto u : g[1]) {
    dfs(u, 1, ++d);
    o[++tot] = {1,d};
  }
  O(tot);
  FOR(i,1,tot) O(o[i].fi, o[i].se);
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

