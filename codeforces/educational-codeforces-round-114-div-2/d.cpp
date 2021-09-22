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
#include <time.h>
#include <cstring>
#include <iostream>
#include <set>
#include <queue>
#include <random>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/

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
// #define MULTI
const int N = 15;
typedef vector<i64> vi;
int c[N];
vi a[N];
set<u64> st, st1;
int n;
u64 B, C, D, E;

int f[4000000][15], tot = 1;
int stk[4000000], tt;


inline u64 val(int *cur) {
  u64 ret = 0;
  FOR(i, 0, n) {
    ret = (ret * B + (cur[i] + 1) * C) % 1000000007;
  }
  return ret;
}
int xx;
int x[N], s;

void solve() {
  cin >> n;
  FOR(i, 0, n) {
    cin >> c[i];
    FOR(j, 0, c[i]) {
      cin >> xx;
      a[i].pb(xx);
    }
  }
  int m;
  cin >> m;
  FOR(i, 0, m) {
    FOR(j, 0, n)cin >> xx,  f[i][j] = xx-1;
    st.insert(val(f[i]));
  }
  FOR(i, 0, n) --c[i];
  if (st.find(val(c)) == st.end()) {
    FOR(i, 0, n) cout << c[i] + 1 << ' ';
    return;
  }
  FOR(i, 0, m) {
    i64 ss = 0, cur = 0;
    FOR(j, 0, n) {
      ss += a[j][f[i][j]];
    }
    FOR(j, 0, n) {
      if (f[i][j]) {
        --f[i][j];
        cur = ss - a[j][f[i][j]+1] + a[j][f[i][j]];
        if (cur > s && st.find(val(f[i])) == st.end()) {
          s = cur;
          FOR(k, 0, n) x[k] = f[i][k];
        }
        ++f[i][j];
      }
    }
  }
  FOR(i, 0, n) cout << x[i] + 1 << ' ';
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  srand(time(0));
  B = rand();
  C = rand();
  D = rand(), E = rand();
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
