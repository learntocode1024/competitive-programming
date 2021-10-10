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
#include <time.h>
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
const int N = 1e3+5;
int a[N][N];
i64 x[N];
bool vis[N];
int q[N];
int n;

bool argu(int u) {
  q[0] = u;
  int tot = 1;
  i64 c = x[u];
  for (int i = u + 1; i <= n; ++i) {
    if (!vis[i] && x[i] % c == 0) {
      q[tot++] = i;
      c = x[i];
      vis[i] = 1;
    }
  }
  if (tot == 1) return 0;
  for (int i = 0; i + 1 < tot; ++i) {
    for (int j = i + 1; j < tot; ++j) {
      if (i / 4 == j / 4) a[q[i]][q[j]] = 1;
      else if (i / 16 == j / 16) a[q[i]][q[j]] = 2;
      else a[q[i]][q[j]] = 3;
    }
  }
  return 1;
}

void solve() {
  srand(time(0));
  cin >> n;
  FOR(i, 1, n + 1) cin >> x[i];
  FOR(i, 1, n) FOR(j, i + 1, n + 1) if (x[j] % x[i]) a[i][j] = 1;
  FOR(i, 1, n) {
    if (!vis[i]) {
      while (argu(i));
    }
  }
  FOR(i, 1, n) FOR(j, i + 1, n + 1) if (!a[i][j]) a[i][j] = rand() % 3 + 1;
  FOR(i, 2, n + 1) {
    FOR(j, 1, i) cout << a[j][i] << ' ';
    cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
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
