/** @file
 * @ingroup segtree binary_lifting
记录每一条鱼能吃到的区间，这些区间有如下性质
1. 区间之间只能包含或不交。
2. 对于在一个区间对应的任意一条鱼， 其能吃到的区间一定也包含在该区间中
3. 每一条鱼至多被包含在$O(\log \max A)$个区间中
修改：暴力删除该位置对应的区间，线段树上二分，分别查找新形成的区间可能的左右端点，并检查这$O(log^2 \max A)$个区间的合法性，进行插入。
查询：
由于是区间查询，将在区间截断处额外产生一些区间，同样找出可能的左/右端点，排除掉即可。
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
const int N = 1e5+7;

i64 a[N];
i64 _a[N];
int n;

struct segV {
  struct node {
    i64 s, t;
  } a[N<<2];
  inline void down(const int &p) {
    a[p<<1].s += a[p].t;
    a[p<<1|1].s += a[p].t;
    a[p<<1].t += a[p].t;
    a[p<<1|1].t += a[p].t;
    a[p].t = 0;
  }
  inline void up(int p) {
    a[p].s = max(a[p<<1].s, a[p<<1|1].s);
  }
  void add(int p, int l, int r, int s, int t, i64 v) {
    if (l == s && r == t) return a[p].s += v, a[p].t += v, void();
    int m = (l + r) >> 1;
    down(p);
    if (s <= m) add(p<<1, l, m, s, min(m, t), v);
    if (t > m) add(p<<1|1, m+1, r, max(m+1,s), t, v);
    return up(p);
  }
  int pre(int p, int l, int r, int x, i64 v) {
    if (x <= l || a[p].s <= v) return 0;
    if (l == r) return l;
    int m = (l + r) >> 1;
    down(p);
    if (x <= m + 1 || a[p<<1|1].s <= v) return pre(p<<1, l, m, x, v);
    int to = pre(p<<1|1, m+1, r, x, v);
    if (!to) return pre(p<<1, l, m, x, v);
    return to;
  }
  int suf(int p, int l, int r, int x, i64 v) {
    if (x >= r || a[p].s <= v) return n+1;
    if (l == r) return l;
    int m = (l + r) >> 1;
    down(p);
    if (x >= m || a[p<<1].s <= v) return suf(p<<1|1, m+1, r, x, v);
    int to = suf(p<<1, l, m, x, v);
    if (to == n+1) return suf(p<<1|1, m+1, r, x, v);
    return to;
  }
  void build(int p = 1, int l = 1, int r = n) {
    if (l == r) return a[p].s = _a[l], void();
    int m = (l + r) >> 1;
    build(p<<1, l, m);
    build(p<<1|1, m+1, r);
    up(p);
  }
} TL, TR;

struct segTab {
  pii r[N];
  int frd[N], tot, ftot;
  struct node {
    unordered_set<int> s;
    pii v;
  } a[N<<2];
  void build(int p = 1, int l = 1, int r = n) {
    a[p].v = {0, r - l + 1};
    if (r == l) return;
    int m = (l + r) >> 1;
    build(p<<1, l, m);
    build(p<<1|1, m+1, r);
  }
  inline pii up(const pii &a, const pii &b) {
    if (a.fi > b.fi) return b;
    else if (a.fi < b.fi) return a;
    return {a.fi, a.se + b.se};
  }
  int buf[40], ctot;
  void _clr(int p, int l, int r, int x) {
    for (auto v : a[p].s) buf[ctot++] = v;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (x <= m) _clr(p<<1, l, m, x);
    else _clr(p<<1|1, m+1, r, x);
  }
  void _clr_(int p, int l, int r, int s, int t, int id) {
    if (l == s && r == t) {
      a[p].s.erase(id);
      --a[p].v.fi;
      return;
    }
    int m = (l + r) >> 1;
    if (s <= m) _clr_(p<<1, l, m, s, min(m, t), id);
    if (t > m) _clr_(p<<1|1, m+1, r, max(m+1, s), t, id);
    a[p].v = up(a[p<<1].v, a[p<<1|1].v);
    a[p].v.fi += a[p].s.size();
  }
  void ins(int p, int l, int r, int s, int t, int id) {
    if (l == s && r == t) {
      a[p].s.insert(id);
      ++a[p].v.fi;
      return;
    }
    int m = (l + r) >> 1;
    if (s <= m) ins(p<<1, l, m, s, min(m, t), id);
    if (t > m) ins(p<<1|1, m+1, r, max(m+1, s), t, id);
    a[p].v = up(a[p<<1].v, a[p<<1|1].v);
    a[p].v.fi += a[p].s.size();
  }
  pii get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return a[p].v;
    int m = (l + r) >> 1;
    pii ret;
    if (t <= m) ret = get(p<<1, l, m, s, t);
    else if (s > m) ret = get(p<<1|1, m+1, r, s, t);
    else ret = up(get(p<<1, l, m, s, m), get(p<<1|1, m+1, r, m+1, t));
    ret.fi += a[p].s.size();
    return ret;
  }

  inline void clr(int x) { 
    _clr(1,1,n,x);
    FOR(i,0,ctot-1) {
      _clr_(1,1,n,r[buf[i]].fi, r[buf[i]].se, buf[i]);
      frd[++ftot] = buf[i];
      err("delete segment [%d, %d]\n", r[buf[i]].fi, r[buf[i]].se);
    }
    ctot = 0;
    if (x > 1) {
      _clr(1,1,n,x-1);
      FOR(i,0,ctot-1) {
        if (r[buf[i]].se != x - 1) continue;
        _clr_(1,1,n,r[buf[i]].fi, r[buf[i]].se, buf[i]);
        frd[++ftot] = buf[i];
        err("delete segment [%d, %d]\n", r[buf[i]].fi, r[buf[i]].se);
      }
      ctot = 0;
    }
    if (x < n) {
      _clr(1,1,n,x+1);
      FOR(i,0,ctot-1) {
        if (r[buf[i]].fi != x + 1) continue;
        _clr_(1,1,n,r[buf[i]].fi, r[buf[i]].se, buf[i]);
        frd[++ftot] = buf[i];
        err("delete segment [%d, %d]\n", r[buf[i]].fi, r[buf[i]].se);
      }
      ctot = 0;
    }
  }

  inline void ins(int l, int rt) {
    int x = ftot ? frd[ftot--] : ++tot;
    ins(1,1,n,l,rt,x);
    r[x] = {l,rt};
    err("add segment [%d, %d]\n", l, rt);
  }

  inline int operator() (int l, int r) {
    return get(1,1,n,l,r).se;
  }
} S;


struct BIT {
  i64 c[N];
  inline void add(int x, i64 v) {
    for (; x <= n; x += x & -x) c[x] += v;
  }
  inline i64 get(int x) {
    i64 ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
  }
} sp;

int L[50], cl, R[50], cr;
i64 sL[50], sR[50];
inline void pre(int x) {
  i64 sx = sp.get(x);
  cl = 0;
  while (x) {
    x = TL.pre(1,1,n,x,sx);
    L[++cl] = x;
    sL[cl] = sp.get(x);
  }
}

inline void suf(int x) {
  i64 sx = -sp.get(x-1);
  cr = 0;
  while (x < n+1) {
    x = TR.suf(1,1,n,x,sx);
    R[++cr] = x;
    sR[cr] = sp.get(x-1);
  }
}

inline void upd(int x, i64 _y) {
  i64 y = _y - a[x];
  a[x] = _y;
  S.clr(x);
  TL.add(1,1,n,x,x,y);
  TL.add(1,1,n,x,n,y);
  if (x < n) TR.add(1,1,n,x+1,n,-y);
  TR.add(1,1,n,x,x,y);
  sp.add(x, y);
  pre(x), suf(x);
  FOR(i,1,cl) FOR(j,1,cr) {
    i64 cur = sR[j] - sL[i];
    if (cur < a[R[j]] && cur < a[L[i]]) S.ins(L[i]+1, R[j]-1);
  }
  if (x > 1) {
    pre(x-1);
    i64 sx = sp.get(x-1);
    FOR(i,1,cl) {
      i64 cur = sx - sL[i];
      if (cur < a[x] && cur < a[L[i]]) S.ins(L[i]+1, x-1);
    }
  }
  if (x < n) {
    suf(x+1);
    i64 sx = sp.get(x);
    FOR(i,1,cr) {
      i64 cur = sR[i] - sx;
      if (cur < a[x] && cur < a[R[i]]) S.ins(x+1, R[i]-1);
    }
  }
}

inline int qry(int l, int r) {
  pre(r);
  suf(l);
  FOR(i,1,cr) {
    if (R[i] <= r) ckmax(l, R[i]);
  }
  FOR(i,1,cl) {
    if (L[i] >= l) ckmin(r, L[i]);
  }
  if (r < l) return 0;
  return S(l,r);
}

inline void sol() {
  rd(n);
  a[0] = a[n+1] = 1e18;
  S.build();
  FOR(i,1,n) {
    int x;
    cin >> x;
    upd(i,x);
  }
  int q;
  cin >> q;
  while (q--) {
    int T, a, b;
    rd(T, a, b);
    if (T == 1) upd(a, b);
    else O(qry(a,b));
  }
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
