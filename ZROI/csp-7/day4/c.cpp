/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 26];  // sizeof in varied in problem
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
const int N = 1000005;
int x[N], y[N];
int P, Q;
int n;

inline bool lt(i64 m, i64 n, i64 p, i64 q) {
  return (__int128)m * q < (__int128)p * n;
}
namespace pt50 {
void solve() {
  int p1 = 1, q1 = 0, p2 = -1, q2 = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int dx = x[i] - x[j], dy = y[i] - y[j];
      if ((dx < 0 && dy > 0) || (dy < 0 && dx > 0)) continue;
      if (dx <= 0 && dy <= 0) dx = -dx, dy = -dy;
      if (lt(dy, dx, p1, q1) && lt(P, Q, dy, dx)) p1 = dy, q1 = dx;
      if (lt(dy, dx, P, Q) && lt(p2, q2, dy, dx)) p2 = dy, q2 = dx;
    }
  }
  int p, q;
  i64 pp1 = 1ll * p1 * Q - q1 * P, qq1 = 1ll * Q * q1;
  i64 pp2 = 1ll * q2 * P - p2 * Q, qq2 = 1ll * Q * q2;
  if (lt(pp1, qq1, pp2, qq2)) {
    p = p1, q = q1;
  } else {
    p = p2, q = q2;
  }
  int x = __gcd(p, q);
  p /= x, q /= x;
  cout << p << '/' << q << '\n';
}
}

namespace en {
using f80 = long double;
pair<f80, int> yy[N];
int pos[N];
const int prec = 20;
void solve() {
  f80 k = P;
  k /= Q;
  for (int i = 0; i < n; ++i) {
    f80 c = y[i], d = x[i];
    yy[i] = mkp(c - d * k, i);
  }
  sort(yy, yy + n);
  for (int i = 0; i < n; ++i) {
    pos[yy[i].se] = i;
  }
  int p1 = 1, q1 = 0, p2 = -1, q2 = 0;
  for (int i = 0; i < n; ++i) {
    for (int k = max(0, pos[i] - prec); k < min(pos[i] + prec, n); ++k) {
      if (k == pos[i]) continue;
      int j = yy[k].se;
      int dx = x[i] - x[j], dy = y[i] - y[j];
      if ((dx < 0 && dy > 0) || (dy < 0 && dx > 0)) continue;
      if (dx <= 0 && dy <= 0) dx = -dx, dy = -dy;
      if (lt(dy, dx, p1, q1) && lt(P, Q, dy, dx)) p1 = dy, q1 = dx;
      if (lt(dy, dx, P, Q) && lt(p2, q2, dy, dx)) p2 = dy, q2 = dx;
    }
  }
  int p, q;
  i64 pp1 = 1ll * p1 * Q - q1 * P, qq1 = 1ll * Q * q1;
  i64 pp2 = 1ll * q2 * P - p2 * Q, qq2 = 1ll * Q * q2;
  if (lt(pp1, qq1, pp2, qq2)) {
    p = p1, q = q1;
  } else {
    p = p2, q = q2;
  }
  int x = __gcd(p, q);
  p /= x, q /= x;
  cout << p << '/' << q << '\n';
}
}

void solve() {
  n = rd(), P = rd(), Q = rd();
  FOR(i, 0, n) x[i] = rd(), y[i] = rd();
  if (n <= 1000) pt50::solve();
  else en::solve();
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
