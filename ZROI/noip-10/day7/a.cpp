/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
const int N = 1e5+5;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
int n;
int x[N], y[N];
int ans[N], ans1[N], ans2[N];

struct segT {
  struct node {
    int l, r;
    int x, y, xy, c;
  } a[N << 5];
  #define lc a[p].l
  #define rc a[p].r
  inline void up(int p) {
    red(a[p].x = a[lc].x + a[rc].x);
    red(a[p].y = a[lc].y + a[rc].y);
    red(a[p].xy = a[lc].xy + a[rc].xy);
    a[p].c = a[lc].c + a[rc].c;
  }
  int rt, tot;
  int x, y, xy, c;
  void _ins(int &p, int l, int r, int t) {
    if (p == 0) p = ++tot;
    if (r - l == 1) {
      red(a[p].x += x);
      red(a[p].y += y);
      red(a[p].xy += xy);
      a[p].c += c;
      return;
    }
    int mid = l + (r - l) / 2;
    if (t < mid) _ins(lc, l, mid, t);
    else _ins(rc, mid, r, t);
    up(p);
  }
  inline void ins(int pos, int _c, int _x, int _y, int _xy) {
    x = _x, y = _y, xy = _xy;
    c = _c;
    _ins(rt, 0, 1e9 + 1, pos);
  }
  node get(int p, int l, int r, int s, int t) {
    if (!p) return a[p];
    if (s == l && t == r) {
      return a[p];
    }
    int mid = l + (r - l) / 2;
    if (t <= mid) return get(lc, l, mid, s, t);
    if (s >= mid) return get(rc, mid, r, s, t);
    auto t1 = get(lc, l, mid, s, mid);
    auto t2 = get(rc, mid, r, mid, t);
    red(t1.x += t2.x);
    red(t1.y += t2.y);
    red(t1.xy += t2.xy);
    t1.c += t2.c;
    return t1;
  }
  node pre(int pos) {
    return get(rt, 0, 1e9+1, 0, pos + 1);
  }
  node suf(int pos) {
    return get(rt, 0, 1e9+1, pos, 1e9+1);
  }
} T;

int b[N];

void cdq(int l, int r) {
  if (r - l == 1) return;
  int mid = l + (r - l) / 2;
  cdq(l, mid);
  cdq(mid, r);
  for (int i = mid; i < r; ++i) {
    int u = b[i];
    T.ins(y[u], 1, x[u], y[u], x[u] * y[u] % p);
  }
  for (int i = l; i < mid; ++i) {
    int u = b[i];
    auto tu = T.suf(y[u]);
    i64 cur = 1ll * tu.c * x[u] % p * y[u] - 1ll * x[u] * tu.y - 1ll * y[i] * tu.x + tu.xy;
    if (cur < 0) cur += p;
    cur %= p;
    red(ans1[u] += cur);
  }
  for (int i = mid; i < r; ++i) {
    int u = b[i];
    T.ins(y[u], -1, p - x[u], p - y[u], p - x[u] * y[u] % p);
  }
  for (int i = l; i < mid; ++i) {
    int u = b[i];
    T.ins(y[u], 1, x[u], y[u], x[u] * y[u] % p);
  }
  for (int i = mid; i < r; ++i) {
    int u = b[i];
    auto tu = T.pre(y[u]);
    i64 cur = 1ll * x[u] * y[u] - 1ll * x[u] * tu.y - 1ll * y[i] * tu.x + tu.xy;
    if (cur < 0) cur += p;
    cur %= p;
    red(ans1[u] += cur);
  }
  for (int i = l; i < mid; ++i) {
    int u = b[i];
    T.ins(y[u], -1, p - x[u], p - y[u], p - x[u] * y[u] % p);
  }
}

void solve() {
  n = rd();
  FOR(i, 0, n) x[i] = rd(), y[i] = rd();
  int sx1 = 0, sx2 = 0, sy1 = 0, sy2 = 0, sxy = 0;
  FOR(i, 0, n) red(sx1 += x[i]), red(sx2 += 1ll * x[i] * x[i] % p), red(sy1 += y[i]), red(sy2 += 1ll * y[i] * y[i] % p), red(sxy += 1ll * x[i] * y[i] % p);
  FOR(i, 0, n) ans[i] = 1ll * n * x[i] % p * x[i] % p + 1ll * n * y[i] % p * y[i] % p - 2ll * x[i] * sx1 % p - 2ll * y[i] * sy1 % p + p * 2 + sy2 + sx2;
  FOR(i, 0, n) ans[i] %= p;
  FOR(i, 0, n) ans2[i] = (1ll * n * x[i] % p * y[i] % p + p - 1ll * x[i] * sy1 % p + p - 1ll * y[i] * sx1 % p + sxy) % p;
  iota(b, b + n, 0);
  sort(b, b + n, [] (int a, int b) { return x[a] < x[b]; });
  cdq(0, n);
  FOR(i, 0, n) red(ans[i] += (ans1[i] * 2 + p - ans2[i]) % p * 2 % p);
  FOR(i, 0, n) cout << ans[i] << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
