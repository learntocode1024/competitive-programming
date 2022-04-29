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

//#define MULTI
const int N = 1e5+5;
int m, n;
int p[N], ol[N], oc[N];
#define op(x,y) {++m;ol[m] = x; oc[m] = y;}
#define swp(x,y) swap(p[x],p[y]);
#define PA4 swp(i+2,i+3);\
        op(i,k-i);\
        op(i+1,-1);\
        op(i+2,k-i-2);
#define PB4 swp(i-2,i-3);\
        op(i-1,k-i);\
        op(i-2,1);\
        op(i-3,k-i+2);

inline void solve() {
  rd(n);
  iota(p,p+n+1,0);
  if (n&1) {
    int k = n/2+1, d = k-1;
    if (d % 4 == 0) {
      for (int i = k+1; i < n; i += 4) {
        PA4
      }
      for (int i = k - 1; i; i -= 4) {
        PB4
      }
    } else if (d % 4 == 3) {
      swp(k+2,k+3);
      op(k+1,-1);
      op(k+2,-2);
      for (int i = k + 4; i < n; i += 4) {
        PA4
      }
      swp(k-2,k-3);
      op(k-2,1);
      op(k-3,2);
      for (int i = k - 4; i; i -= 4) {
        PB4
      }
    } else if (d % 4 == 2) {
      op(k-1,-1);
      op(k,1);
      op(k+1,-2);
      op(k-2,2);
      for (int i = k + 3; i < n; i += 4) {
        PA4
      }
      for (int i = k - 3; i; i -= 4) {
        PB4
      }
    } else {
      op(k-1,1);
      op(k,-1);
      for (int i = k + 2; i < n; i += 4) {
        PA4
      }
      for (int i = k - 2; i; i -= 4) {
        PB4
      }
    }
  } else {
    int k = n / 2;
    if (k % 4 == 0) {
      for (int i = k + 1; i < n; i += 4) {
        PA4
      }
      swp(k-2,k-3);
      op(k-2,1);
      op(k-3,2);
      for (int i = k - 4; i; i -= 4) {
        PB4
      }
    } else {
      int n1 = n - 4;
      if (n1) {
        k = n1 / 2;
      for (int i = k + 1; i < n1; i += 4) {
        PA4
      }
      swp(k-2,k-3);
      op(k-2,1);
      op(k-3,2);
      for (int i = k - 4; i; i -= 4) {
        PB4
      }

      } else k = 0;
      int i = n1 + 1;
      PA4
    }
  }
  FOR(i,1,n) cout << p[i] << " \n"[i==n];
  O(m);
  FOR(i,1,m) O(ol[i], oc[i]);
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

