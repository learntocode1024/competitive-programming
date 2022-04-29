#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1e5+5;
int n, m;
int p[N];

int main() {
  rd(n);
  FOR(i,1,n) rd(p[i]);
  rd(m);
  if (m >= n) {
    O("0 pts!");
    return 1;
  }
  int om = m;
  while (m--) {
    int a, c;
    rd(a,c);
    p[a] += c;
    p[a+1] += c;
    if (p[a] < 0 || p[a+1] < 0) {
      O("negative!");
      return 1;
    }
  }
  FOR(i,2,n) {
    if (p[i] != p[1]) {
      O("invalid!");
      FOR(j,1,n) cout << p[j] << " \n"[j==n];
      return 1;
    }
  }
  cout << "ok: " << om << '/' << n << '\n';
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

