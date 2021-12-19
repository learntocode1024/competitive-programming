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

const int N = 5e5+5;
int c[N<<1], to[N];
int f[N<<1];
int d[N];
int n;
int get(int x) {
  if (x == f[x]) return x;
  return f[x] = get(f[x]);
}

inline void solve() {
  cin >> n;
  int tot = 1, fe = N;
  iota(c, c + N, 0);
  iota(f, f + N, 0);
  iota(to, to + N, 0);
  FOR(i, 0, n) {
    int op, x;
    rd(op, x);
    if (op == 1) {
      f[fe] = to[x];
      d[tot] = fe;
      ++tot;
      ++fe;
    } else {
      int y;
      cin >> y;
      if (x == y) continue;
      f[get(to[x])] = get(to[y]);
      to[x] = fe;
      c[fe] = x;
      f[fe] = fe;
      ++fe;
    }
  }
  FOR(i, 1, tot) {
    cout << c[get(d[i])] << " \n"[i == tot - 1];
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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

