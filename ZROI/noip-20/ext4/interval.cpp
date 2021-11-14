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

const int N = 3e5+5;
vector<int> a[N];
int n;
int c[N];
inline void add(int x) {
  for (; x <= n; x += x & -x) {
    ++c[x];
  }
}

inline int cnt(int x) {
  int ret = 0;
  for (; x; x -= x & -x) {
    ret += c[x];
  }
  return ret;
}

bool chk(int x) {
  FOR(i, 1, n + 1) c[i] = 0;
  ROF(i, x, n + 1) {
    for (auto l : a[i]) {
      add(l);
    }
    if (cnt(i - x + 1) >= x) return true;
  }
  return false;
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) {
    int l, r;
    cin >> l >> r;
    a[r].pb(l);
  }
  int l = 1, r = n + 1;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  println(l);
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

