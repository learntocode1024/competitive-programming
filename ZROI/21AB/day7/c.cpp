/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug 10, 2021
 * Algorithm: polynomial, BGF
 * Difficulty: hard
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
#define MX 3000005
const i64 mod = 998244353;
i64 f[MX];
int shift[30], bak[30];
int ppp[30];

i64 fac[30][MX], a[30][MX];

void solve() {
  int n = rd(), k = rd();
  shift[0] = bak[0] = ppp[0] = 1;
  int lim = 0;
  for (int i = 1; i < 30; ++i) {
    ppp[i] = ppp[i - 1] * k;
    bak[i] = bak[i - 1] + ppp[i];
    shift[i] = shift[i - 1] + bak[i];
    if (bak[i] > n) {
      lim = i;
      break;
    }
  }
  fac[0][0] = 1;
  for (int i = 1; i <= lim; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (j < bak[i - 1]) fac[i][j] = fac[i - 1][j];
      else fac[i][j] = (fac[i - 1][j] + fac[i][j - bak[i - 1]]) % mod;
    }
  }
  static i64 b[MX];
  for (int i = 0; i <= lim; ++i) {
    for (int j = shift[i]; j <= n; ++j) {
      if (i & 1) b[j] += mod - fac[i][j - shift[i]];
      else b[j] += fac[i][j - shift[i]];
    }
  }
  for (int i = 0; i <= n; ++i) b[i] %= mod;
  for (int i = 1; i <= n; ++i) {
    a[0][i] = b[i];
    for (int k = 1; k <= lim && i >= shift[k - 1]; ++k) {
      if (k & 1) a[0][i] += a[k][i - shift[k - 1]];
      else a[0][i] += mod - a[k][i - shift[k - 1]];
    }
    a[0][i] %= mod;
    for (int k = 1; k <= lim; ++k) {
      if (i < bak[k - 1] )a[k][i] = a[k - 1][i];
      else a[k][i] = (a[k - 1][i] + a[k][i - bak[k - 1]]) % mod;
    }
  }
  cout << a[0][n] << '\n';
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
