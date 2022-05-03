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
const int N = 305, M = N*N/2;
struct E {
  int u, v, w;
  bool operator< (const E& b) const {
    return w < b.w;
  }
  inline void rd() {
    ::rd(u,v,w);
  }
} e[M], ee[N];
bool ex[N];
int n, m, k;

struct dsu {
  int f[N];
  int get(int x) { return x == f[x] ? x : f[x] = get(f[x]); };
  bool operator() (int x, int y) {
    if (get(x) == get(y)) return 0;
    f[f[x]] = f[y];
    return 1;
  }
} U;

vector<int> to[N], fr[N], g[N];
bool vis[N], vscol[N];
int cur[N], ccl[N], col[N], tot;
int tcur[N], tccl[N], tcol[N], ttot;

void dfs(int u, int co) {
  vis[u] = 1;
  col[u] = co;
  for (auto v : g[u]) if (!vis[v]) {
    dfs(v, co);
  }
}

bool usedn[N], usedk[N];
bool gra(int);

bool arg(int u) { // comp -> node
  usedn[u] = 1;
  FOR(i,1,n) if (col[i] == u) for (auto v : fr[i]) if (!usedk[v]) {
    if (!ccl[v] || gra(v)) {
      cur[u] = v;
      ccl[v] = i;
      return true;
    }
  }
  return false;
}

bool gra(int u) { // node -> comp;
  usedk[u] = 1;
  return arg(col[ccl[u]]);
}

bool chk() {
  ttot = tot;
  FOR(i,1,n) tcur[i] = cur[i], tccl[i] = ccl[i], tcol[i] = col[i];
  vscol[0] = 1;
  FOR(i,1,n) g[i].clear(), vis[i] = 0, vscol[i] = 0;
  FOR(i,0,m-1) if (!ex[i]) {
    g[e[i].u].pb(e[i].v);
    g[e[i].v].pb(e[i].u);
  }
  FOR(i,1,n) if (!vis[i]) {
    dfs(i, vscol[col[i]] ? ++tot : col[i]);
    vscol[col[i]] = 1;
  }
  FOR(i,1,tot) {
    if (cur[i] && col[ccl[cur[i]]] != i) {
      int j = col[ccl[cur[i]]];
      swap(cur[i], cur[j]);
      //swap(ccl[i], ccl[j]);
    }
  }
  FOR(i,1,tot) if (!cur[i]) if (!arg(i)) {
    tot = ttot;
    FOR(i,1,n) cur[i] = tcur[i], ccl[i] = tccl[i], col[i] = tcol[i];
    return 0;
  } else {
    FOR(i,1,n) usedn[i] = usedk[i] = 0;
  }
  return 1;
}

inline void solve() {
  rd(n, m, k);
  FOR(i,0,m-1) e[i].rd();
  FOR(i,1,k) {
    int s;
    rd(s);
    FOR(j,1,s) {
      int x;
      rd(x);
      to[i].pb(x);
      fr[x].pb(i);
    }
  }
  sort(e,e+m);
  int m1 = 0;
  FOR(i,1,n) U.f[i] = i;
  FOR(i,0,m-1) {
    if (U(e[i].u, e[i].v)) ee[m1++] = e[i];
  }
  m = m1;
  int ans = 0;
  ROF(i,0,m-1) e[i] = ee[m-1-i], ans += e[i].w;
  if (!chk()) {
    O(-1);
    return;
  }
  FOR(i,0,m-1) {
    //FOR(i,1,k) O('k', i, ccl[i]);
    //FOR(i,1,tot) O('n', i, cur[i]);
    ex[i] = 1;
    if (chk()) ans -= e[i].w;
    else ex[i] = 0;
  }
  FOR(i,1,k) if (!ccl[i]) {
    O(-1);
    return;
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

