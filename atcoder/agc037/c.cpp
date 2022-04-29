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
const int N = 2e5+5;
int a[N];
int b[N];
priority_queue<pii> pq;

inline void solve() {
  int n;
  rd(n);
  FOR(i,0,n-1) rd(a[i]);
  FOR(i,0,n-1) rd(b[i]);
  FOR(i,0,n-1) if (a[i] > b[i]) {
    O(-1);
    return;
  } else if (a[i] < b[i]) {
    pq.push({b[i], i});
  }
  i64 ans = 0;
  while (!pq.empty()) {
    auto x = pq.top();
    pq.pop();
    int r = b[(x.se+1)%n] + b[(x.se+n-1)%n];
    int q = (b[x.se] - a[x.se]) / r;
    if (b[x.se]<r || !q) {
      O(-1);
      return;
    }
    b[x.se] -= q * r;
    ans += q;
    if (b[x.se] > a[x.se]) pq.push({b[x.se], x.se});
  }
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

