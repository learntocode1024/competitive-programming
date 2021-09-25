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
#include <random>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 26];  // sizeof in varied in problem
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
const int N = 2000000;
char s[N];
vector<int> g[N];
int c[N];
int cnt[30], num;
i64 H[N], mpw[N];
// int mod = 1000000007;
int n;
void Hash() {
  random_device ran;
  uniform_int_distribution<int> e{114,1919810};
  i64 b = 11451411;
  mpw[0] = 1;
  FOR(i, 1, n) mpw[i] = mpw[i-1] * b;
  H[0] = s[0];
  FOR(i, 1, n) H[i] =  H[i-1] * b + s[i];
}

inline i64 h(int l, int r) {
  if (l == 0) return H[r-1];
  return H[r-1] - H[l-1] * mpw[r-l];
}

int bit[30];

i64 ret = 0;
int mem[N][30];
void solve() {
  ret = 0;
  FOR(i, 0, 30) cnt[i] = 0, bit[i] = 0;
  num = 0;
  n = IO::rdstr(s) - s;
  FOR(i, 0, n) s[i] -= 'a';
  for (int i = n - 1; i >= 0; --i) {
    ++cnt[s[i]];
    if (cnt[s[i]] & 1) ++num;
    else --num;
    c[i] = num;
  }
  Hash();
  FOR(i, 0, n + 1) g[i].clear();
  for (int i = 2; i < n; ++i) {
    i64 cur = h(0, i);
    for (int j = i; j < n; j += i) {
      ++mem[i-1][c[j]];
      if (cur != h(j, j + i)) break;
    }
  }
  for (int i = 0; i < 26; ++i) cnt[i] = 0;
  num = 0;
  for (int i = 0; i < n; ++i) {
    i64 mx = 0;
    for (int j = 0; j <= 26; ++j) mx += bit[j], ret += mx * mem[i][j], mem[i][j] = 0;
    ++cnt[s[i]];
    if (cnt[s[i]] & 1) ++num;
    else --num;
    ++bit[num];
  }
  cout << ret << '\n';
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
