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

//#define MULTI
const int N = 0;
int ask(int i, int j, int k) {
  cout << "? " << i << ' ' << j << ' ' << k << endl;
  int ret;
  cin >> ret;
  return ret;
}
int n;

int a[4], b[4];
void get() {
  b[0] = ask(a[3], a[1], a[2]);
  b[1] = ask(a[0], a[2], a[3]);
  b[2] = ask(a[0], a[1], a[3]);
  b[3] = ask(a[0], a[1], a[2]);
  int mx = -1;
  FOR(i, 0, 4) chkmax(mx, b[i]);
  int t = 0;
  FOR(i, 0, 4) {
    if (b[i] == mx) {
      ++t;
    }
  }
  if (t == 2) {
    FOR(i, 0, 4) if (b[i] == mx) a[i] = 1e9+7;
  } else if (t == 3) {
    int ss = 0;
    FOR(i, 0, 4) {
      if (b[i] == mx && ss < 2) {
        ++ss;
        a[i] = 1e9+7;
      }
    }
  } else {
    if (mx == 0) return;

  }
  sort(a, a + 4);
}

inline void solve() {
  cin >> n;
  iota(a, a + 4, 1);
  get();
  for (int i = 4; i < n; i += 2) {
    a[2] = i+1;
    if (i+2 != n+1) a[3] = i+2;
    else {
      int t = 1;
      for (; t <= n; ++t) {
        if (t != a[0] && t != a[1]) break;
      }
      a[3] = t;
    }
    get(i);
  }
  cout << "! " << a[0] << ' ' << a[1] << endl;
}

int main() {
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
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

