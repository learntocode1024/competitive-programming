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
const int N = 1000005;
i64 a[N];
const i64 mod = 1e9 + 7;
int Q_pow(i64 a, int k) { 
  i64 ret = 1;
  while (k) {
    if (k & 1) ret = ret * a % mod;
    a = a * a % mod;
    k >>= 1;
  }
  return ret;
}
int low[N], p[N], tot;
inline void red(i64 &x) { if (x >= mod) x -= mod; };

i64 b[N], c[N];
i64 inv[N];
i64 ifac[N];

void solve() {
  int n = rd(), k = rd();
  a[1] = 1;
  for (int i = 2; i <= k + 2; ++i) {
    if (!low[i]) {
      low[i] = i;
      p[tot++] = i;
      a[i] = Q_pow(i, k);
    }
    for (int j = 0; j < tot && p[j] <= low[i] && p[j] * i <= k + 2; ++j) {
      a[p[j] * i] = a[i] * a[p[j]] % mod;
      low[p[j] * i] = p[j];
    }
  }
  for (int i = 2; i <= k + 2; ++i) red(a[i] += a[i - 1]);
  if (n <= k + 2) {
    cout << a[n] << '\n';
    return;
  }
  // lagrange
  i64 ans = 0;
  b[0] = 1;
  FOR(i, 1, k + 3) b[i] = (b[i-1] * (n - i)) % mod;
  c[k + 3] = 1;
  ROF(i, 1, k + 3) c[i] = (c[i+1] * (n - i)) % mod;
  inv[1] = 1, ifac[1] = 1, ifac[0] = 1;
  FOR(i, 2, k + 3){
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
  for (int i = 1; i <= k + 2; ++i) {
    i64 cur = a[i];
    cur = cur * c[i + 1] % mod * b[i - 1] % mod;
    i64 gt = ifac[i - 1] * ifac[k + 2 - i] % mod;
    if ((k - i + 2) & 1) gt = mod - gt;
    ans = (ans + cur * gt) % mod;
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
