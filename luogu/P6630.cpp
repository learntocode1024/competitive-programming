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
const int N = 2e5+5;
const i64 p = 998244353;
i64 n, k;

i64 q;

inline i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

inline void red(i64 &x) { if (x >= p) x -= p; }

struct mat {
  i64 a[3][3];
  mat() { memset(a, 0, sizeof(a)); }
  const i64* operator[] (const int k) const { return a[k]; }
  i64* operator[] (const int k) { return a[k]; }
  mat operator* (const mat &rhs) {
    mat ret;
    FOR(i, 0, 3) FOR(j, 0, 3) FOR(k, 0, 3)
      red(ret[i][k] += a[i][j] * rhs[j][k] % p);
    return ret;
  }
  mat operator+ (const mat &rhs) {
    mat ret = *this;
    FOR(i, 0, 3) FOR(j, 0, 3)
      red(ret[i][j] += rhs[i][j]);
    return ret;
  }
  mat operator* (const i64 rhs) {
    mat ret = *this;
    FOR(i, 0, 3) FOR(j, 0, 3) ret[i][j] = ret[i][j] * rhs % p;
    return ret;
  }
  inline friend i64 calc(mat x) {
    int kk = k;
    mat ret;
    ret[0][0] = ret[1][1] = ret[2][2] = 1;
    while (kk) {
      if (kk & 1) ret = ret * x;
      x = x * x;
      kk >>= 1;
    }
    return ret[0][2];
  }
} m1, m2, m3, m4, m5;
i64 ans;

inline i64 c2(i64 x) { return x * (x + 1) / 2 % p; }

int L[N], R[N], lc[N], rc[N], tot = 1;

void build(int p, int l, int r) {
  L[p] = l, R[p] = r;
  if (l == r) return;
  int m = rd();
  lc[p] = ++tot;
  build(lc[p], l, m);
  rc[p] = ++tot;
  build(rc[p], m + 1, r);
}

void work(int _p, int fl, int fr) {
  i64 l = L[_p], r = R[_p];
  i64 p1, p2, p3, p4, p5;
  p1 = (l * (n - r + 1) % p) * q % p;
  p2 = (c2(r - l + 1) + p - 1) * q % p;
  p3 = (fl * (n - fr + 1) % p) * q % p;
  p4 = ((l == fl) ? c2(fr - r) : c2(l - fl)) * q % p;
  p5 = (1 + 4 * p - p1 - p2 - p3 - p4) % p;
  p1 = (p1 + p - p3) % p;
  if (_p == 1) p1 = q, p2 = p - q, p3 = p4 = p5 = 0;
  mat cur = m1 * p1 + m2 * p2 + m3 * p3 + m4 * p4 + m5 * p5;
  red(ans += calc(cur));
  if (l == r) return;
  work(lc[_p], l, r);
  work(rc[_p], l, r);
}

void solve() {
  m5[0][0] = m5[1][1] = m5[2][2] = 1;
  m4[0][1] = m4[1][1] = m4[2][2] = 1;
  m3[0][0] = m3[1][2] = m3[2][2] = 1;
  m2[2][2] = 1;
  m1[0][2] = m1[2][2] = 1;
  n = rd(), k = rd();
  q = q_pow(n * (n + 1) / 2, p - 2);
  build(1, 1, n);
  work(1, 1, n);
  cout << ans << '\n';
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
