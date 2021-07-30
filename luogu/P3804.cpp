/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 22, 2021
 * Algorithm: SAM
 * Difficulty: normal
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
template <typename T> void chkmin(T &a, const T &b) { b = min(a, b); }

/*********************************** solution *********************************/
#define MX 1000005
char s[MX];

class SAM {
  struct stat {
    int ln, len, nxt[26];
  } a[MX];
  int tot, last;
  SAM() {
    tot = 1;
    last = 0;
    a[0].ln = -1;
  }
  void push_back(char c) {
    c -= 'a';
    int cur = tot++;
    int p = last;
    a[cur].len = a[last].len + 1;
    while (p != -1 && !a[p].nxt[c]) a[p].nxt[c] = cur;
    if (p == -1) a[cur].ln = 0;
    else {
      int q = a[p].nxt[c];
      if (a[q].len == a[p].len + 1) a[p].ln = q;
      else {
        int cpy = tot++;
        a[cpy].len = a[p].len + 1;
        a[cpy].ln = a[q].ln;
        memcpy(a[cpy].nxt, a[q].nxt, sizeof(a[q].nxt));
        while (p != -1) {
          if (a[p].nxt[c] == q) a[p].nxt[c] = cpy;
        }
      }
    }
  }
};

void solve() {
  cin >> s;
  
}

int main() {
#if defined BUFFER ^ defined MASSIVE_INPUT
  IO::init_in();
#endif
#ifndef BUFFER
  cin.tie(0);
  ios::sync_with_stdio(false);
#endif
#ifdef MULTI
#ifdef BUFFER
  int T = IO::read();
#else
  int T, cin >> T;
#endif
  while (T--)
    solve(), T && clear();
#else
  solve();
#endif
  return 0;
}
