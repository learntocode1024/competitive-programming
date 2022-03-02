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
const int N = 2e5+5, M = 8e3 + 5;
int a[N], b[N];
int s[M][M];
const int p = 1e9 + 7;
inline void red(int &x) { if (x >= p) x -= p; }

int f[M] = {1, 1}, iF[M] = {1, 1}, iv[M] = {0, 1};

inline int binom(int r, int k) { return 1ll * f[r] * iF[k] % p * iF[r- k] % p; }

void solve() {
  int n = rd();
  int _a = 0, _b = 0;
  FOR(i, 0, n) a[i] = rd(), b[i] = rd(), chkmax(_a, a[i]), chkmax(_b, b[i]);
  ++_a, ++_b;
  FOR(i, 0, n) ++s[_a - a[i]][_b - b[i]];
  FOR(i, 1, _a << 1) FOR(j, 1, _b << 1) {
    red(s[i][j] += s[i - 1][j]);
    red(s[i][j] += s[i][j - 1]);
  }
  int ans = 0;
  FOR(i, 0, n) red(ans += s[_a + a[i]][_b + b[i]]);
  FOR(i, 0, n) red(ans += p - binom((a[i] + b[i]) << 1, a[i] << 1));
  ans = 1ll * ans * iv[2] % p;
  cout << ans << '\n';
}

int main() {
  FOR(i, 2, M) {
    f[i] = 1ll * f[i-1] * i % p;
    iv[i] = 1ll * (p - p / i) * iv[p % i] % p;
    iF[i] = 1ll * iF[i - 1] * iv[i] % p; 
  }
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
