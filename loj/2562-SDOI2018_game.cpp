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

#define MULTI
const int N = 2e5+5;
int n, m;
vector<int> g[N], G[N];
int low[N], dfn[N], tdfn, tot;
int s[N], t;

void dfs(int u, int fa) {
  low[u] = dfn[u] = ++tdfn;
  for (auto v : g[u]) if (v != fa) {
      if (!dfn[v]) {
        s[++t] = v;
        dfs(v, u);
        chkmin(low[u], low[v]);
        if (low[v] >= dfn[u] && (fa || g[u].size() > 1)) { // cut
          ++tot;
          G[tot].pb(u);
          G[u].pb(tot);
          int c;
          while (true) {
            c = s[t--];
            G[tot].pb(c);
            G[c].pb(tot);
            if (!t || c == v) break;
          }
        }
      } else chkmin(low[u], dfn[v]);
    }
}

int d[N], d0[N], f[18][N], rk[N], tot2;
void dfs1(int u, int fa) {
  rk[u] = ++tot2;
  d0[u] = d0[fa] + 1;
  d[u] = d[fa] + (u <= n);
  f[0][u] = fa;
  for (auto v : G[u]) if (v != fa) dfs1(v, u);
}
int lca(int a, int b) {
  if (d0[a] > d0[b]) swap(a, b);
  int x = d0[b] - d0[a];
  for (int i = 0; i < 18 && x; ++i, x >>= 1) if (x & 1) b = f[i][b];
  if (a == b) return a;
  ROF(i, 0, 18) if (f[i][a] != f[i][b]) a = f[i][a], b = f[i][b];
  return f[0][a];
}

inline void solve() {
  cin >> n >> m;
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  tot = n;
  s[t=1] = 1;
  dfs(1, 0); // BCC refactor tree
  dfs1(1, 0);
  FOR(i, 1, 18) FOR(j, 1, tot + 1) {
    f[i][j] = f[i-1][f[i-1][j]];
  }
  int q;
  cin >> q;
  FOR(i, 0, q) {
    int S;
    cin >> S;
    int ans = -S;
    FOR(i, 0, S) cin >> s[i], ans += d[s[i]];
    sort(s, s + S, [] (auto a, auto b) {
      return rk[a] < rk[b];
    });
    int x = s[0];
    FOR(i, 1, S) {
      x = lca(x, s[i]);
      ans -= d[lca(s[i-1], s[i])];
    }
    ans -= d[x];
    println(ans + (x <= n));
  }
  FOR(i, 1, n + 1) g[i].clear();
  FOR(i, 1, tot + 1) G[i].clear();
  FOR(i, 1, n + 1) dfn[i] = 0;
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
