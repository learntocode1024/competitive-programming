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

void E(long long &x, long long y) { x ^= y; x ^= x >> 12; x ^= x << 25; x ^= x >> 27; }
const int N = 4005;
const i64 inf = 6e17;
int n;
i64 f[N][N];
int r[N], c[N];
i64 rv[N], cv[N];
i64 g[N][N];

namespace segT {
const int N = ::N<<2;
i64 a[N], tg[N];
i64 A[N];
int L, R;
void build(int p, int l, int r) {
  tg[p] = 0;
  if (r - l == 1) {
    a[p] = A[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(p<<1, l, mid);
  build(p<<1|1, mid, r);
  a[p] = max(a[p<<1], a[p<<1|1]);
}
i64 V;
void _add(int p, int l, int r, int s, int t) {
  if (l == s && r == t) {
    a[p] += V;
    tg[p] += V;
    return;
  }
  if (tg[p]) {
    a[p<<1] += tg[p];
    a[p<<1|1] += tg[p];
    tg[p<<1] += tg[p];
    tg[p<<1|1] += tg[p];
    tg[p] = 0;
  }
  int mid = (l + r) >> 1;
  if (s < mid) _add(p<<1, l, mid, s, min(t, mid));
  if (t > mid) _add(p<<1|1, mid, r, max(s, mid), t);
  a[p] = max(a[p<<1], a[p<<1|1]);
}

inline void init(int l, int r) {
  L = l;
  R = r + 1;
  build(1, L, R);
}
inline i64 val() {
  return a[1];
}
inline void add(int r, i64 v) {
  if (r < L || r >= R) return;
  V = v;
  _add(1, L, R, L, r + 1);
}
}
using segT::A;
using segT::init;
using segT::val;
using segT::add;

void work(int c1, int c2, int r1, int r2) {
  if (c1 == c2 && r1 == r2) return;
  if (r2 - r1 > c2 - c1) {
    int mid = (r2 + r1) >> 1;
    work(c1, c2, r1, mid);
    for (int cl = c1 + 1; cl <= c2; ++cl) {
      for (int i = r1; i <= mid; ++i) {
        A[i] = f[i][cl - 1];
      }
      init(r1, mid);
      for (int cr = cl; cr <= c2; ++cr) {
        add(c[cr], cv[cr]);
        g[cl][cr] = val();
      }
    }
    for (int j = c1; j <= c2; ++j) {
      for (int k = c1; k <= j; ++k) {
        A[k] = g[k][j];
      }
      init(c1, j);
      for (int i = mid + 1; i <= r2; ++i) {
        add(r[i], rv[i]);
        chkmax(f[i][j], val());
      }
    }
    work(c1, c2, mid + 1, r2);
  } else {
    int mid = (c2 + c1) >> 1;
    work(c1, mid, r1, r2);
    for (int i = r1 + 1; i <= r2; ++i) {
      for (int k = c1; k <= mid; ++k) {
        A[k] = f[i - 1][k];
      }
      init(c1, mid);
      for (int j = i; j <= r2; ++j) {
        add(r[j], rv[j]);
        g[i][j] = val();
      }
    }
    for (int i = r1; i <= r2; ++i) {
      for (int k = r1; k <= i; ++k) {
        A[k] = g[k][i];
      }
      init(r1, i);
      for (int j = mid + 1; j <= c2; ++j) {
        add(c[j], cv[j]);
        chkmax(f[i][j], val());
      }
    }
    work(mid + 1, c2, r1, r2);
  }
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n + 1) FOR(j, 0, n + 1) f[i][j] = -inf;
  f[0][0] = 0;
  FOR(i, 1, n + 1) {
    int p;
    i64 ww;
    rd(p, ww);
    r[i] = p;
    rv[i] = ww;
    c[p] = i;
    cv[p] = ww;
  }
  // if (r[1] == 1) f[1][1] = rv[1];
  work(0, n, 0, n);
  i64 ans = 0;
  FOR(i, 1, n + 1) FOR(j, 1, n + 1) E(ans, f[i][j]), cerr << f[i][j] << " \n"[j == n];
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

