// clang-format off

#include <bits/stdc++.h>

using namespace std; template<typename T> void rd(T &a) {   cin >> a; } template<typename A> void O(const A& a) {   cout << a << '\n'; } typedef pair<int, int> pii;    typedef long long i64; const int N = 1<<18; const int p = 998244353; int a[N]; bool vis[N]; int n; int g[N]; int fac[N], ifac[N], inv[N]; inline int q_pow(i64 x, int a) {   i64 ret = 1;   while (a) {     if (a & 1) ret = ret * x % p;     x = x * x % p;     a >>= 1;   }   return ret; }  inline int C(int n, int k) {   return 1ll * fac[n] * ifac[n-k] % p * ifac[k] % p; }  int b[N], m, lt[N]; int v[N]; int A[N], B[N]; int bv[N];  inline void ntt(int *a, int lim) {   for (int i = (1); i <= (lim-1); ++i) {     bv[i] = bv[i>>1]>>1;     if (i&1) bv[i] |= lim>>1;     if (bv[i]>i) swap(a[i],a[bv[i]]);   }   for (int i = 1; i < lim; i <<= 1) {     int w = g[N/i/2];     for (int j = 0; j < lim; j += i<<1) {       int ww = 1;       for (int k = j; k < i + j; ++k) {         int x = a[k], y = 1ll * a[k+i] * ww % p;         a[k] = (x+y)%p;         a[k+i] = (x+p-y)%p;         ww = 1ll * ww * w % p;       }     }   }  }  inline void intt(int *a, int lim) {   ntt(a,lim);   reverse(a+1,a+lim);   int iv = q_pow(lim,p-2);   for (int i = (0); i <= (lim-1); ++i) a[i] = 1ll * a[i] * iv % p; }  inline void mul(int lim) {   ntt(A,lim);   ntt(B,lim);   for (int i = (0); i <= (lim-1); ++i) A[i] = 1ll * A[i] * B[i] % p;   intt(A,lim); }  void work(int l, int r) {   if (r == l + 1) {     for (int i = 1; i <= b[l]; ++i) {       v[lt[l] + i] = C(b[l], i);     }     return;   }   int m = (l + r) >> 1;   work(l,m);   work(m,r);   int lim = 1 << (32 - __builtin_clz(lt[r] - lt[l] + 1));   for (int i = (lt[l]); i <= (lt[m]-1); ++i) A[i-lt[l]] = v[i];   for (int i = (lt[m]); i <= (lt[r]-1); ++i) B[i-lt[m]] = v[i];   mul(lim);   for (int i = (lt[l]); i <= (lt[r]-1); ++i) v[i] = A[i-lt[l]];   for (int i = (0); i <= (lim-1); ++i) A[i] = B[i] = 0; }  inline void solve() {   rd(n);   inv[1] = inv[0] = fac[1] = ifac[1] = ifac[0] = ifac[0] = 1;   for (int i = (2); i <= (n); ++i) {     inv[i] = 1ll * inv[p%i] * (p - p / i) % p;     fac[i] =1ll* fac[i-1]*i%p;     ifac[i]=1ll*ifac[i-1]*inv[i]%p;   }   g[0] = 1;   g[1] = q_pow(114514,(p-1)/N);   for (int i = (2); i <= (N-1); ++i) g[i] = 1ll * g[i-1]*g[1] % p;   for (int i = (1); i <= (n); ++i) rd(a[i]);   for (int i = (1); i <= (n); ++i) if (!vis[i]) {   int u = i;   while (!vis[u]) {   ++b[m];   vis[u] = 1;   u = a[u];   }   ++m;   }   for (int i = (1); i <= (m); ++i) {     lt[i] = lt[i-1] + b[i-1] + 1;   }   work(0,m);   int ans = 0;   for (int i = (m); i <= (n); ++i) {     int cur = 1ll * fac[i] * v[i] % p;     if ((n-i)&1) ans = (ans + p - cur) % p;     else ans = (ans + cur) % p;   }   O(ans); }  int main() {   ios::sync_with_stdio(0);   cin.tie(0);   solve();   return 0; } 

/*

       　  　▃▆█▇▄▖

　 　 　 ▟◤▖　　　◥█▎

   　 ◢◤　 ▐　　　 　▐▉

　 ▗◤　　　▂　▗▖　　▕█▎

　◤　▗▅▖◥▄　▀◣　　█▊

▐　▕▎◥▖◣◤　　　　◢██

█◣　◥▅█▀　　　　▐██◤

▐█▙▂　　     　◢██◤

◥██◣　　　　◢▄◤

 　　▀██▅▇▀



 */

// WHY POLY??????????????????


