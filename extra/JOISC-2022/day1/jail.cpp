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

#define MULTI
const int N = 1.2e5+5, W = 17;
vector<int> g[N], G[N*W*2];
int d[N*W*2];
int n, tot;
int f[W][N], fs[W][N], ft[W][N];
int dep[N];

void dfs(int u, int fa) { dep[u] = dep[fa] + 1, f[0][u] = fa; for (auto v : g[u]) if (v != fa) dfs(v,u); }

int s[N], t[N];

inline int Merge(int x, int y, bool ty) {
  if (!x || !y) return x | y;
  ++tot;
  if (!ty) {
    G[x].pb(tot);
    G[y].pb(tot);
    d[tot] += 2;
  } else {
    G[tot].pb(x);
    G[tot].pb(y);
    ++d[x];
    ++d[y];
  }
  return tot;
}

inline void add(int x, int y) {
  if (!y || !x) return;
  G[x].pb(y);
  ++d[y];
}

int qu[W*N*2], hd, tl;

bool topo() {
  int cnt = 0;
  hd = 1;
  tl = 0;
  FOR(i,1,tot) if (d[i]) {
    ++cnt;
  } else qu[++tl] = i;
  while (hd <= tl) {
    int u = qu[hd++];
    for (auto v : G[u]) {
      --d[v];
      if (!d[v]) qu[++tl] = v, --cnt;
    }
  }
  return cnt == 0;
}

inline void solve() {
  FOR(i,1,tot) G[i].clear(), d[i] = 0;
  FOR(i,1,n) g[i].clear(), fs[0][i] = ft[0][i] = f[0][i] = 0;
  rd(n);
  FOR(i,2,n) {
    int u, v;
    rd(u,v);
    g[u].pb(v);
    g[v].pb(u);
  }
  int m;
  rd(m);
  tot = m;
  FOR(i,1,m) {
    rd(s[i], t[i]);
    fs[0][s[i]] = i;
    ft[0][t[i]] = i;
  }
  dfs(1,0);
  FOR(i,1,W-1) FOR(j,1,n) {
    f[i][j] = f[i-1][f[i-1][j]];
    fs[i][j] = Merge(fs[i-1][j], fs[i-1][f[i-1][j]], 0);
    ft[i][j] = Merge(ft[i-1][j], ft[i-1][f[i-1][j]], 1);
  }
  FOR(c,1,m) {
    int u = s[c], v = t[c];
    add(c,ft[0][u]);
    add(fs[0][v],c);
    if (f[0][s[c]] == t[c] || f[0][t[c]] == s[c]) continue;
    if (dep[u] < dep[v]) swap(u, v);
    u = f[0][u];
    if (dep[u] < dep[v]) {
      v = f[0][v];
      if (u == v) {
        add(fs[0][u], c);
        add(c, ft[0][u]);
        continue;
      }
    } else {
      int dif = dep[u] - dep[v];
      FOR(i,0,W-1) if ((dif >> i) & 1) {
        add(fs[i][u], c);
        add(c, ft[i][u]);
        u = f[i][u];
      }
      if (u == v) continue;
      else {
        add(fs[0][u], c);
        add(c, ft[0][u]);
        u = f[0][u];
        v = f[0][v];
      }
    }
    ROF(i,0,W-1) if (f[i][u] != f[i][v]) {
      add(fs[i][u], c);
      add(c, ft[i][u]);
      add(fs[i][v], c);
      add(c, ft[i][v]);
      u = f[i][u];
      v = f[i][v];
    }
    if (u != v) {
      add(fs[0][u], c);
      add(c, ft[0][u]);
      add(fs[0][v], c);
      add(c, ft[0][v]);
      u = f[0][u];
    }
    add(fs[0][u], c);
    add(c, ft[0][u]);
  }
  O(topo()?"Yes":"No");
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

