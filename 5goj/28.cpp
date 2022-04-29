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
const int N = 1005, M = N<<4;
const i64 inf = 1e17;

int hd[M], h[M], to[M], nxt[M], e[M];
i64 w[M];
i64 C;
bool vis[M];
i64 dis[M];
int tot = 1;
int nv;

void add_flow(int u, int v, int cap, i64 cos) {
  to[++tot] = v, nxt[tot] = hd[u], hd[u] = tot, e[tot] = cap, w[tot] = cos;
  to[++tot] = u, nxt[tot] = hd[v], hd[v] = tot, e[tot] = 0, w[tot] = -cos;
}

int S, T;

int qu[M], h1, t1;
bool bfs() {
  qu[h1 = t1 = 1] = S;
  FOR(i,1,nv) dis[i] = inf;
  dis[S] = 0;
  while (h1 <= t1) {
    int u = qu[h1++];
    vis[u] = 0;
    for (int i = hd[u]; i; i = nxt[i]) if (e[i] && dis[to[i]] > dis[u] + w[i]) {
      dis[to[i]] = dis[u] + w[i];
      if (!vis[to[i]]) qu[++t1] = to[i], vis[to[i]] = 1;
    }
  }
  return dis[T] < inf;
}

int dfs(int u, int ext) {
  if (u == T) return ext;
  int ret = 0;
  vis[u] = 1;
  for (int &i = h[u]; i; i = nxt[i]) if (!vis[to[i]] && dis[to[i]] == dis[u] + w[i] && e[i]) {
    int vol = dfs(to[i], min(e[i], ext));
    ext -= vol;
    e[i] -= vol;
    e[i^1] += vol;
    C += w[i] * vol;
    ret += vol;
  }
  vis[u] = 0;
  return ret;
}

int a[N], b[N];

inline void solve() {
  int n, k, t1, t2;
  rd(n, k, t1, t2);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,n) rd(b[i]);
  t2 = k - t2;
  FOR(i,1,n) C -= b[i], a[i] -= b[i];
  S = n - k + 3, T = n - k + 4;
  nv = T;
  add_flow(S,1,t2,0);
  add_flow(n-k+2,T,t2,0);
  FOR(i,1,n) {
    add_flow(max(1,i-k+1),min(n-k+2,i+1),1,-a[i]);
  }
  FOR(i,1,n-k+1) add_flow(i,i+1,t2-t1,0);
  int ans = 0;
  while (bfs()) {
    FOR(i,1,nv) h[i] = hd[i];
    ans += dfs(S, 1e7);
  }
  O(-C);
}

int main() {
#ifndef MISAKA
  freopen("ieh.in", "r", stdin);
  freopen("ieh.out", "w", stdout);
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

