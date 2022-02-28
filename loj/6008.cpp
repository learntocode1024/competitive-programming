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
const int N = 2005, M = 15005;
const int INF = 0x3f3f3f3f;
int to[M<<1], hd[N], cur[N], nxt[M<<1], e[M<<1], cost[M<<1], tot = 1;
int d[N];
int n, m, C, s, T;
void add_flow(int u, int v, int w, int c) {
  to[++tot] = v, nxt[tot] = hd[u], hd[u] = tot, e[tot] = w, cost[tot] = c;
  to[++tot] = u, nxt[tot] = hd[v], hd[v] = tot, e[tot] = 0, cost[tot] = -c;
}

int qu[N<<4], h, t;
bool vis[N];

inline bool bfs() {
  h = t = 1;
  qu[1] = s;
  FOR(i, 1, n + 1) d[i] = INF;
  d[s] = 0;
  while (h <= t) {
    int u = qu[h++];
    vis[u] = 0;
    for (int i = hd[u]; i; i = nxt[i]) if (e[i] && d[to[i]] > d[u] + cost[i]) {
      d[to[i]] = cost[i] + d[u];
      if (!vis[to[i]]) qu[++t] = to[i], vis[to[i]] = 1;
    }
  }
  return d[T] != INF;
}


int dfs(int u, int exc) {
  if (u == T || !exc) return exc;
  int rem = exc;
  vis[u] = 1;
  for (int& i = cur[u]; i; i = nxt[i]) if (e[i] && d[to[i]] == d[u] + cost[i] && !vis[to[i]]) {
    int f = dfs(to[i], min(exc, e[i]));
    e[i] -= f;
    e[i^1] += f;
    exc -= f;
    C += f * cost[i];
    if (!exc) break;
  }
  vis[u] = 0;
  return rem - exc;
}
int flow() {
  int flow = 0;
  while (bfs()) {
    FOR(i, 1, n + 1) cur[i] = hd[i];
    flow += dfs(s, INF);
  }
  return flow;
}
int R[N];
inline void solve() {
  int a,b,c,d,e,f;
  rd(a,b,c,d,e,f);
  n = a+2+a-min(c,e);
  s = n-1, T = n;
  FOR(i,1,a+1) {
    int g;
    rd(g);
    R[i] = g;
    add_flow(i,T,g,0);
    add_flow(s,i,1e8,b);
  }
  FOR(i,1,a-min(c,e)) {
    add_flow(i+a,i+a+1,1e8,0);
  }
  FOR(i,1,a-min(c,e)+1) {
    add_flow(s,i+a,R[i],0);
  }
  FOR(i,1,a-c+1) {
    add_flow(i+a,i+c,1e8,d);
  }
  FOR(i,1,a-e+1) {
    add_flow(i+a,i+e,1e8,f);
  }
  flow();
  // println(flow());
  println(C);
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

