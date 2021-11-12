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

const int N = 1e6+5;
const int p = 1e9+7;
const int i2 = 5e8+4;
inline void red(i64 &x) { if (x >= p) x -= p; }
char s[N];

inline i64 f1(i64 x) {
  return (x + p - x * x % p) % p;
}

inline i64 f2(i64 x) {
  return (x + x * x) % p;
}

int tl;
i64 c1[N], c2[N];

inline void solve() {
  cin >> s + 1;
  i64 ans = 0;
  tl = 1;
  c1[1] = c2[1] = 0;
  for (int i = 1; s[i]; ++i) {
    if (s[i] == '(') {
      ++c1[tl];
      red(c2[tl] += f1(i));
      ++tl;
      c1[tl] = c2[tl] = 0;
    } else {
      if (tl > 1) {
        --tl;
        ans = (ans + c1[tl] * f2(i) + c2[tl]) % p;
      } else {
        tl = 1;
        c1[tl] = c2[tl] = 0;
      }
    }
    s[i] = '\0';
  }
  cout << ans * i2 % p << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  int T;
  cin >> T;
  while (T--)
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

