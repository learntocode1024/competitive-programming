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
#include <map>
#include <queue>
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
const int N = 10;

namespace bf {
int a[N];
void prework() {
  FOR(i, 0, 9) a[i] = i + 1;
  int cnt = 0;
  do {
    bool ok = 1;
    ok = ok && a[0] + a[1] + a[2] == 15;
    ok = ok && a[3] + a[4] + a[5] == 15;
    ok = ok && a[6] + a[7] + a[8] == 15;
    ok = ok && a[0] + a[3] + a[6] == 15;
    ok = ok && a[1] + a[4] + a[7] == 15;
    ok = ok && a[2] + a[5] + a[8] == 15;
    ok = ok && a[0] + a[4] + a[8] == 15;
    ok = ok && a[2] + a[4] + a[6] == 15;
    cnt += ok;
    if (ok) {
      cout << '{';
      FOR(i, 0, 8) cout << a[i] << ", ";
      cout << a[8] << "},\n";
    }
  } while (next_permutation(a, a + 9));
  cout << cnt << '\n';
}
}

short T[400000][9] = {
{2, 7, 6, 9, 5, 1, 4, 3, 8},
{2, 9, 4, 7, 5, 3, 6, 1, 8},
{4, 3, 8, 9, 5, 1, 2, 7, 6},
{4, 9, 2, 3, 5, 7, 8, 1, 6},
{6, 1, 8, 7, 5, 3, 2, 9, 4},
{6, 7, 2, 1, 5, 9, 8, 3, 4},
{8, 1, 6, 3, 5, 7, 4, 9, 2},
{8, 3, 4, 1, 5, 9, 6, 7, 2},
};
int tot = 8;

int ans[400000];
int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

inline int enc(short *a) {
  int res = 0;
    for(int i = 0; i < 9; ++i) {
        int cnt = 0;
        for(int j = i + 1;j < 9; ++j) if(a[j] < a[i]) ++cnt;
        res += cnt * fac[9 - i - 1];
    }
    return res + 1;
}

inline int cpy(int x) {
  FOR(i, 0, 9) T[tot][i] = T[x][i];
  return tot++;
}

const int all = 12;
int tr[all][2] = {
{0,1},{1,2},{3,4},{4,5},{6,7},{7,8},{0,3},{3,6},{1,4},{4,7},{2,5},{5,8}
};

int qy[800000];
int fr, tl;
void bfs() {
  FOR(i, 1, 362881) ans[i] = -1;
  tl = -1;
  FOR(i, 0, 8) {
    qy[++tl] = i;
    ans[enc(T[i])] = 0;
  }
  while (fr <= tl) {
    int u = qy[fr++];
    i64 fr = enc(T[u]);
    for (int i = 0; i < all; ++i) {
      swap(T[u][tr[i][0]], T[u][tr[i][1]]);
      i64 to = enc(T[u]);
      if (ans[to] == -1) {
        ans[to] = ans[fr] + 1;
        qy[++tl] = cpy(u);
      }
      swap(T[u][tr[i][0]], T[u][tr[i][1]]);
    }
  }
}

short a[9];

void solve() {
  FOR(i, 0, 9) a[i] = rd();
  cout << ans[enc(a)] << '\n';
}

int main() {
  bfs();
  // prework();
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
