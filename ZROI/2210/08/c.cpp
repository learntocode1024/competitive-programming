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
const int N = 2e5+5, X = 1e4+5, X2 = X*2+5;

struct BIT_SEG {
  i64 ans = 0;
  int rt[X2+5], tot;
  struct node {
    int l,r;
    i64 s;
  } a[N<<6];
  void ins(int &p, int l, int r, int t, int v) {
    if (!p) p = ++tot, a[p].l = a[p].r = a[p].s = 0;
    a[p].s += v;
    if (r-l==1) return;
    int m = (l+r)>>1;
    if (t < m) ins(a[p].l,l,m,t,v);
    else ins(a[p].r,m,r,t,v);
  }
  i64 sum(int p, int l, int r, int s, int t) {
    if (!p) return 0;
    if (l == s && r == t) return a[p].s;
    int m = (l+r)>>1;
    i64 ret = 0;
    if (s < m) ret = sum(a[p].l,l,m,s,min(m,t));
    if (t > m) ret += sum(a[p].r,m,r,max(m,s),t);
    return ret;
  }
  inline i64 pref(int x, int l, int r) {
    i64 ret = 0;
    for (; x; x -= x & -x) ret += sum(rt[x], 1, X2, l, r);
    return ret;
  }
  inline void ins(int x, int y) {
    x += X, y += X;
    ans += pref(x-1, 1, y);
    ans += pref(X2-1, y+1, X2) - pref(x, y+1, X2);
    for (; x < X2; x += x & -x) {
      ins(rt[x], 1, X2, y, 1);
    }
  }
  inline void del(int x, int y) {
    x += X, y += X;
    ans -= pref(x-1, 1, y);
    ans -= pref(X2-1, y+1, X2) - pref(x, y+1, X2);
    for (; x < X2; x += x & -x) {
      ins(rt[x], 1, X2, y, -1);
    }
  }
  inline i64 sum() {
    return ans;
  }
} T;

int n, q;
int x[N], y[N];
int A[N], B[N], C[N];

namespace sub1 {
int m;
int a[N], b[N];

inline void work() {
  FOR(_,1,q) {
    i64 A, B, C;
    rd(A,B,C);
    m = 0;
    FOR(i,1,n) {
      if (A*x[i]+B*y[i]+C>0ll) T.ins(x[i], y[i]);
    }
    O(T.sum());
    FOR(i,1,n) {
      if (A*x[i]+B*y[i]+C>0ll) T.del(x[i], y[i]);
    }
  }
}
}

namespace sub2 {
vector<int> g[X2+5];
i64 ans[N];
vector<pii> a, b;
inline void work() {
  FOR(i,1,n) {
    x[i] += X;
    y[i] += X;
    g[y[i]].pb(x[i]);
  }
  FOR(i,1,q) {
    if (B[i] > 0) a.eb(floor(-1.0l*C[i]/B[i])+1+X, i);
    else b.eb(ceil(-1.0l*C[i]/B[i])-1+X, i);
  }
  sort(begin(a), end(a));
  sort(begin(b), end(b));
  int l = 1;
  for (auto v : b) {
    while (l <= v.fi && l < X2) {
      for (auto i : g[l]) {
        T.ins(i-X,l-X);
      }
      ++l;
    }
    ans[v.se] = T.sum();
  }
  while (l < X2) {
    for (auto i : g[l]) {
      T.ins(i-X,l-X);
    }
    ++l;
  }
  l = 1;
  for (auto v : a) {
    while (l < v.fi && l < X2) {
      for (auto i : g[l]) {
        T.del(i-X,l-X);
      }
      ++l;
    }
    ans[v.se] = T.sum();
  }
  FOR(i,1,q) {
    O(ans[i]);
  }
}
}

namespace sub3 {
typedef long double dbl;
const dbl eps = 1e-11l;
bool flt(dbl a, dbl b) {
  if (fabs(a-b)<eps) return 0;
  return a < b;
}

bool fle(dbl a, dbl b) {
  if (fabs(a-b)<eps) return 1;
  return a < b;
}
struct pts {
  dbl al;
  int x, y;
  int id;
  pts() {
    x = y = id = al = 0;
  }
  pts(int _x, int _y, int _id) {
    id = _id;
    x = _x;
    y = _y;
    al = atan2(_y,_x);
  }
  bool operator< (const pts &r) const {
    return al < r.al;
  }
} a[N], b[N];
i64 ans[N];
inline void work() {
  FOR(i,1,n) a[i] = pts(x[i], y[i],0);
  sort(a+1,a+n+1);
  FOR(i,1,q) b[i] = pts(B[i], -A[i],i);
  sort(b+1,b+q+1);
  int l = 1, r = 1;
  int m = 1;
  while (m <= q && fle(b[m].al, 0)) ++m;
  while (r <= n && flt(a[r].al, 0.0l)) T.ins(a[r].x, a[r].y), ++r;
  FOR(i,1,m) {
    while (r <= n && flt(a[r].al, b[i].al + M_PI)) {
      T.ins(a[r].x, a[r].y);
      ++r;
    }
    while (l <= n && fle(a[l].al, b[i].al)) {
      T.del(a[l].x, a[l].y);
      ++l;
    }
    ans[b[i].id] = T.sum();
  }
  if (m <= q) {
    while (r <= n) T.ins(a[r].x, a[r].y), ++r;
    while (l <= n && fle(a[l].al, 0)) T.del(a[l].x, a[l].y), ++l;
    r = l;
    l = 1;
    FOR(i, m, q) {
      while (l <= n && flt(a[l].al, b[i].al - M_PI)) {
        T.ins(a[l].x, a[l].y);
        ++l;
      }
      while (r <= n && fle(a[r].al, b[i].al)) {
        T.del(a[r].x, a[r].y);
        ++r;
      }
      ans[b[i].id] = T.sum();
    }
  }
  FOR(i,1,q) O(ans[i]);
}
}

inline void solve() {
  rd(n,q);
  FOR(i,1,n) rd(x[i], y[i]);
  if (n <= 1005 && q <= 1005) sub1::work();
  else {
    bool op1 = 1, op2 = 1;
    FOR(i,1,q) {
      rd(A[i], B[i], C[i]);
      if (A[i] != 0) op1 = 0;
      if (C[i] != 0) op2 = 0;
    }
    if (op1) sub2::work();
    else if (op2) sub3::work();
    else O("F u lxl");
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

