/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 28];  // sizeof in varied in problem
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
#define MULTI
const int N = 3e5+5;
using namespace __gnu_pbds;
typedef tree<pii, null_type, greater<pii>, rb_tree_tag, tree_order_statistics_node_update> pset;
int d, n, k;
pset S;
vector<pii> g[N];
i64 ans, cur;

void solve() {
  cur = ans = 0;
  S.clear();
  d = rd(), n = rd(), k = rd();
  FOR(i, 1, d + 1) g[i].clear();
  FOR(i, 0, n) {
    int a = rd(), b = rd(), c = rd();
    g[b].emplace_back(a, i);
    g[c + 1].emplace_back(-a, i);
  }
  for (int i = 1; i <= d; ++i) {
    for (auto v : g[i]) {
      if (v.fi > 0) {
        S.insert(v);
        if (S.size() > k) {
          if (S.order_of_key(v) < k) {
            cur += v.fi;
            cur -= S.find_by_order(k)->fi;
          }
        } else cur += v.fi;
      } else {
        v.fi = -v.fi;
        if (S.size() > k) {
          if (S.order_of_key(v) < k) {
            cur -= v.fi;
            S.erase(v);
            cur += S.find_by_order(k-1)->fi;
          } else S.erase(v);
        } else cur -= v.fi, S.erase(v);
      }
    }
    chkmax(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  FOR(i, 0, T) {
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
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
