#include <bits/stdc++.h>
using namespace std;
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
} // namespace IO
template<typename T>
inline void rdint(T &a) {
  a = IO::rd();
}
template<typename A, typename... B>
inline void rdint(A &a, B& ...b) {
  a = IO::rd();
  rdint(b...);
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
const int N = 1e6+5;
const int P = 998244353q;

int n, k;
int a[N], s[N];
map<int, int> cnt, pre, cc;

inline int c2(i64 x) {
  return (x * (x - 1) / 2) % P;
}

struct qry {
  int s, l, r, c;
} q[N];
int m;
int o[N], c[N], e[N];
bool 

int sum(int x) {
  int ret = 0;
  for (;x;x-=x&-x) ret = (ret + c[x]) % P;
  return ret;
}

void ch(int x, int v) {
  for (;x<=n;x+=x&-x) c[x] = (c[x] + v) % P; 
}

void flip(int x) {
  
}

inline void solve() {
  rdint(n, k);
  FOR(i, 1, n + 1) rdint(a[i]);
  FOR(i, 1, n + 1) s[i] = (s[i-1] + a[i]) % k;
  FOR(i, 0, n + 1) {
    ++cnt[s[i]];
  }
  int ans = c2(n+1);
  for (auto &i : cnt) {
    ans = (ans + P - c2(i.se)) % P;
  }
  ans = (P - ans) % P;
  FOR(i, 0, n + 1) {
    if (pre.find(s[i]) == pre.end()) {
      pre[s[i]] = i;
      continue;
    }
    ++cc[s[i]];
    --cnt[s[i]];
    [m++] = {s[i], pre[s[i]]+1, i, 1ll * cc[s[i]] * cnt[s[i]] % P};
  }
  sort(q, q + m);
  int s = 0, d = k / 2;

  /*FOR(i, 1, n + 1) if (fir[i]) {
    int t = cnt[s[i-1]] - 1, l = 1;
    int cs = s[i-1];
    int b = 0;
    for (int j = i; j <= n && t; ++j) {
      b = (b + a[j]) % k;
      ans = (ans + 1ll * t * l * min(b, k - b)) % P;
      if (s[j] == cs) {
        --t;
        ++l;
      }
    }
  }*/
  
  println(ans);
}

int main() {
  IO::init_in();
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

