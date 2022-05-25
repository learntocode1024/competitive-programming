/** @file
 * @ingroup searching


 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI
const int N = 0;
unordered_set<string> s;
queue<pair<string,int> > q;

string mul(const string &a, int x) {
  string ret;
  int cy = 0;
  for (int i = a.size() - 1; i>=0; --i) {
    int u = a[i] - '0';
    int c = cy + u * x;
    cy = c / 10;
    ret.pb('0' + c % 10);
  }
  if (cy) ret.pb(cy+'0');
  reverse(begin(ret), end(ret));
  return ret;
}

bool vs[10];
vector<int> uni(const string &s) {
  vector<int> ret;
  FOR(i,0,9) vs[i] = 0;
  for (auto c : s) vs[c-'0'] = 1;
  FOR(i,2,9) if (vs[i]) ret.pb(i);
  return ret;
}

inline void sol() {
  int n;
  string num;
  rd(n, num);
  q.push({num, 0});
  s.insert(num);
  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();
    if (u.length() >= n) {
      O(d);
      return;
    }
    for (auto c : uni(u)) {
      string v = mul(u, c);
      if (s.find(v) == s.end()) {
        if (v.length() >= n) {
          O(d+1);
          return;
        }
        s.insert(v);
        q.push({v, d+1});
      }
    }
  }
  O(-1);
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}

