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

const int N = 1.5e5+5;
const int p = 1e9+7;
inline void red(i64 &x) {
  if (x >= p) x -= p;
}
i64 inv[N] = {0, 1};
int n;
int a[N];

struct segT {
  int T = 0;
  struct node {
    i64 a, b;
    i64 tg, tb;
  } a[N<<2];
#define lc (o<<1)
#define rc (o<<1|1)
  inline void up(int o) {
    red(a[o].a = a[lc].a + a[rc].a);
    red(a[o].b = a[lc].b + a[rc].b);
  }
  inline void _down(int o, i64 tg, i64 tb) {
    red(a[o].tb += a[o].tg * tb % p);
    a[o].tg = a[o].tg * tg % p;
    red(a[o].b += p - tb * a[o].a % p);
    a[o].a = a[o].a * tg % p;
  }
  inline void down(int o) {
    if (a[o].tg != 1 || a[o].tb != 0) {
      _down(lc, a[o].tg, a[o].tb);
      _down(rc, a[o].tg, a[o].tb);
      a[o].tg = 1;
      a[o].tb = 0;
    }
  }
  void build(int o = 1, int l = 1, int r = n + 1) {
    a[o].tg = 1;
    a[o].tb = 0;
    if (r - l == 1) {
      a[o].a = 1;
      a[o].b = 0;
      return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid, r);
    up(o);
  }
  i64 V;
  void ch(int o, int l, int r, int s, int t) {
    if (s == l && r == t) {
      _down(o, V, (p + V - 1) * T % p);
      return;
    }
    down(o);
    int mid = (l + r) >> 1;
    if (s < mid) ch(lc, l, mid, s, min(mid, t));
    if (t > mid) ch(rc, mid, r, max(s, mid), t);
    up(o);
  }
  i64 get(int o, int l, int r, int s, int t) {
    if (s == l && r == t) {
      return (a[o].a * T + a[o].b) % p;
    }
    down(o);
    int mid = (l + r) >> 1;
    i64 ret = 0;
    if (s < mid) ret = get(lc, l, mid, s, min(mid, t));
    if (t > mid) red(ret += get(rc, mid, r, max(s, mid), t));
    return ret;
  }
  inline void mul(int l, int r, i64 v) {
    V = v;
    ch(1, 1, n + 1, l, r + 1);
  }
  inline i64 sum(int l, int r) {
    return get(1, 1, n + 1, l, r + 1);
  }
  inline void advance() { ++T; }
} T;

struct qry {
  int l, r, id;
};
vector<qry> q[N];
i64 ans[N];
inline i64 delta(int l, int r, int e) {
  if (e < l) return 1ll * e * (r - l + 1);
  i64 ret = 1ll * (l - 1) * (r - l + 1);
  int L = r - l;
  int R = max(1, r - e);
  return ret + 1ll * (L + R) * (L - R + 1) / 2;
}

int q1[N], q2[N], t1, t2;

inline void solve() {
  int Q;
  cin >> n >> Q;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 2, n + 1) inv[i] = inv[p % i] * (p - p / i) % p;
  for (int i = 1; i <= Q; ++i) {
    int l, r, s, e;
    rd(l, r, s, e);
    q[s - 1].pb(qry{l, r, -i});
    red(ans[i] += delta(l, r, s - 1) % p);
    q[e].pb(qry{l, r, i});
    red(ans[i] += p - delta(l, r, e) % p);
  }
  T.build();
  for (int i = 1; i <= n; ++i) {
    while (t1 && a[q1[t1]] >= a[i]) {
      T.mul(q1[t1 - 1] + 1, q1[t1], inv[a[q1[t1]]]);
      --t1;
    }
    T.mul(q1[t1] + 1, i, a[i]);
    q1[++t1] = i;
    while (t2 && a[q2[t2]] <= a[i]) {
      T.mul(q2[t2 - 1] + 1, q2[t2], inv[a[q2[t2]]]);
      --t2;
    }
    T.mul(q2[t2] + 1, i, a[i]);
    q2[++t2] = i;
    T.advance();
    for (auto v : q[i]) {
      if (v.id < 0) {
        red(ans[-v.id] += p - T.sum(v.l, v.r));
      } else {
        red(ans[v.id] += T.sum(v.l, v.r));
      }
    }
  }
  FOR(i, 1, Q + 1) cout << ans[i] << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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
