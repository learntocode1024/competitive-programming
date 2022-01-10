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
const int N = 5e4+5, Q = 2e5+5;
const i64 C = 6e13;
int n, m, q;
i64 ans[Q];

struct sgT {
  struct {
    i64 a, b, ta, tb;
  } a[N<<2];
  inline void dwn(int p, i64 ta, i64 tb) {
    chkmax(a[p].b, a[p].a + tb);
    a[p].a += ta;
    chkmax(a[p].tb, tb + a[p].ta);
    a[p].ta += ta;
  }
  inline void down(int p) {
    dwn(p<<1, a[p].ta, a[p].tb);
    dwn(p<<1|1, a[p].ta, a[p].tb);
    a[p].ta = a[p].tb = 0;
  }
  void up(int p) {
    a[p].a = max(a[p<<1].a, a[p<<1|1].a);
    a[p].b = max(a[p<<1].b, a[p<<1|1].b);
  }
  inline void clr(int p = 1, int l = 1, int r = n + 1) {
    a[p] = {};
    if (r - l == 1) return;
    int mid = (l + r) >> 1;
    clr(p<<1, l, mid);
    clr(p<<1|1, mid, r);
  }
  void add(int p, int l, int r, int s, int t, i64 v) {
    if (l == s && r == t) {
      return dwn(p, v, v);
    }
    int mid = (l + r) >> 1;
    down(p);
    if (s < mid) add(p<<1, l, mid, s, min(mid, t), v);
    if (t > mid) add(p<<1|1, mid, r, max(mid, s), t, v);
    up(p);
  }
  i64 get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p].b;
    }
    down(p);
    int mid = (l + r) >> 1;
    i64 ret = 0;
    if (s < mid) chkmax(ret, get(p<<1, l, mid, s, min(mid, t)));
    if (t > mid) chkmax(ret, get(p<<1|1, mid, r, max(mid, s), t));
    return ret;
  }
} T;

int s[Q], t[Q];
struct tup {
  int l, r, c;
};
struct stat {
  int l, r;
  vector<tup> v;
};

queue<stat> f;
vector<tup> g[N];

void bfs() {
  int r0 = 0;
  i64 D = 0;
  while (!f.empty()) {
    stat c0, c1;
    stat c = f.front();
    f.pop();
    int l = c.l, r = c.r;
    int mid = (l + r) >> 1;
    if (r < r0) { // clear
      T.clr();
      D = 0;
      r0 = 0;
    }
    // scanner advance
    FOR(i, r0 + 1, r + 1) {
      for (auto v : g[i]) {
        T.add(1, 1, n + 1, v.l, v.r, v.c);
      }
      if (i == l) {
        // reset all time max
        D += C;
        T.add(1, 1, n + 1, 1, n + 1, C);
      }
    }
    r0 = r;
    // process querys
    for (auto v : c.v) {
      if (v.l == l && v.r == r) {
        chkmax(ans[v.c], (i64)(T.get(1, 1, n + 1, s[v.c], t[v.c]) - D));
      } else {
        if (v.r <= mid) c0.v.pb({v.l, v.r, v.c});
        else if (v.l > mid) c1.v.pb({v.l, v.r, v.c});
        else c0.v.pb({v.l, mid, v.c}), c1.v.pb({mid + 1, v.r, v.c});
      }
    }
    if (c0.v.size() || c1.v.size()) {
      c0.l = l;
      c0.r = mid;
      c1.l = mid + 1;
      c1.r = r;
      if (!c0.v.empty()) f.push(c0);
      if (!c1.v.empty()) f.push(c1);
    }
  }
}

inline void solve() {
  rd(n, m, q);
  FOR(i, 0, m) {
    int x, y, z, w, v;
    rd(x, y, z, w, v);
    g[x].pb({y, w + 1, v});
    g[z + 1].pb({y, w + 1, -v});
  }
  stat o;
  o.l = 1, o.r = n;
  FOR(i, 0, q) {
    int l, r;
    rd(l, s[i], r, t[i]);
    ++t[i];
    o.v.pb({l, r, i});
  }
  f.push(o);
  bfs();
  FOR(i, 0, q) println(ans[i]);
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
