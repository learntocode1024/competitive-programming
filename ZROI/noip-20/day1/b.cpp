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
const int N = 200005;
int n, k;
int a[N];

namespace ran {
vector<int> cnt[N];
void work() {
  FOR(i, 0, n) cnt[a[i]].pb(i);
  int t = 0;
  FOR(i, 1, N) t += (cnt[i].size() >> 1) << 1;
  if (t + k < n) {
    puts("-1");
  } else {
    FOR(i, 1, N) {
      if (cnt[i].size() > 1) {
        for (int j = 0; j < cnt[i].size() && j != cnt[i].size() - 1; j += 2) {
          cout << cnt[i][j] << ' ';
        }
      }
    }
    cout << '\n';
    FOR(i, 1, N) {
      if (cnt[i].size() > 1) {
        for (int j = 1; j < cnt[i].size(); j += 2) {
          cout << cnt[i][j] << ' ';
        }
      }
    }
  }
}
}

namespace sol {
int s[N];
int vis[N*25];
vector<int> p1, p2;

inline void print(int x, int y) {
  int u = x & y;
  x ^= u, y ^= u;
  cout << __builtin_popcount(x) + p1.size() << ' ';
  FOR(i, 0, 25) {
    if ((x >> i) & 1) cout << i + 1 << ' ';
  }
  for (auto i : p1)  cout << i + 1 << ' ';
  puts("");
  cout << __builtin_popcount(y) + p2.size() << ' ';
  FOR(i, 0, 25) {
    if ((y >> i) & 1) cout << i + 1 << ' ';
  }
  for (auto i : p2)  cout << i + 1 << ' ';
}

void work() {
  int d = 0;
  FOR(i, 25, n) {
    if (d > 0) d -= a[i], p2.pb(i);
    else d += a[i], p1.pb(i);
  }
  if (d < 0) d = -d, swap(p1, p2);
  FOR(i, 1, 1 << min(25, n)) {
    int t = __builtin_ctz(i);
    s[i] = s[i - (1 << t)] + a[t];
    if (s[i] > d && vis[s[i] - d]) {
      print(vis[s[i] - d], i);
      return;
    }
    vis[s[i]] = i;
  }
  puts("-1");
}
}

void solve() {
  n = rd(), k = rd();
  FOR(i, 0, n) a[i] = rd();
  sol::work();
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
