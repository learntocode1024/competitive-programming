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
const int N = 3005;
vector<int> g[N];
int a[N<<1];
bool vis[N];
int n, m;
i64 ans = 0;

void dfs(int u) {
  vis[u] = 1;
  a[m++] = u;
  for (auto v : g[u]) if (!vis[v]) dfs(v);
}

int x[4], y[4];

i64 range(int l, int r, int s, int t) {
  if (l < s || r < l || t < r) return 0;
  return 1ll * (l-s+1) * (t-r+1);
}

inline void ring() {
  int l1 = n, r1 = 1, l2 = 2*n, r2 = 1;
  FOR(i,0,m-1) if (a[i]<=n) chkmin(l1,a[i]), chkmax(r1, a[i]); else chkmax(r2,a[i]),chkmin(l2,a[i]);
  ans += 1ll * (m/2) * l1 * (n-r1+1) * (l2-n) * (2*n-r2+1);
  FOR(i,m,m*2-1) a[i] = a[i-m];
  FOR(i,1,m) {
    l1 = n, r1 = 1, l2 = 2*n, r2 = 1;
    FOR(j, 1, m-1) {
      if (a[i+j-1]<=n) chkmin(l1,a[i+j-1]), chkmax(r1, a[i+j-1]);
      else chkmax(r2,a[i+j-1]-n),chkmin(l2,a[i+j-1]-n);
      x[0] = 0, x[3] = n+1;
      y[0] = 0, y[3] = n+1;
      x[1] = x[2] = y[1] = y[2] = 0;
      if (a[i-1] <= n) x[1] = a[i-1];
      else y[1] = a[i-1]-n;
      if (a[i+j]<= n) x[2] = a[i+j];
      else y[2] = a[i+j]-n;
      sort(x,x+4);
      sort(y,y+4);
      FOR(p,0,2) FOR(q,0,2)ans += 1ll * (j/2) * range(l1,r1,x[p]+1,x[p+1]-1) * range(l2,r2,y[q]+1,y[q+1]-1);
    }
  }
}

inline void solve() {
  rd(n);
  FOR(i,1,n*2) {
    int u, v;
    rd(u,v);
    g[u].pb(v);
    g[v].pb(u);
  }
  FOR(i,1,n) if (!vis[i]) {
    m = 0;
    dfs(i);
    ring();
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

