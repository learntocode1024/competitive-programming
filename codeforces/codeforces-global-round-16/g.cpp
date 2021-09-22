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
const int N = 100005;
int n, m, q;
bool vis[N << 4];
map<pii, int> mp;

int tot;

struct ed {
  int u, v, w, id;
  void init() {
    u = rd(), v = rd(), w = rd();
    if (v < u) swap(u, v);
    id = ++tot;
    mp[mkp(u, v)] = id;
  }
  bool operator< (const ed& rhs) const {
    return w > rhs.w;
  }
  inline bool vis() const { return ::vis[id]; };
};
using pe = priority_queue<ed>;

pe g, a[N];
bool vis1[N << 4];
int ver[N];
int tot1;
int gmin(int u);
priority_queue<pii> mn;

void ins() {
  ed c;
  c.init();
  g.push(c);
  a[c.u].push(c);
  a[c.v].push(c);
  mn.push(mkp(gmin(c.u), ++tot1));
  ver[c.u] = tot1;
  mn.push(mkp(gmin(c.v), ++tot1));
  ver[c.v] = tot1;
}
void del() {
  int u = rd(), v = rd();
  if (u > v) swap(u, v);
  vis[mp[mkp(u,v)]] = 1;
  mp.erase(mkp(u, v));
  vis1[ver[u]] = vis1[ver[v]] = 0;
  mn.push(mkp(gmin(u), ++tot1));
  ver[u] = tot1;
  mn.push(mkp(gmin(v), ++tot1));
  ver[v] = tot1;
}

pii tmp[10];
ed ttmp[10];
ed stk[N];
int t, tott;
int fnd(ed);
int qry() {
  tott = 0;
  for (int i = 0; i < 6 && !g.empty(); ++i) {
    while (g.top().vis()) g.pop();
    tmp[tott++] = mkp(g.top().w, g.top().id);
    stk[t++] = g.top();
    g.pop();
  }
  FOR(i, 0, t) g.push(stk[i]);
  t = 0;
  int ret = 2e9;
  ed mn = g.top();
  ttmp[0] = mn;
  int tt = 1, u = mn.u;
  for (int i = 0; i < 3 && !a[u].empty(); ++i) {
    while (a[u].top().vis()) a[u].pop();
    if (i > 0) ttmp[tt++] = a[u].top();
    stk[t++] = a[u].top();
    a[u].pop();
  }
  FOR(i, 0, t) a[u].push(stk[i]);
  t = 0;
  u = mn.v;
  for (int i = 0; i < 3 && !a[u].empty(); ++i) {
    while (a[u].top().vis()) a[u].pop();
    if (i > 0) ttmp[tt++] = a[u].top();
    stk[t++] = a[u].top();
    a[u].pop();
  }
  FOR(i, 0, t) a[u].push(stk[i]);
  t = 0;
  FOR(i, 0, tt) {
    chkmin(ret, ttmp[i].w + fnd(ttmp[i]));
  }
  while (vis1[::mn.top().se]) ::mn.pop();
  return min(ret, -::mn.top().fi);
}

int id[10];
bool vv[N << 2];

int fnd(ed c) {
  int tt = 0, u = c.u;
  for (int i = 0; i < 3 && !a[u].empty(); ++i) {
    while (a[u].top().vis()) a[u].pop();
    id[tt++] = a[u].top().id;
    stk[t++] = a[u].top();
    a[u].pop();
  }
  FOR(i, 0, t) a[u].push(stk[i]);
  t = 0;
  u = c.v;
  for (int i = 0; i < 3 && !a[u].empty(); ++i) {
    while (a[u].top().vis()) a[u].pop();
    id[tt++] = a[u].top().id;
    stk[t++] = a[u].top();
    a[u].pop();
  }
  FOR(i, 0, t) a[u].push(stk[i]);
  t = 0;
  FOR(i, 0, tt) vv[id[i]] = 1;
  int ret;
  FOR(i, 0, tott) if (!vv[tmp[i].se]) ret = tmp[i].fi;
  FOR(i, 0, tt) vv[id[i]] = 0;
  return ret;
}
int gmin(int u) {
  int ret = 0;
  for (int i = 0; i < 3 && !a[u].empty(); ++i) {
    while (a[u].top().vis()) a[u].pop();
    ret += a[u].top().w;
    stk[t++] = a[u].top();
    a[u].pop();
  }
  FOR(i, 0, t) a[u].push(stk[i]);
  if (t < 3) {
    t = 0;
    return -2e9;
  }
  t = 0;
  return -ret;
}

void solve() {
  n = rd(), m = rd();
  while (m--) {
    ins();
  }
  q = rd();
  while ((cout << qry() << '\n') && q--) {
    if (rd() == 0) del();
    else ins();
  }
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
