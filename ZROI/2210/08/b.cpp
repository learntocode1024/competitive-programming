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
const int N = 3005, W = 12;
int p[N];
int n, m;
int dfn[N], tt;
vector<int> g[N];
struct O1LCA {
  int e[W][N<<1];
  int rk[N<<1], pos[N], tot;
  void dfs(int u, int fa) {
    dfn[u] = ++tt;
    pos[u] = ++tot;
    rk[tot] = u;
    e[0][tot] = tot;
    for (auto v : g[u]) if (v != fa) {
      dfs(v, u);
      e[0][++tot] = pos[u];
    }
  }
  inline void build() {
    dfs(p[1], 0);
    FOR(i, 1, W) {
      FOR(j, 1, tot + 1 - (1<<i)) {
        e[i][j] = min(e[i-1][j], e[i-1][j+(1<<(i-1))]);
      }
    }
  }
  inline int lca(int u, int v) {
    u = pos[u], v = pos[v];
    if (u > v) swap(u, v);
    int t = 31 - __builtin_clz(v - u + 1);
    int x = min(e[t][u], e[t][v-(1<<t)+1]);
    return rk[x];
  }
  inline int operator() (int u, int v) {
    if (!u || !v) return u | v;
    return lca(u,v);
  }
} a;



int s[N][N];
int mn[N][N], mx[N][N];

inline void solve() {
  rd(n,m);
  FOR(i,1,n) rd(p[i]);
  FOR(i,2,n) {
    int fa;
    rd(fa);
    g[p[fa]].pb(p[i]);
    g[p[i]].pb(p[fa]);
  }
  a.build();
  FOR(i,1,n) {
    mn[i][i] = mx[i][i] = i;
    ROF(j, 1, i-1) {
      mn[j][i] = min(mn[j+1][i], a(j,i));
      mx[j][i] = max(mx[j+1][i], a(j,i));
    }
  }
  FOR(i,1,n) {
    int l = i, r = i;
    s[i][i] = 1;
    FOR(j, i+1, n) {
      chkmin(l, mn[i][j]);
      chkmax(r, mx[i][j]);
      if (l==i&&r==j) s[i][j] = 1;
      s[i][j] += s[i][j-1];
    }
  }
  FOR(i,1,m) {
    int l, r;
    rd(l,r);
    int ans = 0;
    FOR(i,l,r) ans += s[i][r];
    O(ans);
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

