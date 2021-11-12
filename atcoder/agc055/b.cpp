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
char s[N], t[N];
int n;
int a[N], b[N];

inline void solve() {
  cin >> n >> s >> t;
  FOR(i, 0, n) s[i] -= 'A', t[i] -= 'A';
  FOR(i, 0, n) s[i] = (s[i] - i % 3 + 3) % 3;
  FOR(i, 0, n) t[i] = (t[i] - i % 3 + 3) % 3;
  int t1 = 0, t2 = 0;
  FOR(i, 0, n) {
    a[++t1] = s[i];
    if (t1 > 2 && a[t1] == a[t1-1] && a[t1] == a[t1-2]) t1 -= 3;
  }
  FOR(i, 0, n) {
    b[++t2] = t[i];
    if (t2 > 2 && b[t2] == b[t2-1] && b[t2] == b[t2-2]) t2 -= 3;
  }
  FOR(i, 1, t1 + 1) {
    if (t1 != t2 || a[i] != b[i]) {
      println("NO");
      return;
    }
  }
  println("YES");
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

