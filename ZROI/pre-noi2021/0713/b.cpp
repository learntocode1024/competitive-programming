/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 13, 2021
 * Source: ZROI simulation contests for NOI2021
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
typedef complex<long double> Complex;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 200005

/*** */
namespace IO {
char in[1 << 21]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int readInt() {
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
/* */

LL a[MX];
int n, q;
const int blk = 300;
int T;

LL dp[2][MX / blk + 5][blk + 5][blk / 2 + 5];

void proc1() {
  for (int i = 0; i < T; ++i) {
    int l = i * blk, r = min(l + blk, n);
    dp[0][i][r - 2][1] = a[r - 2];
    for (int j = r - 3; j >= l; --j) {
      for (int c = 1; c < (r - j + 1) / 2; ++c) {
        dp[0][i][j][c] = max(dp[0][i][j + 1][c], dp[0][i][j + 2][c - 1] + a[j]);
        if (c)
          dp[1][i][j][c - 1] =
              max(dp[1][i][j + 1][c - 1], dp[1][i][j + 2][c - 2] + a[j]);
      }
    }
    for (int j = r - 1; j >= l; --j) {
      for (int c = (r - j - 1) / 2; c; --c) {
        dp[1][i][j][c] = dp[1][i][j][c - 1] + a[r - 1];
      }
    }
  }
}

LL suff[2][MX / blk + 5][blk / 2 + 5];

priority_queue<pair<LL, int>> pq;
void proc2() {
  for (int i = 0; i < T; ++i) {
    int l = i * blk;
  }
}

void solve() {
  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  T = n / blk + (n % blk > 0);
  proc1();
  proc2();
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}
