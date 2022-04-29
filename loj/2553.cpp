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
const int N = 3.7e5, B = 20;
vector<pii> g1[N], g2[N];
int n;
i64 ans = INT64_MIN;

struct O1LCA {
  vector<pii> *g;
  int dfn[N], rk[N<<1], e[B][N<<1], tot;
  i64 d[N];
  void dfs(int u, int fa) {
    dfn[u] = ++tot;
    rk[tot] = u;
    e[0][tot] = tot;
    for (auto v : g[u]) if (v.fi != fa) {
      d[v.fi] = d[u] + v.se;
      dfs(v.fi, u);
      e[0][++tot] = dfn[u];
    }
  }
  inline int lca(int u, int v) {
    u = dfn[u], v = dfn[v];
    if (u > v) swap(u,v);
    int t = 31 - __builtin_clz(v-u+1);
    return rk[min(e[t][u], e[t][v-(1<<t)+1])];
  }
  inline void build(vector<pii> *_g) {
    g = _g;
    dfs(1,1);
    FOR(i,1,B-1) FOR(j,1,tot-(1<<i)+1) {
      e[i][j] = min(e[i-1][j], e[i-1][j+(1<<(i-1))]);
    }
  }
  inline int operator() (const int &u, const int &v) {
    return lca(u,v);
  }
} d1, d2;

i64 w[N], ww[N];
struct virt_tree {
  vector<int> g[N];
  int n;
  int col[N];
  int a[N], b[N], s[N], tl;
  bool vis[N];
  i64 ans;
  int f[N][2];
  inline void add(int u, int _col) {
    a[n++] = u;
    vis[u] = 1;
    col[u] = _col;
    OO(u)
  }
  static bool cmp(int a, int b) {
    return d2.dfn[a] < d2.dfn[b];
  }
  inline void upd(int u, int v) {
    if (col[v] == col[f[u][0]]) {
      if (w[v] > w[f[u][0]]) f[u][0] = v;
      return;
    } else {
      if (w[v] > w[f[u][0]]) swap(f[u][0], v);
      if (w[v] >= w[f[u][1]]) swap(f[u][1], v);
    }
  }
  void dfs(int u) {
    f[u][0] = 0;
    f[u][1] = ::n+1;
    if (vis[u]) upd(u, u);
    for (auto v : g[u]) {
      dfs(v);
      FOR(i,0,1) FOR(j,0,1) {
        if (col[f[u][i]] != col[f[v][j]]) {
          chkmax(ans, w[f[u][i]] + w[f[v][j]] - 2*d2.d[u]);
#ifdef MISAKA
          O(f[u][i], f[v][j], (w[f[u][i]] + w[f[v][j]] - 2*d2.d[u])/2);
#endif
        }
      }
      upd(u, f[v][0]);
      upd(u, f[v][1]);
    }
  }
  inline i64 run() {
    ans = -1e18;
    w[0] = -1e18;
    w[::n+1] = -1e18;
    sort(a,a+n,cmp);
#ifdef MISAKA
    FOR(i,0,n-1) {
      O(a[i], w[a[i]], col[a[i]]);
    }
#endif
    int m = 1;
    b[0] = 1;
    s[1] = tl = 1;
    FOR(i,a[0] == 1,n-1) {
      int x = d2(s[tl], a[i]);
      if (x != s[tl]) {
        while (d2.dfn[x] < d2.dfn[s[tl]]) {
          int u = s[tl--];
          if (d2.dfn[s[tl]] < d2.dfn[x]) {
            s[++tl] = x;
            b[m++] = x;
          }
          g[s[tl]].pb(u);
        }
      }
      s[++tl] = a[i];
      b[m++] = a[i];
    }
    while (tl > 1) {
      g[s[tl-1]].pb(s[tl]);
      --tl;
    }
    dfs(1);
    FOR(i,0,n-1) vis[a[i]] = 0;
    FOR(i,0,m-1) g[b[i]].clear();
    n = 0;
    return ans;
  }
} T;

int sz[N];
bool vis[N];
int cent(int u, int fa) {
  sz[u] = 1;
  int ret = 0;
  bool ok = 1;
  for (auto v : g1[u]) if (!vis[v.fi] && v.fi != fa) {
    ret |= cent(v.fi, u);
    sz[u] += sz[v.fi];
    if (sz[v.fi] > sz[0]/2) ok = 0;
  }
  if ((sz[0]-sz[u]) > sz[0]/2) ok = 0;
  return ok ? u : ret;
}

int col;
void dfs(int u, int fa) {
  sz[u] = 1;
  T.add(u,col);
  w[u] = d1.d[u]+ww[u];
  for (auto v : g1[u]) if (!vis[v.fi] && v.fi != fa) {
    ww[v.fi] = ww[u] + v.se;
    dfs(v.fi, u);
    sz[u] += sz[v.fi];
  }
}

void work(int u) {
  vis[u] = 1;
  col = 1;
  OO(u)
  OO(d1.d[u])
  T.add(u,1);
  w[u] = d1.d[u];
  ww[u] = 0;
  for (auto v : g1[u]) if (!vis[v.fi]) {
    ++col;
    ww[v.fi] = v.se;
    dfs(v.fi,u);
  }
  chkmax(ans, T.run());
  for (auto v : g1[u]) if (!vis[v.fi]) {
    sz[0] = sz[v.fi];
    int to = cent(v.fi, u);
    work(to);
  }
}

inline void solve() {
  rd(n);
  FOR(i,2,n) {
    int u, v, w;
    rd(u,v,w);
    g1[u].eb(v,w);
    g1[v].eb(u,w);
  }
  FOR(i,2,n) {
    int u, v, w;
    rd(u,v,w);
    g2[u].eb(v,w);
    g2[v].eb(u,w);
  }
  d1.build(g1);
  d2.build(g2);
  sz[0] = n;
  int rt = cent(1,1);
  work(rt);
  ans /= 2;
  FOR(i,1,n) {
    chkmax(ans, d1.d[i]-d2.d[i]);
  }
  O(ans);
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

