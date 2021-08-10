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
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX
int n, t;
int X;
pii operator+(pii a, pii b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}
pii f[8] = {
{0, 1},
{1, 1},
{1, 0},
{1, -1},
{0, -1},
{-1, -1},
{-1, 0},
{-1, 1}
};

map<pii, pii> fa;
map<pii, int> sz;
map<pii, bool> blk;
int hol;
int cnt = 0;

pii get(pii x) {
  if (fa[x] == x) return x;
  fa[x] = get(fa[x]);
  return fa[x];
}

bool insert(pii u) {
  ++cnt;
  fa[u] = u;
  blk[u] = 1;
  sz[u] = 1;
  // hol
  vector<pair<int, pii> > vt;
  for (int i = 0; i < 8; i += 2) {
    if (blk[u + f[i]]) {
      vt.pb(mkp(i, get(u + f[i])));
    }
  }
  for (int i = 0; i < (int)vt.size() - 1; ++i) {
    if (vt[i + 1].fi - vt[i].fi == 2 && vt[i + 1].se == vt[i].se && !blk[u + f[vt[i].fi + 1]]) ++hol;
    if (vt[i + 1].fi - vt[i].fi == 4 && vt[i + 1].se == vt[i].se) ++hol;
  }
  if (vt.size() > 2) {
    auto &a = vt[0], &b = vt.back();
    if (b.fi - a.fi == 6 && a.se == b.se && !blk[u + f[b.fi + 1]]) ++hol;
    if (b.fi - a.fi == 4 && a.se == b.se) ++hol;
  }
  if (blk[u + f[0]] && blk[u + f[2]] && blk[u + f[4]] && blk[u + f[6]]) --hol;
  // if (blk[u + f[0]] && blk[u + f[1]] && blk[u + f[2]] && blk[u + f[3]] && blk[u + f[4]] && blk[u + f[5]] && blk[u + f[6]] && blk[u + f[7]]) --hol;
  for (int i = 0; i < 8; i += 2) {
    if (blk[u + f[i]]) {
      pii v = get(u + f[i]);
      if (v != u) fa[v] = u, sz[u] += sz[v];
    }
  } // union
  if (sz[get(u)] == cnt) return 1;
  return 0;
}

void solve() {
  n = rd(), t = rd();
  for (int i = 0; i < n; ++i) {
    int x = rd() ^ X, y = rd() ^ X;
    bool ans = insert(mkp(x, y));
    ans = ans && !hol;
    cout << ans << ' ';
    // cerr << hol << endl;
    if (t) X = ((X << 1) | ans) % n;
  }
  cout << endl;
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
