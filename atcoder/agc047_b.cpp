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

const int N = 1e6+5, NN = 2e5+5;
int ch[N][26];
bool ed[N];
int tot;
string s[NN];
int vis[NN][26];

inline void solve() {
  tot = 1;
  int n;
  rd(n);
  FOR(i, 0, n) rd(s[i]);
  FOR(i, 0, n) {
    reverse(begin(s[i]), end(s[i]));
    for (auto &c : s[i]) c -= 'a', ++vis[i][c];
    int p = 1;
    for (auto c : s[i]) {
      if (!ch[p][c]) ch[p][c] = ++tot;
      p = ch[p][c];
    }
    ed[p] = 1;
  }
  i64 ans = 0;
  FOR(i, 0, n) {
    int p = 1;
    for (auto c : s[i]) {
      for (int ic = 0; ic < 26; ++ic) {
        if (ic != c && ed[ch[p][ic]] && vis[i][ic]) ++ans;
      }
      if (ed[p]) ++ans;
      p = ch[p][c];
      --vis[i][c];
    }
  }
  println(ans);
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

