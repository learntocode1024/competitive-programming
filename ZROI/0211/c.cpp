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
const int N = 4e4+5, M = 20;
string s[M+1];
char t[N], r[N], tmp[N];

void cyc(char *str, int n) {
  int k = 0, i = 0, j = 1;
  while (k < n && i < n && j < n) {
    if (str[(i + k) % n] == str[(j + k) % n]) {
      k++;
    } else {
      str[(i + k) % n] > str[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
      if (i == j) i++;
      k = 0;
    }
  }
  i = min(i, j);
  FOR(k, 0, n) tmp[k] = str[k];
  FOR(k, 0, n) str[k] = tmp[(i+k)%n];
}

inline void solve() {
  cin >> s[1] >> s[2];
  FOR(i, 3, M+1) {
    s[i] = s[i-1] + s[i-2];
  }
  int q;
  cin >> q;
  while (q--) {
    int id;
    cin >> id >> t;
    int m = strlen(t);
    cyc(t, m);
    int n = s[id].length();
    int ans = 0;
    FOR(i, 0, n - m+1) {
      FOR(j, i, i + m) r[j-i] = s[id][j];
      cyc(r, m);
      bool ok = 1;
      FOR(j, 0, m) if (t[j] != r[j]) ok = 0;
      ans += ok;
    }
    println(ans);
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
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

