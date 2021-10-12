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
const int N = 200005;
const int p = 998244353;
char s[N];
int n;
inline void red(int &x) { if (x >= p) x -= p; }
int q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

namespace ON2 {
int dp[N];
void work() {
  dp[0] = 1;
  reverse(s + 1, s + n + 1);
  for (int i = 1; i <= n; ++i) {
    int num = 0;
    for (int j = i - 1; j >= 0; --j) {
      num = (10ll * num + s[j + 1] - '0') % p;
      red(dp[i] += 1ll * dp[j] * num % p);
    }
  }
  cout << dp[n] << '\n';
}
}

namespace ON {
int dp[N];
int p10[N];
int num[N];
void work() {
  dp[0] = 1;
  p10[0] = 1;
  int i10 = q_pow(10, p - 2);
  for (int i = 1; i <= n; ++i) {
    p10[i] = 1ll * p10[i - 1] * i10 % p;
  }
  reverse(s + 1, s + n + 1);
  i64 pow10 = 1;
  for (int i = 1; i <= n; ++i) {
    num[i] = (pow10 * (s[i] - '0') + num[i - 1]) % p;
    pow10 = pow10 * 10 % p;
  }
  int f = 1, g = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = (1ll * num[i] * f + p - g) % p;
    f = (1ll * dp[i] * p10[i] + f) % p;
    g = (1ll * dp[i] * p10[i] % p * num[i] % p + g) % p;
  }
  cout << dp[n] << '\n';
}
}

void solve() {
  n = rd();
  IO::rdstr(s + 1);
  ON::work();
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
