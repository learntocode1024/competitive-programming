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
const int N = 205, B = 63;
i64 x[B], a[N];
char s[N];
bool ins(i64 v) {
  ROF(i,0,B-1) {
    if ((v>>i)&1) {
      if (x[i]) v ^= x[i];
      else {
        FOR(j,i+1,B-1) if (((v>>j)&1) && x[j]) v ^= x[j];
        x[i] = v;
        FOR(j,0,i-1) if ((x[j]>>i)&1) x[j] ^= v;
        return true;
      }
    }
  }
  return false;
}

inline void solve() {
  int n;
  rd(n);
  FOR(i,0,B-1) x[i] = 0;
  FOR(i,0,n-1) rd(a[i]);
  rd(s);
  ROF(i,0,n-1) {
    if (ins(a[i]) && s[i] == '1') {
      O("1");
      return;
    }
  }
  O("0");
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

