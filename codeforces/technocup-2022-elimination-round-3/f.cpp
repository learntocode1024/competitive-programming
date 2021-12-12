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

const int N = 2e5+5;
const int mod = 998244353;
#define LL long long
#define M 5000000
int tot = 0;
#define mid (l+r>>1)
LL n,q,p[M],mark[M][2],a[M],L,R,qs,num, lc[M], rc[M];
void up(LL x){p[x]=(p[lc[x]]+p[rc[x]])%mod;}
void pushdown(LL x,LL l,LL r){
    p[lc[x]]=p[lc[x]]*mark[x][1]%mod;
    p[lc[x]]=(p[lc[x]]+(mark[x][0]*(mid-l+1)))%mod;
    p[rc[x]]=p[rc[x]]*mark[x][1]%mod;
    p[rc[x]]=(p[rc[x]]+(mark[x][0]*(r-mid)))%mod;
    mark[lc[x]][1]=mark[lc[x]][1]*mark[x][1]%mod;
    mark[lc[x]][0]=(mark[lc[x]][0]*mark[x][1]+mark[x][0])%mod;
    mark[rc[x]][1]=mark[rc[x]][1]*mark[x][1]%mod;
    mark[rc[x]][0]=(mark[rc[x]][0]*mark[x][1]+mark[x][0])%mod;
    mark[x][0]=0ll,mark[x][1]=1ll;
}
void add(LL &x,LL l,LL r,LL m){
  if (!x) x = ++tot, mark[x][1]=1;
    if(r<L||R<l) return;
    if(L<=l&&r<=R){
        mark[x][0]=(mark[x][0]+m)%mod;
        p[x]=(p[x]+(m*(r-l+1)))%mod;
        return;
    }
    pushdown(x,l,r);
    add(lc[x],l,mid,m),add(rc[x],mid+1,r,m);
    up(x);
}
void mult(LL &x,LL l,LL r,LL m){
  if (!x) x = ++tot, mark[x][1]=1;
    if(r<L||R<l) return;
    if(L<=l&&r<=R){
        mark[x][0]=mark[x][0]*m%mod;     
        mark[x][1]=mark[x][1]*m%mod;
        p[x]=p[x]*m%mod;
        return;
    }
    pushdown(x,l,r);
    mult(lc[x],l,mid,m),mult(rc[x],mid+1,r,m);
    up(x);
}
LL query(LL x,LL l,LL r){
    if(r<L||R<l || !x) return 0ll;
    LL ans;
    if(L<=l&&r<=R) ans=p[x]%mod;
    else{
        pushdown(x,l,r);
        ans=(query(lc[x],l,mid)+query(rc[x],mid+1,r))%mod;
        up(x);
    }
    return ans;
}
i64 rt;

int main(){
  cin >> n;
  int a;
  cin >> a;
  L = 1, R = a;
  add(rt, 1, 1e9, 1);
  for (int i = 1; i < n; ++i) {
    cin >> a;
    int num = p[rt];
    L = a + 1, R = 1e9;
    mult(rt, 1, 1e9, 0);
    L = 1, R = a;
    mult(rt, 1, 1e9, -1);
    add(rt, 1, 1e9, num);
  }
  println(p[rt]);
    return 0;
}
