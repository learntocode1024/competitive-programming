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
void print1n(const A& a, const B& ...b) {
  cout << a << ' ';
  print1n(b...);
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
const int N = 1000, M = 50005;
const int inf = 1e6;

struct mcmf {
  int hd[N], cur[N], to[M], e[M], w[M], nxt[M], tot=1;
  int _s, _t, C, n;
  int d[M];
  bool vis[N];
  int qu[N<<4], h1, t1;
  inline void add_flow(int u, int v, int cap, int cost) {
    to[++tot] = v, e[tot] = cap, w[tot] = cost, nxt[tot] = hd[u], hd[u] = tot;
    to[++tot] = u, e[tot] = 0, w[tot] = -cost, nxt[tot] = hd[v], hd[v] = tot;
  }
  bool sssp() {
    h1 = t1 = 1;
    qu[1] = _s;
    FOR(i, 1, n + 1) d[i] = inf;
    d[_s] = 0;
    while (h1 <= t1) {
      int u = qu[h1++];
      vis[u] = 0;
      for (int i = hd[u]; i; i = nxt[i]) if (e[i] && d[to[i]] > d[u] + w[i]) {
        d[to[i]] = d[u] + w[i];
        if (!vis[to[i]]) qu[++t1] = to[i], vis[to[i]] = 1;
      }
    }
    return d[_t] != inf;
  }
  int dfs(int u, int exc) {
    if (u == _t || !exc) return exc;
    int ans = 0;
    vis[u] = 1;
    for (int &i = cur[u]; i; i = nxt[i]) if (!vis[to[i]] && e[i] && d[to[i]] == d[u] + w[i]) {
      int f = dfs(to[i], min(exc, e[i]));
      exc -= f;
      e[i] -= f;
      e[i^1] += f;
      ans += f;
      C += f * w[i];
      if (!exc) break;
    }
    vis[u] = 0;
    return ans;
  }
  inline int flow(int s, int t) {
    _s = s, _t = t;
    int ans = 0;
    while (sssp()) {
      FOR(i, 1, n + 1) cur[i] = hd[i];
      dfs(s, inf);
    }
    return -C;
  }
}f1, f2, f3;

int a[N][N], id[N][N];
int n, m, k;
inline void w1() {
  f1.n = k*2+2;
  int s = f1.n-1, t = f1.n;
  FOR(i, 0, n) FOR(j, 0, m + i) {
    f1.add_flow(id[i][j]*2-1, id[i][j]*2, 1, -a[i][j]);
    if (id[i+1][j]) {
      f1.add_flow(id[i][j]*2, id[i+1][j]*2-1, 1, 0);
    }
    if (id[i+1][j+1]) {
      f1.add_flow(id[i][j]*2, id[i+1][j+1]*2-1, 1, 0);
    }
  }
  FOR(i, 0, m) {
    f1.add_flow(s, id[0][i]*2-1, 1, 0);
  }
  FOR(i, 0, m + n - 1) {
    f1.add_flow(id[n-1][i]*2, t, 1, 0);
  }
  println(f1.flow(s,t));
}
inline void w2() {
  f2.n = k*2+2;
  int s = f2.n-1, t = f2.n;
  FOR(i, 0, n) FOR(j, 0, m + i) {
    f2.add_flow(id[i][j]*2-1, id[i][j]*2, inf, -a[i][j]);
    if (id[i+1][j]) {
      f2.add_flow(id[i][j]*2, id[i+1][j]*2-1, 1, 0);
    }
    if (id[i+1][j+1]) {
      f2.add_flow(id[i][j]*2, id[i+1][j+1]*2-1, 1, 0);
    }
  }
  FOR(i, 0, m) {
    f2.add_flow(s, id[0][i]*2-1, 1, 0);
  }
  FOR(i, 0, m + n - 1) {
    f2.add_flow(id[n-1][i]*2, t, inf, 0);
  }
  println(f2.flow(s,t));
}
inline void w3() {
  f3.n = k*2+2;
  int s = f3.n-1, t = f3.n;
  FOR(i, 0, n) FOR(j, 0, m + i) {
    f3.add_flow(id[i][j]*2-1, id[i][j]*2, inf, -a[i][j]);
    if (id[i+1][j]) {
      f3.add_flow(id[i][j]*2, id[i+1][j]*2-1, inf, 0);
    }
    if (id[i+1][j+1]) {
      f3.add_flow(id[i][j]*2, id[i+1][j+1]*2-1, inf, 0);
    }
  }
  FOR(i, 0, m) {
    f3.add_flow(s, id[0][i]*2-1, 1, 0);
  }
  FOR(i, 0, m + n - 1) {
    f3.add_flow(id[n-1][i]*2, t, inf, 0);
  }
  println(f3.flow(s,t));
}

inline void solve() {
  rd(m, n);
  int tott = 0;
  FOR(i, 0, n) FOR(j, 0, m + i) {
    rd(a[i][j]);
    id[i][j] = ++tott;
  }
  k = tott;
  w1();
  w2();
  w3();
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

