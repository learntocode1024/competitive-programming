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
set<i64> S;
inline void init() {
  FOR(i, 0, 30) {
    i64 x = 1ull << (i*2);
    S.insert(x);
    i64 to = 1;
    for (int j = 0; j < i; ++j, to <<= 2) {
      S.insert(x+to);
    }
    x <<= 1;
    S.insert(x);
    to = 2;
    for (int j = 0; j < i; ++j, to <<= 2) {
      S.insert(x+to);
    }
  }
}

inline void solve() {
  i64 x;
  rd(x);
  if (S.find(x) != S.end()) O(-1);
  else if (x % 3 == 0) {
    O(1, x);
  } else {
    int c0 = 0, c1 = 0;
    i64 s, t;
    FOR(i,0,60) {
      if (((x>>i)&1)) {
        if (i&1) ++c1;
        else ++c0;
      } 
    }
    if (!c0 || !c1) {
      int d = (c0 - c0 % 3) | (c1 - c1 % 3);
      for (int i = 0, j = 0; i <= 60 && j < d; ++i) {
        if ((x>>i)&1) {
          ++j;
          s |= 1ull << i;
        }
      }
      for (int i = 60, j = 0; i >= 0 && j < d; --i) {
        if ((x>>i)&1) {
          ++j;
          s |= 1ull << i;
        }
      }
    } else if (c1%3==(c0+1)%3) {
      for (int i = 1; i < 60; i += 2) {
        if ((x>>i)&1) {
          s = 1ull << i;
          break;
        }
      }
      for (int i = 0; i <= 60; i += 2) {
        if ((x>>i)&1) {
          t = 1ull << i;
          break;
        }
      }
      t |= s;
      s = x ^ s;
    } else {
      for (int i = 1; i < 60; i += 2) {
        if ((x>>i)&1) {
          s = 1ull << i;
          break;
        }
      }
      for (int i = 0; i <= 60; i += 2) {
        if ((x>>i)&1) {
          t = 1ull << i;
          break;
        }
      }
      s |= t;
      t = x ^ t;
    }
    O(2, s, t);
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
  init();
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

