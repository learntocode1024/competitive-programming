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
const int N = 114514;
int d[N], tot, D_P;

inline int q_pow(i64 x, int a, int p) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

void get_d(int n) {
  tot = 0;
  D_P = n;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i == 0) d[tot++] = i;
  }
  int t2 = tot;
  ROF(i,0,t2-1) {
    if (n / d[i] > d[i]) d[tot++] = n / d[i];
  }
}

int phi(int n) {
  int ret = n;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      ret /= i;
      ret *= i-1;
      while(n%i==0) n/=i;
    }
  }
  if (n) {
    ret /= n;
    ret *= n-1;
  }
  return ret;
}

int ord(int x, int p) {
  FOR(i,0,tot-1) {
    if (q_pow(x, d[i], p) == 1) return d[i];
  }
  return 1;
}


int get_g(int p) {
  get_d(p-1);
  for (int i = 2; i < 114514; ++i) {
    if (ord(i, p) == p - 1) return i;
  }
  return -1;
}

i64 index(i64 a,i64 b,i64 p){
  int s_z=ceil(sqrt(p)); 
  i64 b_s=b%p;
  map<i64, i64> tab;
  tab[b_s]=0;
  for(int i=1;i<=s_z;i++){
    b_s=b_s*a%p;
    tab[b_s]=i;
  }
  b_s=q_pow(a,s_z,p);
  i64 t_p=1;
  for(i64 i=1;i<=s_z;i++){
    t_p=t_p*b_s%p;
    if(tab[t_p])
      return ((i*s_z-tab[t_p])%p+p)%p;
  }
  return -1;
}

inline void solve() {
  int x, m, p;
  rd(x,m,p);
  if (x == 1) {
    O(1,2);
    return;
  }
  int g = get_g(p);
  x = index(g, x, p);
  int n = p - 1;
  n /= __gcd(n, x);
  int t = 1;
  while (__gcd(n,m) != 1) {
    ++t;
    n /= __gcd(n,m);
  }
  get_d(phi(n));
  O(t,t+ord(m,n));
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

