/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  6, 2021
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
  *s = '\0';
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
#define MX 200005

struct sam {
  int len[MX << 1], nxt[26][MX << 1], f[MX << 1];
  int tot, lst;
  void init() {
    f[0] = -1;
    lst = 0;
    tot = 1;
  }
  void extend(char c) {
    int cur = tot++;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; p != -1 && !nxt[c][p]; p = f[p])
      nxt[c][p] = cur;
    if (p == -1)
      f[cur] = 0;
    else {
      int q = nxt[c][p];
      if (len[q] == len[p] + 1) {
        f[cur] = q;
      } else {
        int alt = tot++;
        len[alt] = len[p] + 1;
        f[alt] = f[q];
        f[cur] = f[q] = alt;
        for (int i = 0; i < 26; ++i) nxt[i][alt] = nxt[i][q];
        for (; p != -1; p = f[p])
          if (nxt[c][p] == q) nxt[c][p] = alt;
      }
    }
    lst = cur;
  }
  bool is_substr(char *s) {
    int p = 0;
    while (*s && nxt[*s - 'a'][p]) {
      p = nxt[*s - 'a'][p];
      ++s;
    }
    return !(*s);
  }
  inline void insert(char *s) {
    while (*s)
      extend(*s++ - 'a');
  }
} S;

char str[MX];
int k, m;

namespace sub2 {
bool valid[MX];
void solve() {
  S.init();
  S.insert(str);
  for (int i = 0; i < m; ++i) {
    IO::rdstr(str);
    valid[i] = S.is_substr(str);
  }
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    int x = rd();
    if (valid[i])
      chkmax(ans, x);
  }
  cout << ans << '\n';
}
}

void solve() {
  IO::rdstr(str);
  m = rd(), k = rd();
  if (k == 1) {
    sub2::solve();
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}
