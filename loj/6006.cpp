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
const int N = 1205, M = 50005;
int n, m, s, t;
int hd[N], cur[N], to[M<<1], nxt[M<<1], e[M<<1], tot=1;
int d[N];

inline void add_flow(int u, int v, int c) {
  to[++tot] = v, nxt[tot] = hd[u], hd[u] = tot, e[tot] = c;
  to[++tot] = u, nxt[tot] = hd[v], hd[v] = tot, e[tot] = 0;
}

int qu[N], h, tl;
inline bool bfs() {
  h = tl = 1;
  qu[1] = s;
  FOR(i, 1, n + 1) d[i] = -1;
  d[s] = 0;
  while (h <= tl) {
    int u = qu[h++];
    for (int i = hd[u]; i; i = nxt[i]) if (d[to[i]] == -1 && e[i]) {
      d[to[i]] = d[u] + 1;
      qu[++tl] = to[i];
      if (to[i] == t) return true;
    }
  }
  return false;
}

inline i64 dfs(int u, i64 exc) {
  if (!exc || u == t) return exc;
  i64 rem = exc;
  for (int &i = cur[u]; i; i = nxt[i]) if (d[to[i]] == d[u] + 1 && e[i]) {
    i64 f = min((i64)e[i], exc);
    f = dfs(to[i], f);
    exc -= f;
    e[i] -= f;
    e[i^1] += f;
    if (!exc) break;
  }
  return rem - exc;
}

inline i64 flow() {
  i64 ans = 0;
  while (bfs()) {
    FOR(i, 1, n + 1) cur[i] = hd[i];
    ans += dfs(s, 1e18);
  }
  return ans;
}
int k;
int ff[N];

inline void solve() {
  rd(k, m);
  int S = 0;
  n = k + m + 2;
  s = n-1, t = n;
  FOR(i, 1, k + 1) {
    int a;
    rd(a);
    S += a;
    ff[i] = a;
    add_flow(i, t, a);
  }
  FOR(i, 1, m + 1) {
    int p;
    rd(p);
    int w;
    add_flow(s,i+k,1);
    FOR(j, 0, p) {
      rd(w);
      add_flow(i+k,w,1);
    }
  }
  if (flow()!=S) {
    println("No Solution!");
    return;
  }
  FOR(i, 1, k + 1) {
    print(i,":");
    if (!ff[i]) {
      cout << " \n";
    }
    for (int j = hd[i]; j; j = nxt[j]) if ((j&1) && e[j]) {
      cout << ' ' << to[j]-k;
    }
    cout << '\n';
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

