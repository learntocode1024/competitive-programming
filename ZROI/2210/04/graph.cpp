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

//#define MULTI
const int N = 5005;
bitset<N> g[N], aval;
int n;
char s[N];
int d[N], f[N];
// int l[N];
// int o, mn;

// void dfs(int u) {
//   aval[u] = 0;
//   bitset<N> to = aval & g[u];
//   // if (d[u] >= mn) return;
//   if (g[u][o] && d[u] != 1) chkmin(mn, d[u]);
//   for (int v = 1; v <= n; ++v) if (aval[v]) {
//     d[v] = d[u] + 1;
//     dfs(v);
//   }
//   // for (int i = to._Find_first(); i < to.size(); i = to._Find_next(i)) if (aval[i]) {
//   //   d = d[u] + 1;
//   //   dfs(i);
//   // }
// }

int qu[N], hd, tl;

inline void solve() {
  cin >> n;
  FOR(i, 2, n + 1) {
    cin >> s + 1;
    FOR(j, 1, i) if (s[j] == '1') g[i][j] = g[j][i] = 1;
  }
  // FOR(i, 1, n + 1) {
  //   aval.reset();
  //   aval.flip();
  //   o = i;
  //   mn = 1e8;
  //   d[i] = 0;
  //   dfs(i);
  //   l[i] = (mn>>1)+1;
  // }
  FOR(i, 1, n + 1) {
    int ans = 1e8;
    aval.reset();
    aval.flip();
    aval[i] = 0;
    hd = tl = 1;
    qu[1] = i;
    FOR(j, 1, n + 1) d[j] = 1e8;
    d[i] = 0;
    while (tl >= hd) {
      int u = qu[hd++];
      for (int v = g[u]._Find_first(); v < g[u].size(); v = g[u]._Find_next(v)) if (v != f[u]) {
        if (aval[v]) {
        d[v] = d[u] + 1;
        f[v] = u;
        aval[v] = 0;
        qu[++tl] = v;
        }
        else chkmin(ans, (d[u] + d[v])/ 2 + 1);
      }
      if (ans != 1e8) break;
    }
    println(ans > 1e5 ? -1 : ans);
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

