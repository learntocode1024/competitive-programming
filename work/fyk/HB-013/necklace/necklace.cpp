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
const int N = 4e5+5, B = 19;
char s[N];
int n;
int pos[N];
vector<int> g[N];
int dep[N], dfn[N], rnk[N], tt;
struct O1LCA {
  int dfn[N], rk[N<<1], e[B][N<<1], tot;
  void dfs(int u, int fa) {
    ::dfn[u] = ++tt;
    ::rnk[tt] = u;
    dfn[u] = ++tot;
    rk[tot] = u;
    e[0][tot] = tot;
    for (auto v : g[u]) if (v != fa) {
      dep[v] = dep[u] + 1;
      dfs(v, u);
      e[0][++tot] = dfn[u];
    }
  }
  inline int lca(int u, int v) {
    u = dfn[u], v = dfn[v];
    if (u > v) swap(u,v);
    int t = 31 - __builtin_clz(v-u+1);
    return rk[min(e[t][u], e[t][v-(1<<t)+1])];
  }
  inline void build() {
    dfs(1,1);
    FOR(i,1,B-1) FOR(j,1,tot-(1<<i)+1) {
      e[i][j] = min(e[i-1][j], e[i-1][j+(1<<(i-1))]);
    }
  }
  inline int operator() (const int &u, const int &v) {
    return lca(u,v);
  }
} lca;

struct DS {
  struct node {
    int l, r, s, u;
    int cnt;
  } a[N << 2];
  int all;
  #define lc a[p<<1]
  #define rc a[p<<1|1]
  #define P a[p]
  inline void up(int p) {
    if (lc.l && rc.l) {
      P.l = lc.l;
      P.r = rc.r;
      P.s = lc.s + rc.s - dep[lca(rnk[lc.r], rnk[rc.l])];
      P.u = lca(lc.u, rc.u);
    } else {
      P.l = lc.l | rc.l;
      P.r = lc.r | rc.r;
      P.s = lc.s | rc.s;
      P.u = lc.u | rc.u;
    }
  }
  void ins(int p, int l, int r, int pos, int v) {
    if (r - l == 1) {
      P.cnt += v;
      if (P.cnt > 0) {
        P.l = P.r = l;
        P.u = rnk[l];
        P.s = dep[rnk[l]];
      } else {
        P.l = P.r = P.s = P.u = 0;
      }
      return;
    }
    int mid = (l + r) >> 1;
    if (pos < mid) ins(p<<1, l, mid, pos, v);
    else ins(p<<1|1, mid, r, pos, v);
    up(p);
  }
  int get() {
    return a[1].s - dep[a[1].u];
  }
  #undef lc
  #undef rc
  #undef P
} T;

struct pam {
  char *s;
  int len[N], f[N], nxt[N][26];
  int last, tot;
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
      pos[i+1] = cur + 1;
    }
    FOR(i, 1, tot) {
      g[f[i]+1].pb(i+1);
    }
    lca.build();
  }
} P;

int ans[N], bel[N];
const int BB = 400;
struct qry {
  int l, r, id;
  bool operator< (const qry &b) const {
    return (bel[l] == bel[b.l]) ? r < b.r : bel[l] < bel[l];
  }
} q[N];

inline void solve() {
  cin >> s;
  n = strlen(s);
  P.init(s, n);
  int m;
  rd(m);
  int l = 1, r = 0;
  for (int i = BB; i <= n; i += BB) bel[i] = 1;
  FOR(i,BB+1,n) bel[i] += bel[i-1];
  FOR(i,1,m) {
    rd(q[i].l, q[i].r);
    q[i].id = i;
  }
  sort(q + 1, q + m+1);
  T.ins(1,1,P.tot+2,dfn[1],1);
  FOR(i,1,m) {
    while (r < q[i].r) T.ins(1,1,P.tot+2,dfn[pos[++r]], 1);
    while (l > q[i].l) T.ins(1,1,P.tot+2,dfn[pos[--l]], 1);
    while (r > q[i].r) T.ins(1,1,P.tot+2,dfn[pos[r--]], -1);
    while (l < q[i].l) T.ins(1,1,P.tot+2,dfn[pos[l++]], -1);
    ans[q[i].id] = T.get() - 1;
  }
  FOR(i,1,m) O(ans[i]);
}

int main() {
#ifndef MISAKA
  freopen("necklace.in", "r", stdin);
  freopen("necklace.out", "w", stdout);
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

