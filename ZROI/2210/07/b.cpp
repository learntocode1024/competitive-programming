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
const int N = 1.5e4+5, Q = 1e5+5;
i64 ans[Q];
int n, m, q;
int a[N];
struct sgt {
  struct node {
    int mx, se, c, tg;
    i64 s;
  } a[N<<2];
  inline void down(int p) {
    int &tg = a[p].tg;
    if (tg) {
      if (a[p<<1].mx >= a[p<<1|1].mx) {
        a[p<<1].s += 1ll * tg * a[p<<1].c;
        a[p<<1].tg += tg;
        a[p<<1].mx += tg;
      }
      if (a[p<<1|1].mx >= a[p<<1].mx) {
        a[p<<1|1].s += 1ll * tg * a[p<<1|1].c;
        a[p<<1|1].tg += tg;
        a[p<<1|1].mx += tg;
      }
      tg = 0;
    }
  }
  inline void up(int p) {
    a[p].s = a[p<<1].s + a[p<<1|1].s;
    if (a[p<<1].mx == a[p<<1|1].mx) {
      a[p].mx = a[p<<1].mx;
      a[p].se = max(a[p<<1].se, a[p<<1|1].se);
      a[p].c = a[p<<1].c + a[p<<1|1].c;
    } else if (a[p<<1].mx > a[p<<1|1].mx) {
      a[p].mx = a[p<<1].mx;
      a[p].se = max(a[p<<1].se, a[p<<1|1].mx);
      a[p].c = a[p<<1].c;
    } else {
      a[p].mx = a[p<<1|1].mx;
      a[p].se = max(a[p<<1|1].se, a[p<<1].mx);
      a[p].c = a[p<<1|1].c;
    }
  }
  void chk(int p, int l, int r, int s, int t, int v) {
    if (v >= a[p].mx) return;
    if (s == l && r == t && v > a[p].se) {
      int tt = a[p].mx - v;
      a[p].mx = v;
      a[p].tg -= tt;
      a[p].s -= 1ll * tt * a[p].c;
      return;
    }
    int m = (l + r) >> 1;
    down(p);
    if (s < m) chk(p<<1,l,m,s,min(m,t),v);
    if (t > m) chk(p<<1|1,m,r,max(s,m),t,v);
    up(p);
  }
  i64 sum(int p, int l, int r, int s, int t) {
    if (s == l && r == t) {
      return a[p].s;
    }
    int m = (l + r) >> 1;
    down(p);
    i64 ret = 0;
    if (s < m) ret += sum(p<<1,l,m,s,min(m,t));
    if (t > m) ret += sum(p<<1|1,m,r,max(s,m),t);
    return ret;
  }
  void build(int p, int l, int r) {
    a[p].tg = 0;
    if (r - l == 1) {
      a[p].mx = a[p].s = ::a[l];
      a[p].c = 1;
      a[p].se = 0;
      return;
    }
    int m = (l+r)>>1;
    build(p<<1,l,m);
    build(p<<1|1,m,r);
    up(p);
  }
} T;
int l[N], r[N], x[N];
int tot;

struct qry {
  int l1, r1, l2, r2, id;
  bool operator< (const qry &r) const {
    return l1 < r.l1;
  }
} qy[Q];
vector<qry> g[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());



inline void solve() {
  rd(n,m,q);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,m) {
    rd(l[i], r[i], x[i]);
  }
  FOR(i,1,q) {
    rd(qy[i].l1, qy[i].r1, qy[i].l2, qy[i].r2);
    qy[i].id = i;
  }
  sort(qy+1, qy+q+1);
  g[++tot].pb(qy[1]);
  FOR(i,2,q) {
    bool ok = 0;
    FOR(j,1,tot) if (qy[i].r1 <= g[j].rbegin()->r1) {
      g[j].pb(qy[i]);
      ok = 1;
      break;
    }
    if (!ok) g[++tot].pb(qy[i]);
  }
  FOR(i,1,tot) {
    reverse(begin(g[i]), end(g[i]));
    int l = g[i][0].l1, r = l - 1;
    T.build(1,1,n+1);
    for (auto x : g[i]) {
#define run(d) T.chk(1,1,n+1,::l[d], ::r[d]+1,::x[d]);
      vector<int> cur;
      while (r < x.r1) cur.pb(++r);
      while (l > x.l1) cur.pb(--l);
      shuffle(begin(cur), end(cur), rng);
      for (auto v : cur) run(v);
      ans[x.id] = T.sum(1,1,n+1,x.l2,x.r2+1);
    }
  }
  FOR(i,1,q) O(ans[i]);
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

