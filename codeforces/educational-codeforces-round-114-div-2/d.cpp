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
set<u64> st, st1, st01, st11;
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
inline u64 val1(int *cur) {
  u64 ret = 0;
  FOR(i, 0, n) {
    ret = (ret * D + (cur[i] + 1) * E) % 998244353;
  }
  return ret;
}
int xx;
priority_queue<pair<i64, int> > pq;
int inp[N];

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
    FOR(j, 0, n)cin >> xx,  inp[j] = xx-1;
    st.insert(val(inp));
    st01.insert(val1(inp));
  }
  i64 s = 0;
  FOR(i, 0, n) s += a[i].back(), f[1][i] = c[i] - 1;
  pq.push(mkp(s, 1));
  while (!pq.empty()) {
    auto u = pq.top();
    st1.insert(val(f[u.se]));
    st11.insert(val1(f[u.se]));
    pq.pop();
    if (st.find(val(f[u.se])) == st.end() && st01.find(val1(f[u.se])) == st01.end()) {
      FOR(i, 0, n) cout << f[u.se][i] + 1 << ' ';
      cout << '\n';
      return;
    } else {
      i64 s = u.fi;
      FOR(i, 0, n) {
        if (f[u.se][i] > 0) {
          --f[u.se][i];
          if (st1.find(val(f[u.se])) != st1.end() && st11.find(val1(f[u.se])) != st11.end()) continue;
          int v;
          if (tt == 0) v = ++tot;
          else v = stk[tt--];
          FOR(j, 0, n) f[v][j] = f[u.se][j];
          int cc = f[v][i];
          pq.push(mkp(s - a[i][cc+1] + a[i][cc], v));
          ++f[u.se][i];
        }
      }
    }
    stk[++tt] = u.se;
  }
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
