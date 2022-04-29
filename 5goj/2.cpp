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
const int N = 1005;
bool G[N][N];
vector<int> g[N];
int n, m;
int c0 = 0, c1 = 0;
bitset<N> s;
bool vis[N], c[N];

bool dfs(int u, bool col) {
  vis[u] = 1;
  if (col) ++c1;
  else ++c0;
  c[u] = col;
  for (auto v : g[u]) if (!vis[v]) {
    if (!dfs(v, !col)) return false;
  } else if (c[v] == col) return false;
  return true;
}

inline void solve() {
  rd(n, m);
  FOR(i,1,m) {
    int u, v;
    rd(u, v);
    G[u][v] = G[v][u] = 1;
  }
  FOR(i,1,n) FOR(j,1,n) if (i!=j) {
    if (!G[i][j]) g[i].pb(j); 
  }
  s.set(0);
  FOR(i,1,n) if (!vis[i]) {
    c0 = c1 = 0;
    if (!dfs(i, 0)) {
      O(-1);
      return;
    } else {
      s = (s << c1) | (s << c0);
    }
  }
  ROF(i,1,n/2) if (s[i]) {
    O(i);
    return;
  }
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

