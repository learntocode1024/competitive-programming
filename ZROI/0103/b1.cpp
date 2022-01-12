#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<vector>
#include<ctime>
#include<cstring>
#include<map>
#include<cmath>
#include<queue>
#define mp make_pair
#define PII pair<int,int>
#define fi first
#define se second
#define pb push_back
#define int long long
using namespace std;
char gc() {
  constexpr int xn = 1 << 20;
  static char b[xn], *s = b, *t = b;
  return s == t and (t = (s = b) + fread(b, 1, xn, stdin)) == b ? EOF : *s++;
}
inline int read(){
	int x=0,f=1;char c=gc();while(!isdigit(c)){if(c=='-')f=-1;c=gc();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc();}
	return f==-1?~x+1:x;
}
int n,da,db;
int tot;
int head[2000010],nxt[4000010],to[4000010],vl[4000010];
const int mod=998244353;
inline int qpow(int x,int k=mod-2){
	int res=1;
	while(k){ if(k&1) res=1ll*res*x%mod; x=1ll*x*x%mod; k>>=1;}
	return res;
}
struct TAG{
	int x,iv;
	TAG(){
		x=iv=1;
	}
	TAG(long long p,long long y){
		x=p,iv=y;
	}
}mul[2000010];
TAG operator *(TAG a,TAG b){
	return TAG{1ll*a.x*b.x%mod,1ll*a.iv*b.iv%mod};
}
int operator *(int a,TAG b){
	return 1ll*a*b.x%mod;
}
void add(int x,int y,int z){
	nxt[++tot]=head[x];head[x]=tot;to[tot]=y,vl[tot]=z;
}
int dep[2000010],fa[2000010];
int mxl[2000010],son[2000010];
int Lf[2000010],iLf[2000010];
int pf[2000010];
void dfs1(int x,int f){
	dep[x]=dep[f]+1;fa[x]=f;
	for(int i=head[x];i;i=nxt[i]){
		int v=to[i];
		if(v==f) continue ;
		Lf[v]=vl[i];
		dfs1(v,x);
		if(mxl[v]>mxl[son[x]]) son[x]=v;
		mxl[x]=max(mxl[x],mxl[v]+1);
	}
}
int dfn[2000010],idx;
int *dp[2000010];
int buf[2000010],*nw=buf;
int s[2000010];
int g[2000010];
int pr1[2000010],pr2[1000010];
int Add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
int sub(int x,int y){
	return x>=y?x-y:x+mod-y;
}
void dfs2(int x,int top){
	// printf("%d %d\n",x,top);
	if(x==top){
		dp[x]=nw;nw+=mxl[x]+1;
	}
	// dfn[x]=++idx
	if(son[x]){
		dp[son[x]]=dp[x]+1;
		dfs2(son[x],top);
		dp[x][0]=1ll*s[son[x]]*Lf[son[x]]%mod*iLf[son[x]]%mod;
		mul[x]=mul[son[x]]*TAG{1-Lf[son[x]]+mod,iLf[son[x]]};
		s[x]=Add(s[son[x]],dp[x][0]);
		if(mxl[x]>=db){
			s[x]=sub(s[x],dp[x][db]);
			dp[x][db]=0;
		}
	}
	else s[x]=dp[x][0]=1;
	for(int i=head[x];i;i=nxt[i]){
		int v=to[i];if(v==son[x]||v==fa[x]) continue ;
		dfs2(v,v);
		int ev=min(db-1,mxl[v]);
		pr1[0]=dp[x][0]*mul[x];pr2[0]=dp[v][0];
		for(int j=1;j<=ev+1;++j){
			if(j<=mxl[x]) pr1[j]=Add(pr1[j-1],dp[x][j]*mul[x]);
			else pr1[j]=pr1[j-1];
			if(j<=mxl[v]) pr2[j]=Add(pr2[j-1],dp[v][j]);
			else pr2[j]=pr2[j-1];
		}
		auto fix=[&](int j,int va){
			va=1ll*va*mul[x].iv%mod;
			s[x]=Add(sub(s[x],dp[x][j]),va);
			dp[x][j]=va;
		};
		for(int j=0;j<=ev+1;++j){
			int tt=dp[x][j]*mul[x];
			int T=1ll*Lf[v]*s[v]%mod*tt%mod;
			int sm=0;
			if(min(ev,min(j-1,db-j-2))>=0) sm=1ll*tt*pr2[min(ev,min(j-1,db-j-2))]%mod;
			if(min(j-1,db-j-1)>=0&&j-1<=ev) sm=Add(sm,1ll*dp[v][j-1]*pr1[min(j-1,db-j-1)]%mod);
			fix(j,T+(1ll*(1-Lf[v]+mod)*sm%mod));
		}
		for(int j=max(db-ev-2,ev+2);j<=mxl[x]&&j<db;++j){
			int tt=dp[x][j]*mul[x];
			int T=1ll*Lf[v]*s[v]%mod*tt%mod;
			int sm=0;
			if(min(ev,min(j-1,db-j-2))>=0) sm=1ll*tt*pr2[min(ev,min(j-1,db-j-2))]%mod;
			if(min(j-1,db-j-1)>=0&&j-1<=ev) sm=Add(sm,1ll*dp[v][j-1]*pr1[min(j-1,db-j-1)]%mod);
			fix(j,T+(1ll*(1-Lf[v]+mod)*sm%mod));
		}
	}
	if(x==top){
		for(int i=0;i<=mxl[x];++i) dp[x][i]=1ll*dp[x][i]*mul[x]%mod;
		s[x]=1ll*s[x]*mul[x]%mod;
		mul[x]=TAG{1,1};
	}
}
signed main(){
	mxl[0]=-1;
	// freopen("run1.in","r",stdin);
	n=read(),da=read(),db=read();
	if(da<=2*db) printf("1\n");
	else{
		int mxd=0,mxp=0;
		int t=qpow(10000000);
		for(int i=1;i<n;++i){
			int u=read(),v=read(),p=read();
			p=1ll*p*t%mod;add(u,v,p);add(v,u,p);
			mxp=max(mxp,p);
		}
		db<<=1;db|=1;
		dfs1(1,0);
		pf[0]=1;
		for(int i=1;i<=n;++i) pf[i]=1ll*pf[i-1]*(1-Lf[i]+mod)%mod;
		iLf[n]=qpow(pf[n]);
		for(int i=n-1;i>=0;--i) iLf[i]=1ll*iLf[i+1]*(1-Lf[i+1]+mod)%mod;
		for(int i=1;i<=n;++i) iLf[i]=1ll*iLf[i]*pf[i-1]%mod;
		dfs2(1,1);
		printf("%lld\n",s[1]);
	}
}
 

