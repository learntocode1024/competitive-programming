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

const int N = 1e9+7;
inline i64 qry(int l, int r) {
  cout << "? " << l << ' ' << r << endl;
  i64 ret;
  cin >> ret;
  return ret;
}

inline void solve() {
  int n;
  int i, j, k;
  cin >> n;
  i64 all = qry(1, n);
  int l = 1, r = n;
  while (r - l > 1) {
    int mid = l + (r - l) / 2;
    if (qry(1, mid) == all) r = mid;
    else l = mid;
  }
  k = r;
  int l2 = qry(1, k) - qry(1, k - 1);
  j = k - l2;
  int l1 = qry(1, j - 1) - qry(1, j - 2);
  i = j - 1 - l1;
  cout << "! " << i << ' ' << j << ' ' << k << endl;
}

int main() {
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

