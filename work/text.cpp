#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int base=233;
typedef long long LL;
#define N 3000005
std::unordered_map<LL,int>X;
inline int readint(){
    int c=getchar(),d=0;
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar())
    d=d*10+(c^'0');
    return d;
}
int n,m,k,id[N],fp=0,buc[N];
LL ans[N];
int siz;
char s[N];
struct que{
    int l,r,id;
    inline bool operator<(const que&rhs)const{
        return(l/siz!=rhs.l/siz)?l<rhs.l:r<rhs.r;
    }
}q[100005];
#define FOR(x, y, z) for (int x = y; x < z; ++x)  
unsigned long long H[N], srt[N], aa[N];
void Hash() {
  H[1] = s[1];
  const unsigned long long b = 131;
  FOR(i, 2, n + 1) {
    H[i] = H[i-1] * b + s[i];
  }
  unsigned long long pwk = b;
  FOR(i, 1, k) pwk *= b;
  FOR(i, 1, n + 2 - k) {
    srt[i - 1] = aa[i] = H[i + k - 1] - H[i - 1] * pwk;
  }
  sort(srt, srt + n - k + 1);
  int ss = unique(srt, srt + n - k + 1) - srt;
  FOR(i, 1, n - k + 2) {
    id[i] = lower_bound(srt, srt + ss, aa[i]) - srt + 1;
  }
}

int main(){
    n=readint(),m=readint(),k=readint();
    scanf("%s",s+1);
    Hash();
    for(int i=1;i<=m;++i){
        q[i].l=readint(),q[i].r=readint();q[i].id=i;
        if(q[i].r>n-k+1)q[i].r=n-k+1;
        if(q[i].l>q[i].r)q[i].l=1,q[i].r=0;
    }
    siz=n/sqrt(m);
    std::sort(q+1,q+m+1);
    LL now=0;
    for(int l=1,r=0,i=1;i<=m;++i){
        while(r<q[i].r)now+=buc[id[++r]]++;
        while(l>q[i].l)now+=buc[id[--l]]++;
        while(l<q[i].l)now-=--buc[id[l++]];
        while(r>q[i].r)now-=--buc[id[r--]];
        ans[q[i].id]=now;
    }
    for(int i=1;i<=m;++i)printf("%lld\n",ans[i]);
    return 0;
}
