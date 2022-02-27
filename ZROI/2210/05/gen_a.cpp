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

typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());
inline pii rpii(r32 &e) {
  int a = e(rng), b = e(rng);
  if (a > b) swap(a, b);
  return {a, b};
}
#define shuf(BEGIN, END) shuffle(BEGIN, END, rng)

const int n = 1000000;

int main() {
  println(n);
  r32 e{0, n+1};
  r32 f{0, 2};
  FOR(i, 0, n) cout << (f(rng) == 0 ? 0 : min(e(rng), e(rng))) << " \n"[i==n-1];
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
