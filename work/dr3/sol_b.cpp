// Thank you, meyi ... but ...
// It's never the end.
// We still have an inFINITY line.
#include<bits/stdc++.h>
using namespace std;
#define ri int
typedef long long ll;
const int maxn=5010,mod=998244353;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
struct modint{
	int val;
	inline modint(int val_=0):val(val_){}
	inline modint &operator=(int val_){return val=val_,*this;}
	inline modint &operator+=(const modint &k){return val=val+k.val>=mod?val+k.val-mod:val+k.val,*this;}
	inline modint &operator-=(const modint &k){return val=val-k.val<0?val-k.val+mod:val-k.val,*this;}
	inline modint &operator*=(const modint &k){return val=1ll*val*k.val%mod,*this;}
	inline modint &operator^=(int k){
	    modint ret=1,tmp=*this;
	    for(;k;k>>=1,tmp*=tmp)if(k&1)ret*=tmp;
	    return val=ret.val,*this;
	}
	inline modint &operator/=(modint k){return *this*=(k^=mod-2);}
	inline modint &operator+=(int k){return val=val+k>=mod?val+k-mod:val+k,*this;}
	inline modint &operator-=(int k){return val=val<k?val-k+mod:val-k,*this;}
	inline modint &operator*=(int k){return val=1ll*val*k%mod,*this;}
	inline modint &operator/=(int k){return *this*=((modint(k))^=mod-2);}
	template<class T>friend modint operator+(modint a,T b){return a+=b;}
	template<class T>friend modint operator-(modint a,T b){return a-=b;}
	template<class T>friend modint operator*(modint a,T b){return a*=b;}
	template<class T>friend modint operator^(modint a,T b){return a/=b;}
	template<class T>friend modint operator/(modint a,T b){return a/=b;}
	friend modint operator^(modint a,int b){return a^=b;}
	friend bool operator==(modint a,int b){return a.val==b;}
	friend bool operator!=(modint a,int b){return a.val!=b;}
	inline bool operator!(){return !val;}
	inline modint operator-(){return val?mod-val:0;}
	inline modint &operator++(){return *this+=1;}
};
using mi=modint;
mi f[maxn][maxn],g[maxn][maxn],p[maxn],P;
int a,b,n,t_case,x,y;
char s[maxn];
int main(){
	scanf("%d",&t_case);
	while(t_case--){
		scanf("%d%d%d%d%d%s",&n,&x,&y,&a,&b,s+1);
		P=1-mi(x)/y;
		for(ri i=1;i<=n;++i)p[i]=(s[i]=='R');
		for(ri i=0;i<=n+1;++i)clear(f[i],n),clear(g[i],n);
		f[0][a]=1;
		for(ri i=1;i<=n;++i){
			mi sum=0;
			for(ri j=0;j<=n;++j){
				if(j)sum=sum*P+f[i-1][j];
				f[i][j]=f[i-1][j+1]*(1-p[i])+sum*p[i]*(1-P);
			}
		}
		g[n+1][b]=1;
		for(ri i=n;i;--i){
			mi sum=0;
			for(ri j=0;j<=n;++j){
				if(j)sum=sum*(1-P)+g[i+1][j];
				g[i][j]=g[i+1][j+1]*p[i]+sum*(1-p[i])*P;
			}
		}
		mi ans=0;
		for(ri i=0;i<=n;++i)ans+=f[i][0]*g[i+1][0];
		printf("%d\n",ans);
	}
	return 0;
}
