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
#include <set>
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
const int mod = 998244353;
int a[N], pos[N];
int n;
inline void red(int &x) {
  if (x >= mod) x -= mod;
}

vector<pii> q[N];
set<pii> si;

struct DS {
  struct node {
    int s, f;
    int t = 0;
  } a[N << 2];
  inline int sum() {
    return a[1].f;
  }
  void up(int p) {
    red(a[p].s = a[p<<1].s + a[p<<1|1].s);
    if (a[p].t == 0) {
      red(a[p].f = a[p<<1].f + a[p<<1|1].f);
    } else a[p].f = 0;
  }
  void ins(int p, int l, int r, int s, int v) {
    if (r - l == 1) {
      a[p].s = v;
      if (a[p].t == 0) a[p].f = v;
      else a[p].f = 0;
      return;
    }
    int mid = (l + r) >> 1;
    if (s < mid) ins(p<<1, l, mid, s, v);
    else ins(p<<1|1, mid, r, s, v);
    up(p);
  }
  void toggle(int p, int l, int r, int s, int t, int v) {
    if (r == t && s == l) {
      a[p].t += v;
      if (a[p].t == 0) {if (r - l > 1) red(a[p].f = a[p<<1].f + a[p<<1|1].f); else a[p].f = a[p].s;}
      else a[p].f = 0;
      return;
    }
    int mid = (l + r) >> 1;
    if (s < mid) toggle(p<<1, l, mid, s, min(mid, t), v);
    if (t > mid) toggle(p<<1|1, mid, r, max(mid, s), t, v);
    up(p);
  }
} D;

void solve() {
  n = rd();
  FOR(i, 0, n) a[i + 1] = rd();
  FOR(i, 1, n + 1) {
    pos[a[i]] = i;
  }
  si.insert(mkp(1, n));
  FOR(i, 1, n + 1) {
    int u = pos[i];
    auto it = si.upper_bound(mkp(u, n + 1));
    auto cur = it;
    --cur;
    int l = u, m = u, rl = -1, rr = -1;
    if ((*cur).fi == u) {
      if (cur == si.begin()) l = 1;
      else {
        --cur;
        l = (*cur).se + 1;
        ++cur;
      }
    }
    if (u == (*cur).se && it != si.end()) {
      rl = (*it).fi;
      rr = (*it).se;
    }
    if (u < (*cur).se) {
      rl = u + 1;
      rr = (*cur).se;
    }
    if (rl != -1) {
      q[rl].emplace_back(l, m);
      q[rr + 1].emplace_back(-l, m);
    }
    if (u - 1 >= (*cur).fi) si.insert(mkp((*cur).fi, u-1));
    if (u + 1 <= (*cur).se) si.insert(mkp(u+1, (*cur).se));
    si.erase(cur);
  }
  D.ins(1, 0, n + 1, 0, 1);
  int ans = 0;
  FOR(i, 1, n + 1) {
    for (auto p : q[i]) {
      if (p.fi < 0) {
        D.toggle(1, 0, n + 1, -p.fi - 1, p.se, -1); // recover
      } else {
        D.toggle(1, 0, n + 1, p.fi - 1, p.se, 1); // ban
      }
    }
    ans = D.sum();
    D.ins(1, 0, n + 1, i, ans);
  }
  cout << ans << '\n';
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
