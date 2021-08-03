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
#define MULTI
#define MX 200005
int n, m;
inline i64 gcd(i64 a, i64 b) {
  if (b) while ((a %= b) && (b %= a));
  return a | b;
}
i64 g[20][MX];
i64 a[MX], d[MX];
void clear() {
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j < n; ++j)
      g[i][j] = 1;
}

void solve() {
  n = read();
  clear();
  REP(i, 0, n) a[i] = read();
  REP(i, 0, n - 1) g[0][i] = abs(a[i + 1] - a[i]);
  REP(i, 1, 20) {
    REP(j, 0, n - 1) {
      g[i][j] = gcd(g[i - 1][j], g[i - 1][j + (1 << (i - 1))]);
    }
  }
  int ans = 1;
  REP(i, 0, n - 1) {
    int k = i, gg = 0;
    PER(j, 0, 20) {
      if (gcd(gg, g[j][k]) > 1) gg = gcd(gg, g[j][k]), k += 1 << j;
    }
    chkmax(ans, k - i + 1);
  }
  cout << ans << endl;
}

int main() {
#ifndef MASSIVE_INPUT
  IO::init_in();
#endif
#ifdef MULTI
  int T = IO::read();
  while (T--)
    solve();
#else
  solve();
#endif
  return 0;
}

