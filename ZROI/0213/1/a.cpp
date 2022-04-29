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

struct FFFF {
static const int N = 2e4+5, M = 5e5+5;
int n, m, s, t;
int hd[N], cur[N], to[M<<1], nxt[M<<1], e[M<<1], tot=1;
int d[N];

inline void add_flow(int u, int v, int c) {
  // O(u,v,c);
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

inline i64 flow(int _n, int _s, int _t) {
  n = _n;
  s = _s;
  t = _t;
  i64 ans = 0;
  while (bfs()) {
    FOR(i, 1, n + 1) cur[i] = hd[i];
    ans += dfs(s, 1e18);
  }
  return ans;
}
} G;

//#define MULTI
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e4+5, K = 55;
int x[N][K], id[N][K];
int tmp[K][N];
u64 h[K][N], H[N];
int n, k;
map<u64, int> S;
inline void solve() {
  rd(n,k);
  FOR(i,1,n) FOR(j,1,k) {
    rd(x[i][j]);
    tmp[j][i] = x[i][j];
  }
  FOR(i,1,k) {
    sort(tmp[i]+1,tmp[i]+n+1);
    int l = unique(tmp[i]+1, tmp[i]+n+1) - tmp[i];
    FOR(j,1,l) h[i][j] = rng();
    FOR(j,1,n) {
      id[j][i] = lower_bound(tmp[i]+1,tmp[i]+l,x[j][i]) - tmp[i];
    }
  }
  FOR(i,1,n) {
    u64 ha = 0;
    FOR(j,1,k) ha ^= h[j][id[i][j]];
    S[ha] = i;
    H[i] = ha;
  }
  OO(S.size());
  int s = n*2+1, t = s + 1;
  FOR(i,1,n) {
    int codd = 0;
    u64 hto = 0;
    bool ok = 1;
    FOR(j,1,k) {
      codd += x[i][j] & 1;
      if (tmp[j][id[i][j]+1] == x[i][j] + 1 && (x[i][j] & 1) == 0) {
        hto = H[i] ^ h[j][id[i][j]] ^ h[j][id[i][j]+1];
        if (S.find(hto) != S.end()) G.add_flow(i*2,S[hto]*2-1,n+1);
      }
      if (tmp[j][id[i][j]-1] == x[i][j] - 1 && (x[i][j] & 1) == 0) {
        hto = H[i] ^ h[j][id[i][j]] ^ h[j][id[i][j]-1];
        if (S.find(hto) != S.end()) G.add_flow(i*2,S[hto]*2-1,n+1);
      }
    }
    if (codd == 0) G.add_flow(s,i*2-1,n+1);
    else G.add_flow(i*2,t,n+1);
  }
  FOR(i,1,n) G.add_flow(2*i-1,2*i,1);
  O(G.flow(t,s,t));
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

