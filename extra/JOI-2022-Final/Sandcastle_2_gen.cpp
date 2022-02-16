#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
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
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 5e4+5;
vector<vector<int> > a;
int h, w;
int U, D, L, R;
vector<vector<int> > f[3][3][3][3];

inline int sum_2d(const vector<vector<int> > &g, int i1, int i2, int j1, int j2) {
  int ret = g[i2][j2];
  --i1, --j1;
  if (i1 >= 0 && j1 >= 0) ret += g[i1][j1];
  if (i1 >= 0) ret -= g[i1][j2];
  if (j1 >= 0) ret -= g[i2][j1];
  return ret;
}
inline bool cap(pii &a, pii b) {
  if (b.fi > b.se) return 1;
  chkmin(a.se, b.se);
  chkmax(a.fi, b.fi);
  if (a.fi > a.se) return 1;
  return 0;
}

#define F3(i) FOR(i, 0, 3)
#define F5(i) FOR(i, 1, 7)
string pref(string a, string b, int x, int y, int z) {
  if (z - x < y - z) {
    return a + "+" + to_string(z-x);
  } else return b + "-" + to_string(y - z);
}
inline int count(int i1, int i2, int j1, int j2) {
  int ans = 0;
  F3(u) F3(d) F3(l) F3(r) {
    pii ud = {i1, i2}, lr = {j1, j2};
    if (cap(ud, u != 2 ? mkp(i1 + u, i1 + u) : mkp(i1 + 2, i2))) continue;
    if (cap(ud, d != 2 ? mkp(i2 - d, i2 - d) : mkp(i1, i2 - 2))) continue;
    if (cap(lr, l != 2 ? mkp(j1 + l, j1 + l) : mkp(j1 + 2, j2))) continue;
    if (cap(lr, r != 2 ? mkp(j2 - r, j2 - r) : mkp(j1, j2 - 2))) continue;
    // ans += sum_2d(f[u][d][l][r], ud.fi, ud.se, lr.fi, lr.se);
    cout << "ans += sum_2d(f["<<u<<"]["<<d<<"]["<<l<<"]["<<r<<"], "<<pref("i1", "i2", i1, i2, ud.fi)<<", "<<pref("i1", "i2", i1, i2, ud.se)<<", "<<pref("j1", "j2", j1, j2, lr.fi)<<", "+pref("j1", "j2", j1, j2, lr.se)+");\n";
  }
  return ans;
}

inline void gen() {
  println ("switch (hh) {");
  F5(i) { 
    if (i == 5) continue;
    if (i < 5) cout << "  case " << i << ":\n";
    else cout << "default:\n";
      println ("switch (ww) {");
    F5(k) {
    if (k == 5) continue;
    if (k < 5) cout << "  case " << k << ":\n";
    else cout << "default:\n";
    count(0,i-1,0,k-1); 
  cout << "break;\n";
  }
  cout << "}\n";
  cout << "break;\n";
  }
  println("}");
}


int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    gen();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

