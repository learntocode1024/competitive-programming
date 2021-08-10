/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  7, 2021
 * Algorithm: birthday_paradox, NTT
 * Difficulty: mid
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
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
#define MX 
int mod = 998244353;

i64 Q_pow(i64 a, int b) {
  i64 ret = 1;
  while (b) {
    if (b & 1) ret = ret * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ret;
}

const int N = 1 << 18;
i64 a[N];
i64 pp[N];
u32 inv[N];
void ntt() {
  for (int i = 1; i < N; ++i) {
    inv[i] = inv[i >> 1] >> 1;
    if (i & 1) inv[i] |= (N >> 1);
    if (i < inv[i]) swap(a[i], a[inv[i]]);
  }
  for (int i = 1; i < N; i <<= 1) {
    i64 wn = pp[N / i / 2];
    for (int j = 0; j < N; j += i << 1) {
      i64 w = 1;
      for (int k = j; k < j + i; ++k) {
        i64 x = a[k], y = a[k + i] * w % mod;
        a[k] = (x + y) % mod;
        a[k + i] = (x - y + mod) % mod;
        w = w * wn % mod;
      }
    }
  }
}

void solve() {
  int n = rd(), B = rd();
  if (n == 1) {
    i64 a = rd(), b = rd();
    if (!a || !b) puts("1 2");
    else if (b == 1 || (mod - 1) % b != 0) puts("-1");
    cout << 1 << ' ' << Q_pow(3, (mod - 1) / b) << '\n';
  } else {
    pp[0] = 1;
    i64 g = Q_pow(3, (mod - 1) >> 18);
    for (int i = 1; i < N; ++i) {
      pp[i] = pp[i - 1] * g % mod;
    }
    for (int i = 0; i < n; ++i) {
      i64 a = rd(), b = rd();
      ::a[b % N] += a;
      ::a[b % N] %= mod;
    }
    ntt();
    map<int, int> m;
    for (int i = 0; i < N; ++i) {
      if (m.find(a[i]) != m.end()) {
        cout << pp[m[a[i]]] << ' ' << pp[i] << '\n';
        break;
      }
      m[a[i]] = i;
    }
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