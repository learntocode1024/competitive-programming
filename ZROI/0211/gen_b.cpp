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

const int n = 300;
int e[n], o[n];

void gen_tree() {
  iota(o, o + n - 2, n+1);
  iota(e, e + n, 1);
  shuf(o, o + n - 2);
  shuf(e, e + n);
  int t = 0;
  FOR(i, 1, n - 1) {
    println(e[i], o[t]);
    println(e[i+1], o[t]);
    e[i+1] = o[t++];
    shuf(e+i+1, e+n);
  }
  println(e[n-1], e[0]);
}

int main() {
  println(n);
  gen_tree();
  gen_tree();
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
