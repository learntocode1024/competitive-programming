/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug 13, 2021
 * Algorithm: combinatorics, bitwise-Op
 * Difficulty: easy
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
char in[1 << 24]; // sizeof in varied in problem
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
long long rdll() {
  unsigned long long u = 0, s = 0;
  while (*o && *o <= 32)
    ++o; // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)
  return static_cast<long long>((u ^ s) + !!s);
}

char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
using IO::rdll;
#define MULTI
const int N = 64;
const i64 mod = 1000000007;
i64 inv[N], fac[N], ifac[N];

i64 Q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % mod;
    a = a * a % mod;
    x >>= 1;
  }
  return ret;
}

inline i64 C(int n, int m) {
  return fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}

void solve() {
  i64 a = rdll(), k = rdll();
  i64 ans = 0;
  i64 len = 1;
  i64 l = 1, r = 2e9, mid;
  while (r > l) {
    mid = l + (r - l) / 2;
    if (mid * (mid + 1) / 2 >= a) r = mid;
    else l = mid + 1;
  }
  len = l;
  a -= len * (len - 1) / 2;
  ans = Q_pow(2, len) - Q_pow(2, len - a);
  if (ans < 0) ans += mod;
  int lim = len - a - 1;
  if (lim < 0) {
    if (k == 1) cout << ans << '\n';
    else cout << "-1\n";
    return;
  }
  --k;
  int cnt = 0;
  while (k >= C(lim, cnt)) {
    k -= C(lim, cnt);
    ++cnt;
  }
  for (int i = cnt; i; --i) {
    int j = i - 1;
    while (j < lim) {
      if (k >= C(j, i - 1)) {
        k -= C(j, i - 1);
        ++j;
      } else break;
    }
    if (j >= lim) {
      puts("-1");
      return;
    }
    ans += Q_pow(2, j);
  }
  cout << ans << '\n'; 
}

int main() {
  inv[1] = fac[0] = fac[1] = ifac[1] = ifac[0] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = mod / i * (mod - inv[mod % i]) % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve();
#else
  solve();
#endif
  return 0;
}
