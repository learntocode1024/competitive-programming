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
const int N = 0;
inline string getl(int k, int l, int r) {
  ++r;
  string ret;
  FOR(i, l, r) {
    ret += "AB"[i%(k+1)==k];
  }
  return ret;
}

inline string getr(int k, int l, int r) {
  ++r;
  string ret;
  FOR(i, l, r) {
    ret += "BA"[i%(k+1)==0];
  }
  return ret;
}

inline string solve() {
  i64 a, b, s,t;
  rd(a,b,s,t);
  i64 n = a + b;
  __int128 k = ceil(1.0l*max(a,b)/(min(a,b)+1));
  i64 l = 0, r = 1e9;
  while (r - l > 1) {
    i64 m = l + (r - l) / 2;
    if (b-m<=k*(a-m*k)) l = m;
    else r = m;
  }
  i64 L = l * (k+1);
  a -= l*k;
  b -= l;
  i64 R =n - b/k * (k+1) + 1;
  a -= b/k;
  b %= k;
  string ret;
  if (s <= L) ret += getl(k,s-1, min(t,L)-1);
  if (max(s,L+1) <= min(R-1,t)) {
    int li = max(s,L+1)-L-1, ri = min(R-1, t)-L-1;
    int mid = a;
    if (ri<mid) {
      ret += string(ri-li+1, 'A');
    } else if (li >= mid) {
      ret += string(ri-li+1,'B');
    } else {
      ret += string(mid-li, 'A') + string(ri-mid+1, 'B');
    }
  }
  if (t >= R) {
    ret = ret + getr(k,max(R,s)-R, t-R);
  }
  return ret;
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
  println(solve());
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

