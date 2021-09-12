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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

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
typedef tree<
int, /* key type */
null_type, /* value type */
less<int>, /* comparison */
rb_tree_tag, /* for having an rb tree */
tree_order_statistics_node_update> tr;
using IO::rd;
#define  MULTI
const int N = 305;
pii a[N * N];
int n, m;
int l[N * N], r[N * N];
tr st[N];


void solve() {
  n = rd(), m = rd();
  FOR(i, 0, n * m) {
    a[i].fi = rd();
    a[i].se = i;
  }
  sort(a, a + n * m);
  for (int l = 0, r = -1; l < n * m;) {
    while (a[r + 1].fi == a[l].fi) ++r;
    for (int i = l; i <= r; ++i) {
      ::l[a[i].se] = l;
      ::r[a[i].se] = r;
    }
    l = r + 1;
  }
  int ans = 0;
  FOR(i, 0, n) FOR(j, 0, m) st[i].insert(j);
  for (int i = 0; i < n * m; ++i) {
    int r1 = l[i] / m, r2 = r[i] / m;
    int rw = -1, mn = 114514;
    decltype(st[0].begin()) itr;
    for (int j = r1; j <= r2; ++j) {
      if (st[j].empty()) continue;
      int rr = min(r[i], (j + 1) * m - 1), ll = max(l[i], j * m);
      rr %= m, ll %= m;
      auto it = st[j].lower_bound(rr + 1);
      if (it == st[j].begin()) continue;
      --it;
      if (*it < ll) continue;
      int inc = st[j].size() - 1 - st[j].order_of_key(*it);
      if (inc < mn) {
        mn = inc;
        itr = it;
        rw = j;
      }
    }
    ans += mn;
    st[rw].erase(itr);
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
