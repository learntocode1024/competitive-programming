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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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

const int n = 5, m = 5, X = 10;
r32 e{-X,X};

int main() {
  O(n,m);
  FOR(i,0,n) {
    int x = e(rng), y = e(rng);
    O(x,y);
    cerr << "(" << x << ',' << y << ")\n";
  }
  FOR(i,0,n) {
    int a = e(rng), b = e(rng), c = e(rng);
    c = 0;
    do {
     a = e(rng), b = e(rng), c = e(rng);
     c = 0;
    } while (!a && !b);
    O(a,b,c);
    cerr << a << "x+" << b << "y+" << c << ">0\n";
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
