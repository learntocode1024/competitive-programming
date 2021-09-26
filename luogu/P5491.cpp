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
#define MULTI
const int N = 0;

int q_pow(i64 x, int a, int p) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

int cipolla(int n, int p) { // p is an odd prime
  if (q_pow(n, (p-1)>>1, p) == p - 1) return -1;
  if (n == 0) return 0;
  srand(time(0));
  i64 a, w = -1;
  while (w == -1) {
    a = rand() % (p - 1) + 1;
    w = (a * a - n + p) % p;
    if (q_pow(w, (p-1)>>1, p) == 1) w = -1;
  }
  int t = (p+1) >> 1;
  pair<i64, i64> x(1, 0), y(a, 1);
  auto mul = [w, p] (pair<i64, i64> a, pair<i64, i64> b) {
    pair<i64, i64> ret;
    ret.fi = (a.fi * b.fi + a.se * b.se % p * w) % p;
    ret.se = (a.fi * b.se + a.se * b.fi) % p;
    return ret;
  };
  while (t) {
    if (t & 1) x = mul(x, y);
    y = mul(y, y);
    t >>= 1;
  }
  return x.fi;
}

void solve() {
  int n = rd(), p = rd();
  int ans = cipolla(n, p);
  if (ans == -1) cout << "Hola!\n";
  else if (ans == 0) cout << ans << '\n';
  else cout << min(ans, p - ans) << ' ' << max(ans, p - ans) << '\n';
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
