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

struct TRIE {
  int ch[1 << 22][2];
  int tot = 1;
  inline void ins(int x) {
    int p = 1;
    for (int i = 19; i >= 0; --i) {
      int &cur = ch[p][(x >> i) & 1];
      if (cur == 0) cur = ++tot;
      p = cur;
    }
  }
  inline int ans(int x) {
    int ret = 0;
    int p = 1;
    for (int i = 19; i >= 0; --i) {
      int c = (x >> i) & 1;
      c ^= 1;
      if (ch[p][c]) {
        ret |= 1 << i;
        p = ch[p][c];
      } else {
        p = ch[p][c^1];
      }
    }
    return ret;
  }
} T;

struct DS {
  int a1[1<<10][1<<10], a2[1<<10][1<<10];
  bool vis[1<<10];
  inline void ins(int x) {
    int x1 = x >> 10;
    int x2 = x & 1023;
    vis[x1] = 1;
    for (int i = 0; i < 1024; ++i) {
      chkmax(a1[x1][i], x2 & i);
    }
    for (int i = 0; i < 1024; ++i) {
      chkmax(a2[x1][i], x2 | i);
    }
  }
  inline int ansand(int x) {
    int ret = 0;
    int x1 = x >> 10;
    int x2 = x & 1023;
    for (int i = 0; i < 1024; ++i) {
      if (vis[i]) chkmax(ret, ((i & x1) << 10) + a1[i][x2]);
    }
    return ret;
  }
  inline int ansor(int x) {
    int ret = 0;
    int x1 = x >> 10;
    int x2 = x & 1023;
    for (int i = 0; i < 1024; ++i) {
      if (vis[i]) chkmax(ret, ((i | x1) << 10) + a2[i][x2]);
    }
    return ret;
  }
};

struct sol {
  bool mk[1<<20] = {1};
  inline void ins(int x) {
    if (mk[x]) return;
    mk[x] = 1;
    FOR(i, 0, 20) {
      if ((x >> i) & 1) ins(x ^ (1 << i));
    }
  }
  inline int ansand(int x) {
    int ret = 0;
    int req = 0;
    ROF(i, 0, 20) {
      if ((x >> i) & 1) {
        if (mk[req | (1 << i)]) {
          req |= 1 << i;
          ret |= 1 << i;
        }
      }
    }
    return ret;
  }
  inline int ansor(int x) {
    int ret = 0, req = 0;
    ROF(i, 0, 20) {
      if ((x >> i) & 1) {
        ret |= 1 << i;
      } else {
        if (mk[req | (1 << i)]) {
          req |= 1 << i;
          ret |= 1 << i;
        }
      }
    }
    return ret;
  }
} D;

int t[1<<20], x[1<<20];
int q;

void _solve() {
  FOR(i, 0, q) {
    if (t[i] == 1) {
      T.ins(x[i]);
      D.ins(x[i]);
    } else if (t[i] == 2) {
      cout << T.ans(x[i]) << ' ' << D.ansand(x[i]) << ' ' << D.ansor(x[i]) << '\n';
    } else {
      cout << T.ans(x[i]) << '\n';
    }
  }
}

void solve() {
  bool sub = 1;
  q = rd();
  FOR(i, 0, q) {
    t[i] = rd(), x[i] = rd();
  }
  _solve();
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
