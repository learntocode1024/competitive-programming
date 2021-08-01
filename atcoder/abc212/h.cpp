/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  1, 2021
 * Algorithm: FMT(xor-convolution)
 * Difficulty: template
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
#ifdef MASSIVE_INPUT
namespace IO {
template <int size> struct io {
  char ibuf[size], obuf[size];
  char *o, *o1, *p, *p1;
  io() : o(ibuf), o1(ibuf), p(obuf), p1(obuf + size){};
  ~io() { fwrite(obuf, 1, p - obuf, stdout); }
  inline char gc() {
    return o == o1 && (o1 = (o = ibuf) + fread(ibuf, 1, size, stdin)), *o++;
  };
  inline void pc(char ch) {
    p == p1 &&fwrite(obuf, 1, p - obuf, stdout) && (p = obuf), *p++ = ch;
  }
};
io<1 << 20> f;
inline int read() {
  int x = 0, u = 1;
  char ch = f.gc();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      u = -1;
    ch = f.gc();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = f.gc();
  }
  return x * u;
}
} // namespace IO
#else
namespace IO {
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int read() {
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
} // namespace IO
#endif

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
using IO::read;
const int N = 65536;
const i64 MOD = 998244353;
const i64 inv2 = 499122177;

void fwt(i64 *a) {
  for (int len = 1; len < N; len <<= 1) {
    for (int i = 0; i < N; i += len << 1) {
      for (int j = i; j < i + len; ++j) {
        i64 x = a[j], y = a[j + len];
        a[j] = (x + y) % MOD;
        a[j + len] = (x - y + MOD) % MOD;
      }
    }
  }
}

void ifwt(i64 *a) {
  for (int len = 1; len < N; len <<= 1) {
    for (int i = 0; i < N; i += len << 1) {
      for (int j = i; j < i + len; ++j) {
        i64 x = a[j], y = a[j + len];
        a[j] = (x + y) * inv2 % MOD;
        a[j + len] = (x - y + MOD) * inv2 % MOD;
      }
    }
  }
}

i64 a[N];

i64 Q_pow(i64 a, int x) {
  a %= MOD;
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % MOD;
    a = a * a % MOD;
    x >>= 1;
  }
  return ret;
}

void solve() {
  int n = read(), k = read();
  for (int i = 0; i < k; ++i) {
    int t = read();
    ++a[t];
  }
  fwt(a);
  for (int i = 0; i < N; ++i) {
    if (a[i] == 1) a[i] = n;
    else a[i] = ((Q_pow(a[i], n + 1) + MOD - 1) * Q_pow(a[i] - 1 + MOD, MOD - 2) + MOD - 1) % MOD;
  }
  ifwt(a);
  i64 ans = 0;
  for (int i = 1; i < N; ++i) ans += a[i];
  cout << ans % MOD << '\n';
}

int main() {
#ifndef MASSIVE_INPUT
  IO::init_in();
#endif
#ifdef MULTI
  int T = IO::read();
  while (T--)
    solve(), T &&clear();
#else
  solve();
#endif
  return 0;
}

