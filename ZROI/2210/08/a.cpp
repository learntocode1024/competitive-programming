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

#define MULTI
const int N = 1e6+5;
const int P = 998244353;
char s[N], t[N];
int n;
int p[3];

inline void solve() {
  rd(n,s,t);
  i64 ans = 0;
  iota(p,p+3,0);
  do {
    i64 cur = 1;
    bool ok = 1;
    for (int i = 0; i <= n*2; i += 2) {
      if (s[i] != 'A'+p[0] && s[i] != '?') ok = 0;
    }
    if (!ok) continue;
    for (int i = 1; i <= n*2; i += 2) {
      if (s[i] == 'A'+p[0]) cur = 0;
      else if (s[i] == '?') cur = (cur*2) % P;
    }
    for (int i = 0; i <= n*2; i += 2) {
      if (t[i] != 'A'+p[1] && t[i] != '?') cur = 0;
    }
    for (int i = 1; i <= n*2; i += 2) {
      if (t[i] != 'A'+p[2] && t[i] != '?') cur = 0;
    }
    ans = (ans + cur) % P;
  } while(next_permutation(p,p+3));
  do {
    i64 cur = 1;
    bool ok = 1;
    for (int i = 0; i <= n*2; i += 2) {
      if (t[i] != 'A'+p[0] && t[i] != '?') ok = 0;
    }
    if (!ok) continue;
    bool b1 = 1;
    bool b2 = 1;
    for (int i = 1; i <= n*2; i += 2) {
      if (t[i] == 'A'+p[0]) cur = 0;
      else if (t[i] == '?') cur = (cur*2) % P;
      if (t[i] != '?' && t[i] != 'A'+p[1]) b1 = 0;
      if (t[i] != '?' && t[i] != 'A'+p[2]) b2 = 0;
    }
    if (b1) --cur;
    if (b2) --cur;
    cur = (cur + P) % P;
    for (int i = 0; i <= n*2; i += 2) {
      if (s[i] != 'A'+p[1] && s[i] != '?') cur = 0;
    }
    for (int i = 1; i <= n*2; i += 2) {
      if (s[i] != 'A'+p[2] && s[i] != '?') cur = 0;
    }
    ans = (ans + cur) % P;
  } while(next_permutation(p,p+3));
  O(ans);
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

