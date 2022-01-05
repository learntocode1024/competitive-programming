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

const int N = 1e4+5;
int n;
bool v[N];
int p[N];
int t = 0;

int f(int x) {
  ++t;
  println('?', x);
  int ret;
  cin >> ret;
  return ret;
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) v[i] = 0;
  FOR(i, 1, n + 1) if (!v[i]) {
    int c = f(i), l = 0;
    vector<int> q;
    while (!v[c]) {
      ++l;
      v[c] = 1; 
      c = f(i);
      q.pb(c);
    }
    p[q[l - 1]] = q[0];
    FOR(i, 0, l - 1) {
      p[q[i]] = q[i + 1];
    }
  }
  cout << "! ";
  FOR(i, 1, n + 1) cout << p[i] << " \n"[i==n];
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

