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
const int N = 1e5+5, M = 1005;
typedef bitset<M> bs;
char s[N];
int n;
char t0[M], t[M];
bs v[30];

int work(int m, int l) {
  for (int i = 0; i < 26; ++i) {
    v[i].reset();
    for (int j = 0; j < m; ++j) {
      if (t[j] == '.' || t[j] == i + 'a') v[i].set(j);
    }
  }
  bs dp;
  for (;l < n; ++l) {
    bs tmp = dp << 1;
    tmp.set(0);
    dp = tmp & v[s[l] - 'a'];
    if (dp[m-1]) return l + 1;
  }
  return l + 1;
}

inline void solve() {
  cin >> s;
  n = strlen(s);
  int k;
  cin >> k;
  FOR(_, 0, k) {
    memset(t0, 0, sizeof(t0));
    cin >> t0;
    int m = strlen(t0);
    t0[m] = '*';
    int r = 0, l = -1;
    for (int i = 0, c = 0; i < m + 1; ++i) {
      if (t0[i] == '*') {
        if (c < i) {
          for (int j = c; j < i; ++j) {
            t[j-c] = t0[j];
          }
          r = work(i - c, r);
          if (l == -1) l = r - (i - c) + 1;
        }
        c = i + 1;
      } else continue;
    }
    if (r > n) println("0 0");
    else {
      if (t0[0] == '*') l = 1;
      println(l,r);
    }
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

