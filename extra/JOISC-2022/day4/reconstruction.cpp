/** @file
 * @ingroup MST complexity
1. 注意到每条边存在的时间是一段区间
2. 暴力求出每一条边的存在时间（当排序后其左侧/右侧的边能够使$A_i$，$B_i$连通时）
时间： $O(NM\log(n))$.
### 时间复杂度正确的证明：
从询问的角度考虑：最多有$O(M)$种本质不同的询问，而我们的做法恰好遍历了这$O(M)$棵生成树中所有的边，共$O(NM)$条.
 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI
const int N = 505, M = 1e5+5, Q = 1e6+5;
int n, m, q;
pii x[Q];
i64 ans[Q];

struct Edge {
  int u, v, w;
  bool operator< (const Edge &r) const {
    return w < r.w;
  }
} e[M];

int f[N];
#define CLR iota(f,f+n+1,0)
int get(int x) { return f[x] == x ? x : f[x] = get(f[x]); }
inline void uni(int u, int v) {
  if (get(u) != get(v)) f[f[u]] = f[v];
}

struct opt {
  int t, v;
  bool o;
  bool operator< (const opt &r) const {
    return t < r.t;
  }
} g[M<<2];
int cnt;

inline void sol() {
  rd(n, m);
  FOR(i,1,m) {
    rd(e[i].u, e[i].v, e[i].w);
  }
  sort(e+1,e+m+1);
  rd(q);
  FOR(i,1,q) rd(x[i].fi), x[i].se = i;
  sort(x+1,x+q+1);
  FOR(i,1,m) {
    int l = 0, r = 1e9+7;
    if (i > 1) {
      CLR;
      int j = i;
      do {
        --j;
        if (j == 0) break;
        uni(e[j].u, e[j].v);
      } while (get(e[i].u) != get(e[i].v));
      if (j) l = (e[j].w + e[i].w + 1) >> 1;
      err("jL = %d ", j);
    }
    if (i < m) {
      CLR;
      int j = i;
      do {
        ++j;
        if (j == m+1) break;
        uni(e[j].u, e[j].v);
      } while (get(e[i].u) != get(e[i].v));
      if (j <= m) r = ((e[j].w + e[i].w + 1) >> 1) - 1;
      err("jR = %d ", j);
    }
    err("[%d, %d, %d]: L = %d, R = %d\n", e[i].u, e[i].v, e[i].w, l, r);
    if (e[i].w >= r) {
      g[++cnt] = {l, e[i].w, 0};
      g[++cnt] = {r+1, e[i].w, 1};
    } else if (e[i].w <= l) {
      g[++cnt] = {l, -e[i].w, 0};
      g[++cnt] = {r+1, -e[i].w, 1};
    } else {
      g[++cnt] = {l, e[i].w, 0};
      g[++cnt] = {e[i].w, e[i].w, 1};
      g[++cnt] = {e[i].w+1, -e[i].w, 0};
      g[++cnt] = {r+1, -e[i].w, 1};
    }
  }
  i64 k = 0, c = 0;
  sort(g+1,g+cnt+1);
  for (int i = 1, j = 1; i <= q; ++i) {
    while (j <= cnt && g[j].t <= x[i].fi) {
      if (g[j].o) {
        c -= g[j].v;
        if (g[j].v > 0) ++k;
        else --k;
      } else {
        c += g[j].v;
        if (g[j].v > 0) --k;
        else ++k;
      }
      ++j;
    }
    ans[x[i].se] = x[i].fi * k + c;
  }
  FOR(i,1,q) O(ans[i]);
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}
