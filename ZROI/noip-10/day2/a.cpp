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
#define MULTI

char ans[3][16][1 << 15 | 10], cnt[3][16][3];
int nxt[3];

int mins(int a, int b, int n) {
  for (int i = 0; i < (1 << n); ++i) {
    if (ans[a][n][i] < ans[b][n][i])
      return a;
    if (ans[a][n][i] > ans[b][n][i])
      return b;
  }
  return a;
}

void prework() {
  nxt[0] = 1;
  nxt[1] = 2;
  nxt[2] = 0;
  ans[0][0][0] = 0;
  ans[1][0][0] = 1;
  ans[2][0][0] = 2;
  cnt[0][0][0] = 1;
  cnt[1][0][1] = 1;
  cnt[2][0][2] = 1;
  for (int i = 1; i < 16; ++i) {
    for (int j = 0; j < 3; ++j) {
      int a = j, b = nxt[j];
      int x = mins(a, b, i - 1), y = a ^ b ^ x;
      for (int k = 0; k < 3; ++k) {
        cnt[j][i][k] = cnt[a][i - 1][k] + cnt[b][i - 1][k];
      }
      for (int k = 0; k < (1 << (i - 1)); ++k)
        ans[j][i][k] = ans[x][i - 1][k],
        ans[j][i][k + (1 << (i - 1))] = ans[y][i - 1][k];
    }
  }
}

void solve() {
  int r = rd(), p = rd(), s = rd();
  int n = 31 - __builtin_clz(r + p + s);
  int t = -1;
  for (int i = 0; i < 3; ++i) {
    if (r == cnt[i][n][1] && p == cnt[i][n][0] && s == cnt[i][n][2]) {
      if (t == -1)
        t = i;
      else
        t = mins(t, i, n);
    }
  }
  if (t != -1) {
    for (int j = 0; j < r + p + s; ++j) {
      cout << "PRS"[ans[t][n][j]];
    }
    cout << '\n';
  } else
    puts("-1");
}

int main() {
  IO::init_in();
  prework();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve();
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
