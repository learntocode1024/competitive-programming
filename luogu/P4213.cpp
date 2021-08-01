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
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
#define MULTI
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
template <typename T> void chkmin(T &a, const T &b) { b = min(a, b); }

/*********************************** solution *********************************/
const int N = 1664515;
i64 phi[N], u[N], s1[N], s2[N];
int low[N], p[N], tot;

void seive() {
  phi[1] = u[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!low[i])
      low[i] = p[tot++] = i, phi[i] = i - 1, u[i] = -1;
    for (int j = 0; j < tot && p[j] * i < N; ++j) {
      low[i * p[j]] = p[j];
      if (p[j] < low[i]) {
        phi[i * p[j]] = phi[i] * (p[j] - 1);
        u[i * p[j]] = -u[i];
      } else {
        phi[i * p[j]] = phi[i] * p[j];
        u[i * p[j]] = 0;
      }
    }
  }
  for (int i = 1; i < N; ++i) {
    s1[i] = s1[i - 1] + phi[i];
    s2[i] = s2[i - 1] + u[i];
  }
}

unordered_map<i64, i64> mp, mu;

i64 S_phi(i64 n) {
  if (n < N) return s1[n];
  if (mp.find(n) != mp.end()) return mp[n];
  i64 ret = 1ll * n * (n + 1) / 2;
  for (i64 i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret -= S_phi(n / i) * (j - i + 1);
  }
  return mp[n] = ret;
}

i64 S_u(i64 n) {
  if (n < N) return s2[n];
  if (mu.find(n) != mu.end()) return mu[n];
  i64 ret = 1;
  for (i64 i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret -= S_u(n / i) * (j - i + 1);
  }
  return mu[n] = ret;
}

void solve() {
  int n = IO::read();
  cout << S_phi(n) << ' ' << S_u(n) << '\n';
}

int main() {
  seive();
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

