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
const int N = 1000003;
const i64 p = 1000003;

i64 q_pow(i64 x, int y) {
  i64 ret = 1;
  while (y) {
    if (y & 1) ret = ret * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ret;
}
int phi[N];
int _p[N], tot;
int low[N];

void seive() {
  phi[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!low[i])
      low[i] = _p[tot++] = i, phi[i] = i - 1;
    int j;
    for (j = 0; j < tot && i * _p[j] < N; ++j) {
      low[i * _p[j]] = _p[j];
      if (_p[j] < low[i])
        phi[i * _p[j]] = phi[i] * (_p[j] - 1);
      else {
        phi[i * _p[j]] = phi[i] * _p[j];
        break;
      }
    }
  }
}


void solve() {
  int a = rd(), b = rd();
  if (a == 0 && b == 0) {
    puts("0");
    return;
  }
  i64 ans = 0;
  int c = a + b;
  int f = __gcd(a, c);
  c /= f;
  auto contrib = [f, c] (int d) {
    return phi[d] * q_pow(2, f * c / d) % p;
  };
  for (int i = 1; i * i <= c; ++i) {
    if (c % i == 0) {
      ans = (ans + contrib(i)) % p;
      if (i * i != c) ans = (ans + contrib(c / i)) % p;
    }
  }
  ans = ans * q_pow(c, p - 2) % p;
  cout << (q_pow(2, a + b) - ans + p) % p << '\n';
}

int main() {
  seive();
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
