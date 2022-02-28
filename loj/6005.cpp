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
const int N = 405, M = 20005;
struct network {
int n, s, t;
int hd[N], cur[N], to[M<<1], nnt[M<<1], e[M<<1], tot=1;
int d[N];

inline void add_flow(int u, int v, int c) {
  to[++tot] = v, nnt[tot] = hd[u], hd[u] = tot, e[tot] = c;
  to[++tot] = u, nnt[tot] = hd[v], hd[v] = tot, e[tot] = 0;
}

int qu[N], h, tl;
inline bool bfs() {
  h = tl = 1;
  qu[1] = s;
  FOR(i, 1, n + 1) d[i] = -1;
  d[s] = 0;
  while (h <= tl) {
    int u = qu[h++];
    for (int i = hd[u]; i; i = nnt[i]) if (d[to[i]] == -1 && e[i]) {
      d[to[i]] = d[u] + 1;
      qu[++tl] = to[i];
      if (to[i] == t) return true;
    }
  }
  return false;
}

inline i64 dfs(int u, i64 enc) {
  if (!enc || u == t) return enc;
  i64 rem = enc;
  for (int &i = cur[u]; i; i = nnt[i]) if (d[to[i]] == d[u] + 1 && e[i]) {
    i64 f = min((i64)e[i], enc);
    f = dfs(to[i], f);
    enc -= f;
    e[i] -= f;
    e[i^1] += f;
    if (!enc) break;
  }
  return rem - enc;
}

inline i64 flow() {
  i64 ans = 0;
  while (bfs()) {
    FOR(i, 1, n + 1) cur[i] = hd[i];
    ans += dfs(s, 1e18);
  }
  return ans;
}
inline void init(int _n, int _s, int _t) {
  n = _n, s = _s, t = _t;
}
} g;
int a[N];
int f[N], G[N];
bool v[N];
inline void solve() {
  int n;
  rd(n);
  FOR(i, 1, n + 1) cin >> a[i];
  int a1 = 0;
  FOR(i, 1, n + 1) {
    FOR(j, 0, i) if (a[j] <= a[i]) chkmax(f[i], f[j]+1);
    chkmax(a1, f[i]);
  }
  println(a1);
  int m = n*2+2, s = m-1, t = m;
  g.init(m,s,t);
  FOR(i, 1, n + 1) FOR(j, i+1, n + 1) if (a[i]<=a[j])g.add_flow(i*2-1,j*2,1);
  FOR(i, 1, n + 1) if (f[i] == 1) g.add_flow(s,i*2-1,1);
  FOR(i,1,n) {
    G[i] = 1;
    FOR(j, i + 1, n + 1) {
      G[j] = -1e8;
      FOR(k, i, j) if (a[j] >= a[k]) chkmax(G[j], G[k]+1);
      if (G[j] == a1) {
        v[j] = 1;
      }
    }
  }
  FOR(i,1,n+1) if (v[i]) g.add_flow(i*2,t,1);
  int a2=0;
  println(a2=g.flow());
  g.add_flow(s,1,1e7);
  if (v[n]) g.add_flow(n*2,t,1e7);
  println(a2+g.flow());
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

