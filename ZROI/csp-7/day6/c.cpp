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
const int N = 505;

int n;
int g[N][2];
bool vis[N];
int b[N], a[N];

bool ring() {
  FOR(i, 1, n + 1) vis[i] = 0;
  int tot = 1;
  b[1] = 1;
  vis[1] = 1;
  int p = 1;
  for (int i = 1; i < n; ++i) {
    if (!vis[g[p][0]]) p = g[p][0];
    else if (!vis[g[p][1]]) p = g[p][1];
    else break;
    vis[p] = 1;
    b[++tot] = p;
  }
  if (tot < n) return 0;
  FOR(i, 1, n + 1) a[i] = i;
  return 1;
}

int dp[N][N];

int lcs() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = 0;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      chkmax(dp[i][j], dp[i][j - 1]);
      chkmax(dp[i][j], dp[i - 1][j]);
      if (a[i] == b[j]) chkmax(dp[i][j], dp[i - 1][j - 1] + 1);
    }
  }
  return dp[n][n];
}

void solve() {
  cin >> n;
  if (n == 0)
    exit(0);
  FOR(i, 1, n + 1) {
    cin >> g[i][0] >> g[i][1];
  }
  if (!ring()) {
    cout << "Not solvable.\n";
    return;
  }
  cout << "Knot solvable.\n";
  int ans = n - lcs();
  reverse(b + 2, b + n + 1);
  chkmin(ans, n - lcs());
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  while (true)
    solve();
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
