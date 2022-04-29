#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void wrtln(const T &x) { cout << x << '\n'; }
template <typename T, typename... W>
inline void wrtln(const T &x, const W &...b) {
  cout << x << ' ';
  wrtln(b...);
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
const int N = 5e5+5;
char s[3][N];
int V[N], E[N], F[N];
map<pii, int> S;

inline void sol() {
  int n;
  cin >> n;
  FOR(i,0,2) cin >> s[i] + 1;
  FOR(i,1,n) {
    V[i] += V[i-1];
    FOR(j,0,2) V[i] += s[j][i] == '1';
    V[i] -= s[0][i] == '1' && s[1][i] == '1';
    V[i] -= s[2][i] == '1' && s[1][i] == '1';
  }
  FOR(i,2,n) {
    E[i] = E[i-1];
    FOR(j,0,2) if (s[j][i-1] == '1' && s[j][i] == '1') ++E[i];
  }
  FOR(i,2,n) {
    F[i] = F[i-1];
    F[i] += s[0][i] == '1' && s[1][i] == '1' && s[0][i-1] == '1' && s[1][i-1] == '1';
    F[i] += s[2][i] == '1' && s[1][i] == '1' && s[2][i-1] == '1' && s[1][i-1] == '1';
  }
  int tot = 0;
  for (int i = 2; i < n; ++i) {
    if (s[1][i] != '0') continue;
    int j = i;
    while (j < n && s[1][j+1] == '0') ++j;
    bool ok = j < n;
    FOR(k,0,2) ok &= s[k][i-1] == '1';
    FOR(k,0,2) ok &= s[k][j+1] == '1';
    FOR(k,i,j) ok &= s[0][k] == '1';
    FOR(k,i,j) ok &= s[2][k] == '1';
    if (ok) {
      S[{i,j}] = ++tot;
    }
    i = j + 1;
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    int ans = V[r] - V[l-1];
    ans -= E[r] - E[l];
    ans += F[r] - F[l];
    int f1 = 0;
    auto it = S.upper_bound({l,N});
    if (it != S.end()) {
      int L = it->se;
      auto it2 = S.lower_bound({r,0});
      if (it2 != S.begin()) {
        --it2;
        if (it2->fi.se >= r && it2 != S.begin()) --it2;
        ckmax(f1, it2->se - L + 1);
      }
    }
    wrtln(ans + f1);
  }
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

