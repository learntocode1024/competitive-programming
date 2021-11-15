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

const int N = 205;
int a[N], b[N], c[N];

inline void solve() {
  int n;
  FOR(i, 0, N) a[i] = b[i] = c[i] = 0;
  cin >> n;
  FOR(i, 0, n) {
    int x;
    cin >> x;
    ++a[x+100];
  }
  FOR(i, 0, n) {
    int x;
    cin >> x;
    ++b[x+100];
  }
  FOR(i, 0, N - 1) {
    if (a[i] + c[i] > b[i]) {
      int t = a[i] + c[i] - b[i];
      if (t > a[i]) {
        cout << "NO\n";
        return;
      }
      c[i + 1] = t;
    } else if (a[i] + c[i] < b[i]) {
      cout << "NO\n";
      return;
    }
  }
  if (a[N - 1] + c[N - 1] != b[N - 1]) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
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

