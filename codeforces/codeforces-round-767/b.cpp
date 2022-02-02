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

#define MULTI
const int N = 1e5+5;
string s[N];
int n;
set<string> S, T, A, B;

inline void solve() {
  rd(n);
  S.clear();
  T.clear();
  A.clear();
  B.clear();
  FOR(i, 0, n) cin >> s[i];
  bool ok = 0;
  FOR(i, 0, n) {
    if (s[i].length() == 1) ok = 1;
    if (s[i].length() == 2 && s[i][0] == s[i][1])  ok = 1;
    if (s[i].length() == 3 && s[i][0] == s[i][2]) ok = 1;
  }
  FOR(i, 0, n) {
    if (s[i].length() == 2) {
      if (S.find(s[i]) != S.end()) ok = 1;
      string ss = s[i];
      swap(ss[0], ss[1]);
      S.insert(ss);
    } else {
      if (T.find(s[i]) != T.end()) ok = 1;
      string ss = s[i];
      swap(ss[0], ss[2]);
      S.insert(ss);
    }
  }
  FOR(i, 0, n) {
    if (s[i].length() == 2) {
      if (B.find(s[i]) != B.end()) ok = 1;
      string ss = s[i];
      swap(ss[0], ss[1]);
      A.insert(ss);
    } else {
      string ss;
      ss.pb(s[i][1]);
      ss.pb(s[i][2]);
      if (A.find(ss) != A.end()) ok = 1;
      ss.clear();
      ss.pb(s[i][1]);
      ss.pb(s[i][0]);
      B.insert(ss);
    }
  }
  println(ok?"YES" :"NO");
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

