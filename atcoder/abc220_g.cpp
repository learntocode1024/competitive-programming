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
#include <map>
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
const int N = 1005;
using cr = tuple<i64, i64, i64>;
map<cr, map<pii, int> > mp;
int x[N], y[N], c[N];

cr get(i64 x1, i64 x2, i64 y1, i64 y2) {
  i64 a = 0, b = 0, c = 0;
  if (y1 == y2) {
    c = -x1 - x2;
    if (c % 2) {
      a = 2;
    } else {
      a = 1;
      c = c / 2;
    }
  } else if (x1 == x2) {
    c = -y1 - y2;
    if (c % 2) {
      b = 2;
    } else {
      b = 1;
      c = c / 2;
    }
  } else {
    a = 2 * (x1 - x2);
    b = 2 * (y1 - y2);
    c = - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2;
    i64 t = __gcd(abs(a), abs(b));
    t = __gcd(t, abs(c));
    if (a < 0) t = -t;
    a /= t;
    b /= t;
    c /= t;
  }
  return cr(a, b, c);
}

void solve() {
  int n = rd();
  FOR(i, 0, n) x[i] = rd(), y[i] = rd(), c[i] = rd();
  FOR(i, 0, n) FOR(j, 0, i) {
    chkmax(mp[get(x[i], x[j], y[i], y[j])][mkp(x[i] + x[j], y[i] + y[j])], c[i] + c[j]);
  }
  i64 ans = -1;
  for (auto &u : mp) {
    i64 m1 = 0, m2 = 0;
    if (u.se.size() < 2) continue;
    for (auto &v : u.se) {
      if (v.se > m1) m2 = m1, m1 = v.se;
      else if (v.se > m2) m2 = v.se;
    }
    chkmax(ans, m1 + m2);
  }
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
