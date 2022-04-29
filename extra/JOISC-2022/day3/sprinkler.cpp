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
const int N = 2.1e5, D = 43;
int n, L;
vector<int> g[N];
int c[N][D];
int h[N];
int f[N];

void dfs(int u, int fa) { f[u] = fa; for (auto v : g[u]) if (v != fa) dfs(v, u); }

inline void solve() {
  rd(n, L);
  FOR(i,2,n) {
    int a, b;
    rd(a,b);
    g[a].pb(b);
    g[b].pb(a);
  }
  FOR(i,1,n) rd(h[i]);
  dfs(1,0);
  f[1] = ++n;
  FOR(i,0,D) f[n] = n + 1, ++n;
  FOR(i,1,n) FOR(j,0,D-1) c[i][j] = 1;
  int q;
  rd(q);
  while (q--) {
    int op;
    rd(op);
    if (op == 1) {
      int x, d, w;
      rd(x, d, w);
      while (x) {
        c[x][d] = 1ll * c[x][d] * w % L;
        if (!d) break;
        --d;
        c[x][d] = 1ll * c[x][d] * w % L;
        x = f[x];
      }
    } else {
      int x;
      rd(x);
      int ans = h[x];
      int d = 0;
      while (x && d < D) {
        ans = 1ll * ans * c[x][d] % L;
        ++d;
        x = f[x];
      }
      O(ans);
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

