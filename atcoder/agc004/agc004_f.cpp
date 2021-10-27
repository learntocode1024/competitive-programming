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
int n, m;
vector<int> g[N];
int ans;
int c[2], co[N];
bool vis[N];

void col(int u, int fa) {
  co[u] = co[fa] ^ 1;
  ++c[co[u]];
  vis[u] = 1;
  for (auto v : g[u])
    if (!vis[v]) col(v, u);
}

int dfs(int u, int fa) {
  int d = co[u] ? 1 : -1;
  for (auto v : g[u])
    if (v != fa && co[v] != co[u]) d += dfs(v, u);
  ans += abs(d);
  return d;
}

int stk[N], tot;
int r[N << 1], cnt, s[N << 1];
bool in[N];

bool cyc(int u, int fa) {
  stk[++tot] = u;
  in[u] = 1;
  for (auto v : g[u]) {
    if (v == fa) continue;
    if (in[v]) {
      while (stk[tot] != v) r[cnt++] = stk[tot--];
      r[cnt++] = v;
      return 1;
    } else {
      if (cyc(v, u)) return 1;
    }
  }
  in[u] = 0;
  --tot;
  return 0;
}

inline void solve() {
  cin >> n >> m;
  FOR(i, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
  if (n & 1) {
    cout << "-1\n";
  } else if (m == n - 1) {
    col(1, 0);
    if (c[0] != c[1]) {
      cout << "-1\n";
    } else {
      dfs(1, 0);
      cout << ans << '\n';
    }
  } else {
    cyc(1, 0);
    col(1, 0);
    if (cnt & 1) {
      if (abs(c[0] - c[1]) & 1) {
        cout << "-1\n";
      } else {
        dfs(1, 0);
        cout << ans + abs(c[0] - c[1]) / 2 << '\n';
      }
    } else {
      if (c[0] != c[1]) {
        cout << "-1\n";
      } else {
        throw "not Aval";
      }
    }
  }
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

