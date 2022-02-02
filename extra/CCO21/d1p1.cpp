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
const int N = 1e5+5, MXQ = 1e6+5;
vector<int> g[N];
vector<pii> q[N];
int a[N];
int n, K, Q;
int p[N];
i64 ans[MXQ];
int c[N];
i64 f[N];
const int B = 500;
inline void add(int x, int v) {
  for (;x <= n; x += x & -x) {
    c[x] += v;
  }
}

inline int sum(int x) {
  int ret = 0;
  for (; x; x -= x & -x) {
    ret += c[x];
  }
  return ret;
}

inline void solve() {
  rd(n, K, Q);
  iota(p, p + K + 1, 0);
  FOR(i, 1, n + 1) {
    cin >> a[i];
    g[a[i]].pb(i);
  }
  ROF(i, 1, K + 1) {
    for (int j = g[i].size() - 1; j >= 0; --j) {
      ans[0] += sum(g[i][j]);
      add(g[i][j], 1);
    }
  }
  FOR(i, 1, n + 1) c[i] = 0;
  FOR(i, 1, Q + 1) {
    int x;
    cin >> x;
    ans[i] = g[p[x]].size() * g[p[x+1]].size();
    if (ans[i]) {
      if (g[p[x]].size() < B && g[p[x]].size() < B) {
        int cur = 0;
        for (int u = 0, v = 0; v < g[p[x]].size(); ++v) {
          while (u < g[p[x+1]].size() && g[p[x+1]][u] < g[p[x]][v]) ++u;
          cur += u;
        }
        ans[i] -= cur << 1;
      } else if (g[p[x+1]].size() >= B) {
        q[p[x+1]].eb(p[x], i);
      } else {
        q[p[x]].eb(p[x+1], -i);
        ans[i] = -ans[i];
      }
    }
    swap(p[x], p[x+1]);
  }
  FOR(i, 1, K + 1) {
    if (!q[i].empty()) {
      for (auto v : g[i]) c[v] = 1;
      FOR(j, 2, n + 1) c[j] += c[j-1];
      FOR(j, 1, n + 1) f[a[j]] += c[j];
      for (auto qi : q[i]) {
        if (qi.se > 0) ans[qi.se] -= f[qi.fi] << 1;
        else ans[-qi.se] += f[qi.fi] << 1;
      }
      FOR(j, 1, n + 1) f[j] = c[j] = 0;
    }
  }
  FOR(i, 1, Q + 1) ans[i] += ans[i-1], println(ans[i]);
}

int main() {
#ifndef MISAKA
  // freopen("d1p1.1-02.in", "r", stdin);
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

