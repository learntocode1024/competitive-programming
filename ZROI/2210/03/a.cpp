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
const int N = 5e5+5;
int n, s, t, m;
vector<int> g[N];
bool vis[N];
int a[N], pa[N];
int A[N], B[N], stk[N], tot;
pii pre[N];

bool mark(int u, int fa) {
  if (u == t) {
    pa[++m] = u;
    vis[u] = 1;
    return 1;
  }
  for (auto v : g[u]) if (v != fa) {
    if (mark(v, u)) {
      vis[u] = 1;
      pa[++m] = u;
      return 1;
    }
  }
  return 0;
}

int getd(int u, int fa) {
  int ret = 0;
  for (auto v : g[u]) if (!vis[v] && v != fa) {
    chkmax(ret, getd(v, u) + 1);
  }
  return ret;
}

struct segT {
  struct node {
    int mx, tg, id;
  } a[N<<2];
  inline void down(int p) {
    int &tg = a[p].tg;
    a[p<<1].mx += tg;
    a[p<<1].tg += tg;
    a[p<<1|1].mx += tg;
    a[p<<1|1].tg += tg;
    tg = 0;
  }
  inline void up(int p) {
    int lc = p<<1, rc = p<<1|1;
    if (a[rc].mx > a[lc].mx) a[p].mx = a[rc].mx, a[p].id = a[rc].id;
    else a[p].mx = a[lc].mx, a[p].id = a[lc].id;
  }
  void build(int p, int l, int r) {
    if (r - l == 1) {
      a[p].id = l;
      a[p].mx = A[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid, r);
    up(p);
  }
  pii get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return {a[p].id, a[p].mx};
    }
    down(p);
    pii ret;
    ret.se = INT_MIN;
    int mid = (l + r) >> 1;
    if (s < mid) ret = get(p<<1, l, mid, s, min(mid, t));
    if (t > mid) {
      pii tmp = get(p<<1|1, mid, r, max(s, mid), t);
      if (tmp.se > ret.se) {
        ret = tmp;
      }
    }
    return ret;
  }
  void ch(int p, int l, int r, int s, int t, int v) {
    if (l == s && r == t) {
      a[p].mx += v;
      a[p].tg += v;
      return;
    }
    down(p);
    int mid = (l + r) >> 1;
    if (s < mid) ch(p<<1, l, mid, s, min(mid, t), v);
    if (t > mid) ch(p<<1|1, mid, r, max(mid, s), t, v);
    up(p);
  }
} T;

pii argmx(int r) {
  int tmx = m - r + a[r];
  int x = -1, mx = INT_MIN;
  for (int i = r - 1; i >= 1; --i) {
    if (i - 1 + a[i] - tmx >= mx) {
      mx = i - 1 + a[i] - tmx;
      x = i;
    }
    chkmax(tmx, m - i + a[i]);
  }
  return {x, mx};
}


inline void solve() {
  rd(n, s, t);
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  mark(s, 0);
  FOR(i, 1, m + 1) a[i] = getd(pa[m - i + 1], 0);
  FOR(i, 1, m + 1) A[i] = a[i] + i - 1, B[i - 1] = a[i] + m - i;
  T.build(1, 1, m);
  for (int i = 1; i < m; ++i) {
    while (tot && B[stk[tot]] <= B[i]) {
      T.ch(1, 1, m, stk[tot-1] + 1, stk[tot] + 1, B[stk[tot]]);
      --tot;
    }
    stk[++tot] = i;
    T.ch(1, 1, m, stk[tot-1] + 1, i + 1, -B[i]);
    pre[i] = T.get(1, 1, m, 1, i + 1);
  }
  int lim = m - m / 2;
  auto to = pre[m - 1];
  int ans;
  if (to.fi <= lim) println(to.se);
  else {
    ans = to.se;
    while (to.fi > lim) {
      to = pre[to.fi - 1];
      chkmin(ans, to.se);
    }
    println(ans);
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

