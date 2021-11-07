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
} // namespace IO
template<typename T>
void rdint(T &a) {
  a = IO::rd();
}
template<typename A, typename... B>
void rdint(A &a, B& ...b) {
  a = IO::rd();
  rdint(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}

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
template <typename T1, typename T2>
void chkmax(T1 &a, const T2 &b) {
  a = max(a, (T1)b);
}
template <typename T1, typename T2>
void chkmin(T1 &a, const T2 &b) {
  a = min(a, (T1)b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
#define MULTI
const int N = 5e5+5;
vector<int> a[N], rmx[N], rmn[N];
int mn[N], mx[N];
char ans[N];
int n, m;

pair<pii, int> L[N], R[N];

void solve() {
  rdint(n, m);
  FOR(i, 1, n + 1) {
    ans[i] = 'R';
    mx[i] = 0;
    mn[i] = 1e7;
    rmx[i] = rmn[i] = a[i] = vector<int>(m + 1);
    FOR(j, 1, m + 1) a[i][j] = rd();
    rmx[i][m] = rmn[i][m] = a[i][m];
  }
  ans[n + 1] = '\0';
  FOR(i, 1, n + 1) {
    ROF(j, 1, m) {
      rmn[i][j] = min(rmn[i][j + 1], a[i][j]);
      rmx[i][j] = max(rmx[i][j + 1], a[i][j]);
    }
  }
  FOR(i, 1, m) {
    FOR(j, 1, n + 1) {
      chkmin(mn[j], a[j][i]);
      chkmax(mx[j], a[j][i]);
      L[j].fi.fi = mn[j];
      L[j].fi.se = mx[j];
      L[j].se = j;
      R[j].fi.se = rmn[j][i+1];
      R[j].fi.fi = rmx[j][i+1];
      R[j].se = j;
    }
    set<u64> S;
    sort(L + 1, L + n + 1);
    sort(R + 1, R + n + 1);
    for (u64 l = 1, cur = 1, mr = 0; l < n; ++l) {
      cur = (__int128)cur * (56466486 ^ L[l].se) % 15131293129102979ull;
      chkmax(mr, L[l].fi.se);
      if (mr >= L[l + 1].fi.fi) continue;
      S.insert(cur);
    }
    for (u64 r = n, cur = 1, ml = 1e7; r > 1; --r) {
      cur = (__int128) cur * (56466486 ^ R[r].se) % 15131293129102979ull;
      chkmin(ml, R[r].fi.se);
      if (ml <= R[r - 1].fi.fi) continue;
      if (S.find(cur) != S.end()) {
        println("YES");
        FOR(i, r, n + 1) ans[R[i].se] = 'B';
        println(ans + 1, i);
        return;
      }
    }
  }
  println("NO");
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
