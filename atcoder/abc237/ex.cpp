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
const int N = 505;
char s[N];
int n;template <u32 MX, u32 MXM>
struct net {
  int head[MX], to[MXM], nxt[MXM], hi[MX], d[MX], tot = 1;
  i64 f[MXM];
  int N;
  int s, t;
  net(int n) : N(n) {};
  void add_flow(int u, int v, i64 w) {
    println(u, v);
    to[++tot] = v, f[tot] = w, nxt[tot] = head[u], head[u] = tot;
    to[++tot] = u, f[tot] = 0, nxt[tot] = head[v], head[v] = tot;
  }
  bool bfs() {
    for (int i = 1; i <= N; ++i) {
      d[i] = 0;
    }
    d[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        i64 w = f[i];
        if (d[v] || !w) continue;
        d[v] = d[u] + 1;
        if (v == t) return 1;
        q.push(v);
      }
    }
    return 0;
  }
  i64 dfs(int u, i64 exc) {
    if (u == t) return exc;
    i64 res = exc;
    for (int &i = hi[u]; i; i = nxt[i]) {
      int v = to[i];
      i64 w = f[i];
      if (d[v] != d[u] + 1 || !w) continue;
      int k = dfs(v, min(res, w));
      if (!k)
        d[v] = 0;
      else
        res -= k, f[i] -= k, f[i ^ 1] += k;
      if (!res) break;
    }
    return exc - res;
  }

  i64 flow(int _s, int _t) {
    i64 ret = 0;
    s = _s, t = _t;
    while (bfs()) {
      for (int i = 1; i <= N; ++i) {
        hi[i] = head[i];
      }
      i64 f = 0;
      while ((f = dfs(s, 1e7))) ret += f;
    }
    return ret;
  }
};
int ans;

struct pam {
  char *s;
  int len[N], f[N], nxt[N][26];
  int last, tot;
  int dp[N];
  void init(char *_s, int n) {
    s = _s;
    len[0] = -1;
    f[0] = 0;
    len[1] = 0;
    f[1] = 0;
    last = 1;
    tot = 1;
    int p;
    for (int i = 0; i < n; ++i) {
      p = last;
      while (s[i] != s[i - len[p] - 1]) p = f[p];
      int &cur = nxt[p][s[i] - 'a'];
      if (cur == 0) {
        cur = ++tot;
        len[cur] = len[p] + 2;
        if (p == 0) f[cur] = 1;
        else {
          p = f[p];
          while (s[i] != s[i - len[p] - 1]) p = f[p];
          f[cur] = nxt[p][s[i] - 'a'];
        }
      }
      last = cur;
      ++dp[cur];
    }
  }
  void gen() {
  net<N,N*26> G(tot*2);
    ans = tot - 1;
    FOR(i, 2, tot + 1) {
      G.add_flow(1, i<<1, 1);
      G.add_flow(i<<1|1,2,1);
      if (f[i]>=2) G.add_flow(i<<1, f[i]<<1|1, 100);
      FOR(j, 0, 26) if (nxt[i][j] >= 2) G.add_flow(i<<1, nxt[i][j]<<1|1, 100);
      // chkmax(ret, 1ll * dp[i] * len[i]);
      // dp[f[i]] += dp[i];
    }
    println(ans - G.flow(1, 2));
  }
} P;

inline void solve() {
  cin >> s;
  n = strlen(s);
  P.init(s, n);
  P.gen();
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

