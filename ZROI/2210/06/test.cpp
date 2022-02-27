#include<bits/stdc++.h>
#define R register
#define N 40201
#define ll long long
#define pp std::pair<int,int>
#define mk std::make_pair
#define P 998244353
#define I4 748683265
#define fi first
#define se second

const int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int n,X[N],Y[N],a[2050][2050],T[N],ans;
std::map<pp,int> mp,mc;
std::unordered_set<int> mw[2050];

inline int qpow(int x,int y){
	R int re=1;
	for(;y;y>>=1,x=1LL*x*x%P) if(y&1) re=1LL*re*x%P;
	return re;
}

inline void Add(int &x,const int &y){x+=y-P,x+=(x>>31)&P;}

inline void guass(int n){
	std::random_shuffle(a+1,a+n+1);
	for(R int i=1;i<=n;++i)
		for(R int j=1;j<=n+1;++j) if(a[i][j]) mw[i].insert(j);
	for(R int i=1;i<=n;++i){
		R int j=i;
		for(;j<=n;++j) if(a[j][i]) break;
		if(j^i) std::swap(a[i],a[j]),std::swap(mw[i],mw[j]);
		R int ha=qpow(a[i][i],P-2);
		for(j=1;j<=n;++j){
			if(j==i) continue;
			if(mw[j].find(i)==mw[j].end())continue;
			R int qc=1LL*(P-a[j][i])*ha%P;
			for(auto k:mw[i]){
				if(!a[j][k]) mw[j].insert(k);
				a[j][k]=(a[j][k]+1LL*qc*a[i][k])%P;
				if(!a[j][k]) mw[j].erase(k);
			}
		}
	}
	for(R int i=1;i<=n;++i){
		a[i][n+1]=(a[i][n+1]*(P-1LL)%P*qpow(a[i][i],P-2))%P;
	}
}

inline void work1(){
	for(R int i=1;i<=n;++i){
		for(R int j=0;j<4;++j){
			R int x=X[i]+dx[j],y=Y[i]+dy[j];
			if(mp.find(mk(x,y))==mp.end()) continue;
			Add(a[i][mp[mk(x,y)]],I4);
		}
		Add(a[i][i],P-1),Add(a[i][n+1],T[i]);
	}
	guass(n);
	for(auto i:mc){
		R int sx=i.fi.fi,sy=i.fi.se,aq=0;
		for(R int j=0;j<4;++j){
			R int x=sx+dx[j],y=sy+dy[j]; if(mp.find(mk(x,y))==mp.end()) continue;
			R int qc=mp[mk(x,y)]; Add(aq,a[qc][n+1]);
		}
		aq=1LL*I4*aq%P; ans^=aq;
	}
	std::cout<<ans;
}

int main(){
//	freopen("!!!.out","r",stdin);
	scanf("%d",&n);
	for(R int i=1;i<=n;++i){
		scanf("%d%d%d",&X[i],&Y[i],&T[i]),mp[mk(X[i],Y[i])]=i;
	}
	for(R int i=1;i<=n;++i)
		for(R int j=0;j<4;++j){
			R int x=X[i]+dx[j],y=Y[i]+dy[j];
			if(mp.find(mk(x,y))==mp.end()) mc[mk(x,y)]=1;
		}
	if(n<=2000)work1();
	return 0;
}
