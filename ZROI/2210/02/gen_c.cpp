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
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;

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

mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());

//#define MULTI
const int N = 0;
int n = 5, m = 5, q = 10;


int main() {
  r32 e{1, n}, e1{1, 1000000000};
  println(n, m, q);
  FOR(i, 0, m) {
    int x = e(rng), y = e(rng), z = e(rng), w = e(rng);
    if (x > z) swap(x, z);
    if (y > w) swap(y, w);
    println(x, y, z, w, e(rng));
  }
  FOR(i, 0, q) {
    int x = e(rng), y = e(rng), z = e(rng), w = e(rng);
    if (x > z) swap(x, z);
    if (y > w) swap(y, w);
    println(x, y, z, w);
  }
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

