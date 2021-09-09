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
#define MULTI
const int N = 2000005;
int a[N], b[N];
int cx[N], cy[N];
int n, m, k;

int buc[N];
int pos[N], tot;
pii tmp[N];

inline i64 C(i64 x) {
  if (x <= 1) return 0ll;
  return ((x - 1) * x) >> 1;
}

int x[N], y[N];

i64 calc(int n, int *a, int *ix, int *iy) {
  FOR(i, 0, k) tmp[i].fi = ix[i], tmp[i].se = iy[i];
  sort(tmp, tmp + k);
  FOR(i, 0, k) x[i] = tmp[i].fi, y[i] = tmp[i].se;
  int l = 0, r = -1;
  i64 ret = 0;
  FOR(i, 0, n - 1) {
    while (l < k && x[l] <= a[i]) ++l;
    while (r < k && x[r + 1] < a[i + 1]) ++r;
    int cnt = 0;
    FOR(j, l, r + 1) {
      if (j >= k) break;
      ++cnt;
      if (buc[y[j]] == 0) pos[++tot] = y[j];
      ++buc[y[j]];
    }
    ret += C(cnt);
    for (int j = 1; j <= tot; ++j) {
      ret -= C(buc[pos[j]]);
      buc[pos[j]] = 0;
    }
    tot = 0;
  }
  return ret;
}

void solve() {
  n = rd(); m = rd(), k = rd();
  FOR(i, 0, n) a[i] = rd();
  FOR(i, 0, m) b[i] = rd();
  FOR(i, 0, k) cx[i] = rd(), cy[i] = rd();
  cout << calc(n, a, cx, cy) + calc(m, b, cy, cx) << '\n';
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
