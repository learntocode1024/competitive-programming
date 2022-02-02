#include <bits/stdc++.h>
#include "matrix.h"
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
/*
ceil(pow(_getrow(a), 2.3))
*/

r32 e{50, 200};
r32 g{0, 998244352};
const int T = 50;

void run_test1() {
  int n = e(rng), m = e(rng);
  if (n > m) swap(n, m);
  set_cost(1e9);
  setmatrix(0, n, n);
  setmatrix(1, n, m);
  FOR(i, 0, n) FOR(j, 0, n) setmatrixnum(0, i, j, g(rng));
  FOR(i, 0, n) FOR(j, 0, m) setmatrixnum(1, i, j, g(rng));
  set_cost(2*m*ceil(pow(n, 1.3)));
  int c = square_mul_normal();
}

void run_test() {
  int n = e(rng);
  set_cost(1e9);
  setmatrix(0, n, n);
  set_cost(4*ceil(pow(n, 2.3))*ceil(log2(n))); 
  shortest_path();
}

int main() {
  FOR(_, 0, T) run_test();
  println("pass");
  return 0;
}