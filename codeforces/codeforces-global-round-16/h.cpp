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
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
#define NDEBUG

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
const int N = 1000005;
int c, n;
int a[N], low[N], w[N], pri[N], tot;
u32 f[N], g[N], gg[N];
vector<int> grp[N];

void prework() {
  a[1] = 1; w[1] = 1;
  FOR(i, 2, c + 1) {
    if (!low[i]) {
      low[i] = i;
      w[i] = i;
      a[i] = 1;
      pri[tot++] = i;
    }
    for (int j = 0; j < tot && i * pri[j] <= c; ++j) {
      if (pri[j] < low[i]) {
        low[i * pri[j]] = pri[j];
        a[i * pri[j]] = a[i];
        w[i * pri[j]] = w[i] * pri[j];
      } else {
        low[i * pri[j]] = pri[j];
        a[i * pri[j]] = 0;
        w[i * pri[j]] = w[i];
        break;
      }
    }
  }
  FOR(i, 1, c + 1) {
    grp[w[i]].pb(i);
  }
  int cnt = 0;
  static int ask[N];
  FOR(i, 1, c + 1) {
    if (a[i] == 1) {
      ask[cnt++] = i;
    }
  }
  cout << cnt << ' ';
  FOR(i, 0, cnt) cout << ask[i] << ' ';
  cout << endl;
  FOR(i, 0, cnt) {
    cin >> g[ask[i]];
  }
    int total_xor = g[1];
    for (int x = 1; x <= c; x++) {
        if (grp[x].empty()) continue;
        for (int y = x; y <= c; y += x) f[y] ^= (g[x] ^ total_xor);
    }
    f[1] = total_xor;
    for (int x = c; x >= 1; x--) {
        if (grp[x].empty()) continue;
        for (int y = 2 * x; y <= c; y += x) {
            if (grp[y].size()) f[x] ^= f[y];
        }
    }
}

vector<int> ans;
vector<vector<vector<int> > > ext;
vector<vector<int> > szext;
mt19937 gen(time(0));

bitset<260> p[260];
const int rand_tot = 500;
u32 s[N];
void gauss(int x) {
  int n = grp[x].size();
  FOR(i, 0, n) s[i] = grp[x][i], p[i] = 0, p[i].set(i);
  int i = 0;
  for (int i = 0; i < n; ++i) {
    int f = -1;
    for (int j = 0; j < n && f < 0; ++j)
      if ((s[j] & -s[j]) == 1 << i) f = j;
    if (f == -1) continue;
    for (int j = 0; j < n; ++j) {
      if (s[j] & (1 << i) && j != f) s[j] ^= s[f], p[j] ^= p[f];
    }
  }
  int all = 0;
  int cnt = 0;
  bitset<260> to;
  for (int i = 0; i < n; ++i) {
    if (s[i]) ++cnt;
    if (s[i] & f[x]) {
      to ^= p[i];
    }
  }
  if (cnt == n) {
    FOR(i, 0, n) {
      if (to[i]) ans.pb(grp[x][i]);
    }
    return;
  }
  vector<vector<int> > cgrp;
  vector<int> csiz;
  vector<bool> vis(260);
  FOR(_, 0, rand_tot) {
    bitset<260> cur = to;
    FOR(i, 0, n) {
      if (!s[i] && gen() & 1) {
        cur ^= p[i];
      }
    }
    if (!vis[cur.count()]) {
      vector<int> cans;
      FOR(i, 0, n) {
        if (cur[i]) cans.pb(grp[x][i]);
      }
      cgrp.pb(cans);
      csiz.pb(cur.count());
      vis[cur.count()] = 1;
    }
  }
  ext.pb(cgrp);
  szext.pb(csiz);
}

void solve() {
  cin >> c >> n;
  prework();
  for (int i = 1; i <= c; ++i) {
    if (grp[i].size()) {
      gauss(i);
        // gauss(f[i], grp[i], ans, szext, ext);
    }
  }
  if (!ext.empty()) {
    n -= ans.size();
    vector<bitset<50000> > h(szext.size() + 1);
    h[0][0] = 1;
    for (int i = 0; i < szext.size(); ++i) {
      for (auto &e : szext[i]) {
        h[i + 1] |= (h[i] << e);
      }
    }
    assert(h[szext.size()][n]);
    for (int i = szext.size(); i > 0; --i) {
      for (int j = 0; j < szext[i-1].size(); ++j) {
        if (h[i - 1][n - szext[i-1][j]]) {
          n -= szext[i-1][j];
          for (auto &e : ext[i-1][j]) {
            ans.pb(e);
          }
          break;
        }
      }
    }
  }
  for (auto i : ans) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {
  freopen("1.in", "r", stdin);
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/* 4 4 2 11 4 4 1

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