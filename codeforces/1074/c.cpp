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
const int N = 3e5+5;
int D(pii x, pii y) {
  return abs(x.fi - y.fi) + abs(x.se - y.se);
}

pii a, b, c, d;
pii p[N];

inline void solve() {
  int n;
  cin >> n;
  int x, y;
  rd(x, y);
  p[0] = a = b = c = d = {x,y};
  FOR(i, 1, n) {
    rd(x, y);
    p[i] = {x, y};
    if (x < a.fi) a = p[i];
    if (x > b.fi) b = p[i];
    if (y < c.se) c = p[i];
    if (y > d.se) d = p[i];
  }
  int a1 = -1;
  pii f[4] = {a,b,c,d};
  FOR(i, 0, 4) FOR(j, i+1, 4) FOR(k, 0, n) {
    chkmax(a1, D(f[i], f[j])+D(f[i],p[k])+D(f[j],p[k]));
  }
  print(a1," ");
  int ans = D(a,c)+D(c,b)+D(b,d)+D(d,a);
  FOR(i, 4, n+1) print(ans, " \n"[i==n]);
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
  solve();
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

