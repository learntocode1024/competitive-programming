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
#define popcnt __builtin_popcountll
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

const int N = 1e6+5, B = 64;

int n;
i64 a[N];
int q1[N], q2[N];
struct qry {
  int i, l, r;
  bool operator< (const qry& r) const {
    return i < r.i;
  }
};
vector<qry> g[B];

struct {
  struct node {
    int mx, s, tg;
  } a[N<<2];
  void clear(int p = 1, int l = 1, int r = n + 1) {
    if (r - l == 1) {
      a[p] = {0,1,0};
      return;
    }
    a[p] = {0,r-l,0};
    int mid = (l + r) >> 1;
    clear(p<<1, l, mid);
    clear(p<<1|1, mid, r);
  }
  int V;
  inline void _down(int p, int v) {
    a[p].mx += v;
    a[p].tg += v;
  }
  inline void down(int p) {
    if (a[p].tg != 0) {
      _down(p<<1, a[p].tg);
      _down(p<<1|1, a[p].tg);
      a[p].tg = 0;
    }
  }
  inline void up(int p) {
    a[p].mx = max(a[p<<1].mx, a[p<<1|1].mx);
    a[p].s = 0;
    if (a[p<<1].mx == a[p].mx) a[p].s += a[p<<1].s;
    if (a[p<<1|1].mx == a[p].mx) a[p].s += a[p<<1|1].s;
  }
  void ch(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      _down(p, V);
      return;
    }
    down(p);
    int mid = (l + r) >> 1;
    if (s < mid) ch(p<<1, l, mid, s, min(mid, t));
    if (t > mid) ch(p<<1|1, mid, r, max(mid, s), t);
    up(p);
  }
  inline void add(int l, int r) {
    V = 1;
    ch(1, 1, n + 1, l, r + 1);
  }
  inline void sub(int l, int r) {
    V = -1;
    ch(1, 1, n + 1, l, r + 1);
  }
} T;

inline void solve() {
  cin >> n;
  FOR(i, 0, n) cin >> a[i + 1];
  int t = 0, t1 = 0;
  for (int i = 1; i <= n; ++i) {
    while (t && a[q1[t]] >= a[i]) {
      g[popcnt(a[q1[t]])].pb({i, q1[t - 1] + 1, -q1[t]});
      --t;
    }
    g[popcnt(a[i])].pb({i, q1[t] + 1, i});
    q1[++t] = i;
    while (t1 && a[q2[t1]] <= a[i]) {
      g[popcnt(a[q2[t1]])].pb({i, q2[t1 - 1] + 1, -q2[t1]});
      --t1;
    }
    g[popcnt(a[i])].pb({i, q2[t1] + 1, i});
    q2[++t1] = i;
  }
  i64 ans = 0;
  FOR(_, 0, B) {
    T.clear();
    int p = 0;
    int nn = g[_].size();
    for (int i = 1; i <= n; ++i) {
      while (p < nn && g[_][p].i == i) {
        if (g[_][p].r < 0) {
          T.sub(g[_][p].l, -g[_][p].r);
        } else {
          T.add(g[_][p].l, g[_][p].r);
        }
        ++p;
      }
      if (T.a[1].mx == 2) ans += T.a[1].s;
    }
  }
  println(ans);
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
