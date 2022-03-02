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
const int N = 1e5+5;
int n;
int s[N][3];
int a[N];
bool b[N], vis[N], v[N];

inline void solve() {
  rd(n);FOR(j,0,3)FOR(i, 0, n) cin >> s[i][j];
  FOR(i,0,n) {
    if (s[i][0] + 1 == s[i][1] && s[i][2] - 1 == s[i][1] && s[i][1] % 3 == 2) a[i+1] = s[i][2]/3;
    else if (s[i][0] - 1 == s[i][1] && s[i][2] + 1 == s[i][1] && s[i][1] % 3 == 2) a[i+1] = s[i][0]/3, b[i+1]=1;
    else {
      println("No");
      return;
    }
  }
  for (int i = 1; i <= n; i += 2) vis[a[i]] = 1;
  for (int i = 1; i <= n; i += 2) if (!vis[i]) {
    println("No");
    return;
  }
  bool b1 = 0, b2 = 0;
  FOR(i, 1, n + 1) {if (i & 1) b1 ^= b[i]; else b2 ^= b[i];}
  int c2 = n / 2, c1 = n - c2;
  for (int i = 1; i <= n; i += 2) {
    if (v[i]) continue;
    for (int c = i; !v[c]; c = a[c]) v[c] = 1;
    --c1;
  }
  for (int i = 2; i <= n; i += 2) {
    if (v[i]) continue;
    for (int c = i; !v[c]; c = a[c]) v[c] = 1;
    --c2;
  }
  c1 &= 1;
  c2 &= 1;
  if ((b1 ^ c2) || (c1 ^ b2)) {
    println("No");
    return;
  }
  println("Yes");
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

