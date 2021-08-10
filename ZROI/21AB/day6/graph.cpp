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
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int rd() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}

char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 100005
int n;
const i64 mod = 998244353;
i64 p, q;
int v[MX];

i64 Q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1)
      ret = ret * a % mod;
    a = a * a % mod;
    x >>= 1;
  }
  return ret;
}

namespace sub1 {
int c[15];
void solve() {
  for (int i = 0; i < n; ++i) {
    c[i] = i + 1;
  }
  i64 ans = 0;
  do {
    if (c[n - 1] < c[1])
      continue;
    i64 prob = Q_pow(p, n);
    for (int i = 1; i < n; ++i) {
      int t = c[i] - 1;
      for (int j = 0; j < i; ++j) {
        t -= c[j] < c[i];
      }
      prob = prob * Q_pow(q, t) % mod;
    }
    ans = (ans + v[c[1]] * v[c[n - 1]] % mod * prob) % mod;
  } while (next_permutation(c + 1, c + n));
  cout << ans << '\n';
}
} // namespace sub1

namespace sub2 {
void solve() {}
} // namespace sub2

namespace sub3 {
i64 ppw[MX];
void solve() {
  if (q == 0) {
    cout << "1\n";
    return;
  }
  i64 ans = Q_pow(p, n) * Q_pow(q, n * (n - 1) / 2) % mod;
  i64 q1 = Q_pow(q, mod - 2);
  ppw[0] = 1;
  for (int i = 1; i <= n; ++i) ppw[i] = ppw[i - 1] * q1 % mod;
  for (int i = 1, t = 0; i <= n - 3; ++i) t = (t + ppw[i]) % mod, ans = ans * t % mod;
  ans = ans * ppw[n] % mod;
  i64 tmp = 0;
  for (int i = 1; i <= n - 2; ++i) tmp = (tmp + ppw[i] * (n - i - 1)) % mod;
  ans = ans * tmp % mod;
  cout << ans << '\n';
}
} // namespace sub3

void solve() {
  n = rd(), p = rd();
  bool A = 1;
  q = 1 - p + mod;
  for (int i = 1; i <= n; ++i)
    v[i] = rd(), A = A && (v[i] == 1);
  if (n <= 10) {
    sub1::solve();
  } else if (n <= 50) {
    sub2::solve();
  } else if (A) {
    sub3::solve();
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}
