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
const int N = 100005;
i64 c[N], ac[N], sc[N];
int blk[N];

struct DS {
  i64 a[N];
  i64 mx[N];
  int pf[N], sf[N];
  void init() {
    for (int i = 1; i <= n; ++i) {
      if (a[i] && !a[i - 1]) pf[i] = i;
      pf[i] = pf[i - 1];
    }
    for (int i = n; i; --i) {
      if (a[i] && !a[i + 1]) sf[i] = i;
      sf[i] = sf[i + 1];
    }
    int i = 1;
    i64 sum = 0;
    while (i <= n) {
      if (blk[i] != blk[i - 1]) sum = 0;
      
    }
  }
} T1, T2;

void solve() {
  int n = rd(), q = rd();
  int B = sqrt(n) + 1;
  for (int i = 1; i <= n; ++i) {
    blk[i] = blk[i - 1];
    if (i % B == 1) ++blk[i];
  }
  FOR(i, 1, n + 1) c[i] = rd();
  FOR(i, 1, n + 1) c[i] -= rd();
  FOR(i, 1, n + 1) {
    ac[i] = abs(c[i]);
    if (c[i] > 0) T1.a[i] = c[i];
    else T2.a[i] = -c[i];
    sc[i] = sc[i - 1] + c[i];
  }
  T1.init();
  T2.init();
  while (q--) {
    int l = rd(), r = rd();
    if (sc[r] != sc[l - 1]) {
      puts("-1");
    } else {
      cout << max(T1.get(l, r), T2.get(l, r)) << '\n';
    }
  }
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
