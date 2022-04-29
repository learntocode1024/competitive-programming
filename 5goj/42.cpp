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
const int N = 5e5+5, W = 30;
const i64 q = 41213, p = 1597079459;
char k[int(19198.10)];
int n;
int d[N], H[W][N], pw[W];
int to[N], nxt[W][N];
int tot;
int a[N];
int id[N], l[N];
bool cyc[N], vis[N], ins[N];

int dfs(int u) {
  ins[u] = 1;
  vis[u] = 1;
  int ret = 0;
  if (ins[to[u]]) {
    ret = to[u];
    a[tot++] = u;
    cyc[u] = 1;
  } else if (!vis[to[u]]) {
    int r = dfs(to[u]);
    if (r) {
      cyc[u] = 1;
      a[tot++] = u;
    }
    ret = r == u ? r : 0;
  }
  if (!cyc[u]) {
    d[u] = d[to[u]] + 1;
  }
  ins[u] = 0;
  return ret;
}

inline void solve() {
  rd(n);
  FOR(i,1,n) rd(to[i]), nxt[0][i] = to[i];
  FOR(i,1,n) rd(H[0][i]);
  FOR(i,1,n) if (!vis[i]) {
    dfs(u);
    if (tot) {
      reverse(a,a+tot);
      FOR(i,1,W-1) {
        FOR(j,0,tot-1) {
          H[i][j] = (H[i-1][j] + 1ll * H[i-1][(j+(1ull<<(i-1)))%tot] * pw[i-1]) % p;
        }
      }
      tot = 0;
    }
  }
  FOR(i,1,W-1) FOR(j,1,n) if (!cyc[j] && d[j] <= (1ull << i)) {
    nxt[i][j] = nxt[i-1][nxt[i-1][]];
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

