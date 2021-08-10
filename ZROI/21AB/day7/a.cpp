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
const int N = 500005;
int n;

pair<int, int> res[N];

  vector<int> t;
void gen() {
  for (int i = 0; i < n; ++i) {
    res[i].fi = t[i], res[i].se = t[i + n];
  }
}

void solve() {
  n = rd();
  for (int i = 0; i < n; ++i) {
    res[i].fi = rd() - 1, res[i].se = rd() - 1;
  }
  if (n > 20) {
    for (int i = 0; i < n; ++i) cout << "XY";
    return;
  }
  static int col[N * 2];
  for (int i = 0; i < 1 << n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i & (1 << j)) {
        col[res[j].fi] = 0;
        col[res[j].se] = 1;
      } else {
        col[res[j].fi] = 1;
        col[res[j].se] = 0;
      }
    }
    bool t = 1;
    for (int j = 0; j < 2 * n; ++j) {
      if (col[j] == col[(j + 2 * n - 1) % (2 * n)] && col[j] == col[(j + 1) % (2 * n)]) {
        t = 0;
        break;
      }
    }
    if (t) {
      for (int i = 0; i < 2 * n; ++i) {
        cout << (col[i] ? 'X' : 'Y');
      }
      return;
    }
  }
  cout << "impossible";
}

int main() {
  // for (int i = 0; i < 2 * n; ++i) t.pb(i);
  // for (int i = 0; i < 10000000; ++i) {
  //   gen();
  //   cout << "#" << i << ' ';
  //   solve();
  //   cout << '\n';
  //   if (!next_permutation(begin(t), end(t))) break;
  // }
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
    cout << endl;
#endif
  return 0;
}
